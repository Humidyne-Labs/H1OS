/**
 * @file h1os_lifecycle.c
 * @brief Layer 4: Declarative application lifecycle engine implementation
 *
 * Copyright (c) 2026 Humidyne Labs
 * SPDX-License-Identifier: MIT
 */

#include "driver/gpio.h"
#include "driver/rtc_io.h"
#include "esp_log.h"
#include "esp_sleep.h"
#include "esp_timer.h"
#include "freertos/FreeRTOS.h"
#include "freertos/event_groups.h"
#include "freertos/task.h"
#include "h1os.h"
#include "h1os_lvgl.h"
#include "h1os_time.h"
#include "hal_i2c.h"
#include "hal_io.h"
#include "orch_display_sync.h"
#include "orch_flow.h"
#include "orch_math.h"
#include "orch_state.h"
#include "sdkconfig.h"
#include "soc/rtc_cntl_reg.h"
#include "soc/rtc_io_reg.h"
#include "sub_audio.h"
#include "sub_display.h"
#include "sub_nvs.h"
#include "sub_power.h"
#include "sub_rtc.h"
#include "sub_sdcard.h"
#include "ulp_h1os.h"

#include <stdio.h>
#include <string.h>

static const char *TAG = "h1os_lifecycle";

#define LIFECYCLE_LVGL_DRAIN_TIMEOUT_MS       6000U /**< Max wait to drain LVGL rendering (6s).     */
#define LIFECYCLE_DEFAULT_SYNC_TIMEOUT_MS     5000U /**< Default max wait for parallel on_sync (5s).*/
#define LIFECYCLE_BATTERY_CRITICAL_CUTOFF_MV  3250U /**< Critical brownout warning voltage (3.25V). */
#define LIFECYCLE_BATTERY_REBOUND_GATE_TENTHS 30U   /**< Minimum 3.0% SoC rebound to reset lap.     */
#define LIFECYCLE_POWER_KEY_POLL_CYCLES       200U  /**< Power key debounce loop iterations.        */
#define LIFECYCLE_POWER_KEY_STABLE_THRESHOLD  4U    /**< Stable HIGH consecutive read count.        */

#define BARRIER_SYNC_DONE    (1U << 0) /**< EventGroup bit: Core 0 sync phase complete.        */
#define BARRIER_DISPLAY_DONE (1U << 1) /**< EventGroup bit: Core 1 LVGL/EPD pipeline quiescent.*/
#define BARRIER_ALL_READY    (BARRIER_SYNC_DONE | BARRIER_DISPLAY_DONE)

static h1os_lifecycle_t   s_app_lifecycle     = {0};
static esp_timer_handle_t s_session_timer     = NULL;
static volatile bool      s_session_running   = false;
static bool               s_audio_initialized = false;
static portMUX_TYPE       s_session_mux       = portMUX_INITIALIZER_UNLOCKED;

static StaticEventGroup_t s_sleep_barrier_buf;
static EventGroupHandle_t s_sleep_barrier_group = NULL;
static volatile bool      s_sync_held           = false;

/* Retain previous battery state across deep-sleep cycles in RTC Slow SRAM for accurate charger unplug detection */
RTC_DATA_ATTR static h1os_battery_state_t s_prev_bat_state = H1OS_BATTERY_DISCHARGING;

static esp_err_t h1os_validate_flow_periods(uint32_t flow_a_sec,
                                            uint32_t flow_b_sec,
                                            uint32_t *out_overflow,
                                            uint32_t *out_remainder);
static esp_err_t h1os_apply_flow_periods(uint32_t flow_a_sec,
                                         uint32_t flow_b_sec,
                                         bool reset_slice_counter);

/**
 * @brief Initialize and clear the static FreeRTOS EventGroup sleep barrier.
 */
static void h1os_barrier_init_and_reset(void)
{
    if (s_sleep_barrier_group == NULL) {
        s_sleep_barrier_group = xEventGroupCreateStatic(&s_sleep_barrier_buf);
    }
    s_sync_held = false;
    (void)xEventGroupClearBits(s_sleep_barrier_group, BARRIER_ALL_READY);
}

/**
 * @brief Hold the deep-sleep barrier open for an asynchronous synchronization task.
 */
void h1os_sync_hold(void)
{
    s_sync_held = true;
}

/**
 * @brief Signal that Core 0 data synchronization is complete (`BARRIER_SYNC_DONE`).
 */
void h1os_sync_notify_complete(void)
{
    s_sync_held = false;
    h1os_lvgl_release_sync_gate();
    if (s_sleep_barrier_group != NULL) {
        (void)xEventGroupSetBits(s_sleep_barrier_group, BARRIER_SYNC_DONE);
    }
}

/**
 * @brief Signal that the Core 1 LVGL / SSD1681 display pipeline is quiescent (`BARRIER_DISPLAY_DONE`).
 */
void h1os_display_notify_quiescent(void)
{
    if (s_sleep_barrier_group != NULL) {
        (void)xEventGroupSetBits(s_sleep_barrier_group, BARRIER_DISPLAY_DONE);
    }
}

/**
 * @brief Fatal startup / lifecycle error handler with battery latch protection (MANDATE-06).
 *
 * @details Invokes the user `on_error` hook (if registered), places audio and display
 *          subsystems into low-power standby, releases the `GPIO 17` (`BAT_CTRL`) power
 *          latch so battery-powered units immediately power down without draining the
 *          LiPo cell, and enters emergency EXT0 deep sleep if USB VBUS is attached.
 */
static void h1os_handle_fatal_startup_error(const h1os_lifecycle_t *config, esp_err_t err, const char *stage)
{
    ESP_LOGE(TAG, "[FATAL STARTUP ERROR] Stage '%s' failed with %s (0x%x)",
             (stage != NULL) ? stage : "unknown", esp_err_to_name(err), (unsigned int)err);

    if (config != NULL && config->on_error != NULL) {
        config->on_error(err, (stage != NULL) ? stage : "unknown", config->user_data);
    }

    (void)sub_audio_standby();
    (void)sub_display_enter_deep_sleep();

    sub_power_cut_power_latch();
    vTaskDelay(pdMS_TO_TICKS(100));

    ESP_LOGW(TAG, "External USB power detected after fatal error; entering standby (wake: POWER button)");
    esp_sleep_disable_wakeup_source(ESP_SLEEP_WAKEUP_ALL);
    rtc_gpio_pullup_en(HAL_PIN_BUTTON_POWER);
    rtc_gpio_pulldown_dis(HAL_PIN_BUTTON_POWER);
    esp_sleep_enable_ext0_wakeup(HAL_PIN_BUTTON_POWER, 0);
    esp_deep_sleep_start();
}

/**
 * @brief One-shot esp_timer callback fired when the interactive session inactivity window expires.
 */
static void h1os_session_timeout_timer_cb(void *arg)
{
    (void)arg;
    bool was_running = false;
    portENTER_CRITICAL(&s_session_mux);
    was_running       = s_session_running;
    s_session_running = false;
    portEXIT_CRITICAL(&s_session_mux);

    if (!was_running) {
        return;
    }

    ESP_LOGI(TAG, "Interactive session timeout reached (%lu s inactivity). Entering deep sleep...",
             (unsigned long)s_app_lifecycle.session.inactivity_timeout_sec);

    /* Commit discharge lap autonomy metrics to NVS at the end of an interactive session */
    volatile orch_persisted_state_t *st = orch_state_get();
    orch_state_save_runtimes_to_nvs();
    st->last_nvs_commit_sec = st->total_sleep_sec;

    uint32_t sleep_sec = st->flow_b_period_sec;
    if (sleep_sec == 0) {
        ESP_LOGE(TAG, "Lifecycle configuration error: flow_b_period_sec is 0. Aborting to safe shutdown.");
        h1os_shutdown();
        return;
    }
    esp_err_t err = h1os_sleep(sleep_sec);
    if (err != ESP_OK) {
        ESP_LOGE(TAG, "h1os_sleep failed (%s), forcing safe shutdown", esp_err_to_name(err));
        h1os_shutdown();
    }
}

/**
 * @brief Reset the interactive session inactivity timer (extends session by timeout_sec).
 *
 * @details Uses the hardware-backed one-shot esp_timer alarm (`esp_timer_restart` / `esp_timer_start_once`)
 *          rather than a 500 ms polling FreeRTOS task, saving 4 KB of task stack and eliminating periodic wakes.
 */
void h1os_reset_session_timer(void)
{
    uint32_t timeout_sec = s_app_lifecycle.session.inactivity_timeout_sec;
    if (timeout_sec == 0) {
        ESP_LOGE(TAG, "Lifecycle configuration error: inactivity_timeout_sec is 0. Aborting session timer reset.");
        return;
    }

    uint64_t timeout_us = (uint64_t)timeout_sec * 1000000ULL;
    if (s_session_timer == NULL) {
        const esp_timer_create_args_t timer_args = {
            .callback              = &h1os_session_timeout_timer_cb,
            .arg                   = NULL,
            .dispatch_method       = ESP_TIMER_TASK,
            .name                  = "h1os_sess_tmr",
            .skip_unhandled_events = true,
        };
        if (esp_timer_create(&timer_args, &s_session_timer) != ESP_OK) {
            ESP_LOGE(TAG, "Failed to create h1os_sess_tmr esp_timer");
            return;
        }
    }

    if (esp_timer_restart(s_session_timer, timeout_us) != ESP_OK) {
        esp_err_t start_err = esp_timer_start_once(s_session_timer, timeout_us);
        if (start_err != ESP_OK) {
            ESP_LOGE(TAG, "Failed to start session timer: %s", esp_err_to_name(start_err));
        }
    }
    ESP_LOGD(TAG, "Interactive session timer reset (+%lu s)", (unsigned long)timeout_sec);
}

/**
 * @brief Check whether an interactive inactivity countdown session is active.
 *
 * @return true if running in an interactive user session, false during unattended wakes.
 */
bool h1os_is_session_active(void)
{
    return s_session_running;
}

/**
 * @brief H1os trigger chime.
 *
 * @param[in]    type            Parameter type.
 *
 * @return Return value of type static void.
 */
static void h1os_trigger_chime(h1os_chime_type_t type)
{
    if (!s_audio_initialized) {
        return;
    }
    if (s_app_lifecycle.presentation.on_chime != NULL) {
        s_app_lifecycle.presentation.on_chime(type, s_app_lifecycle.user_data);
    } else if (s_app_lifecycle.presentation.chime_mask & (1U << type)) {
        uint8_t chime = (uint8_t)type;
        sub_audio_play(SUB_AUDIO_CHIME, &chime, sizeof(chime));
    }
}

/**
 * @brief H1os trigger splash under scoped LVGL lock.
 *
 * @param[in]    type            Parameter type.
 *
 * @return Return value of type static void.
 */
static void h1os_trigger_splash(h1os_splash_type_t type)
{
    if (s_app_lifecycle.presentation.on_splash != NULL) {
        if (h1os_lvgl_lock(1000)) {
            s_app_lifecycle.presentation.on_splash(type, s_app_lifecycle.user_data);
            h1os_lvgl_unlock();
        }
    }
}

/**
 * @brief Drain pending LVGL render/flush tasks using event-driven semaphore wait and stop the Core 1 LVGL worker task.
 */
static void h1os_quiesce_lvgl_pipeline(void)
{
    h1os_lvgl_release_sync_gate();
    if (h1os_lvgl_has_pending_tasks()) {
        ESP_LOGI(TAG, "Waiting for LVGL pipeline to drain...");
        esp_err_t err = h1os_lvgl_wait_idle(LIFECYCLE_LVGL_DRAIN_TIMEOUT_MS);
        if (err != ESP_OK) {
            ESP_LOGW(TAG, "h1os_lvgl_wait_idle warning: %s", esp_err_to_name(err));
        }
    }
    esp_err_t err = h1os_lvgl_stop();
    if (err != ESP_OK) {
        ESP_LOGW(TAG, "h1os_lvgl_stop warning: %s", esp_err_to_name(err));
    }
}

/**
 * @brief Diagnostic dump of ULP wake telemetry.
 *
 * @details Isolated helper function for development; comment out the call in h1os_start() for release builds.
 *
 * @return Return value of type static void.
 */
static void debug_dump_ulp_telemetry(void)
{
    ESP_LOGI(TAG, "--------------------------------------------------------------------------------");
    ESP_LOGI(TAG, "[ULP TELEMETRY] Wake #%lu: cause=%lu (%s), slice=%lu/%lu, vbat=%lu mV (raw=%lu), btn=%lu, stuck=%lu",
             (unsigned long)ulp_wake_counter,
             (unsigned long)ulp_last_wake_cause,
             (ulp_last_wake_cause == ULP_WAKE_CAUSE_BOOT_BTN)           ? "BOOT_BTN"
             : (ulp_last_wake_cause == ULP_WAKE_CAUSE_PWR_BTN)          ? "PWR_BTN"
             : (ulp_last_wake_cause == ULP_WAKE_CAUSE_LONG_OVERFLOW)    ? "LONG_OVERFLOW"
             : (ulp_last_wake_cause == ULP_WAKE_CAUSE_SENSOR_TICK)      ? "SENSOR_TICK"
             : (ulp_last_wake_cause == ULP_WAKE_CAUSE_RTC_INT_STUCK)    ? "RTC_INT_STUCK_FAULT"
             : (ulp_last_wake_cause == ULP_WAKE_CAUSE_CRITICAL_BATTERY) ? "CRITICAL_BATTERY"
                                                                        : "UNKNOWN",
             (unsigned long)ulp_slice_counter,
             (unsigned long)ulp_overflow_limit,
             (unsigned long)ulp_last_vbat_mv,
             (unsigned long)ulp_vbat_raw_adc,
             (unsigned long)ulp_last_wake_btn,
             (unsigned long)ulp_rtc_int_stuck);

    if (ulp_rtc_int_stuck) {
        ESP_LOGE(TAG, "[ULP FAULT] External PCF85063A /INT pin (GPIO 5) remained stuck LOW >50ms! Re-arm suppressed.");
    }
    if (ulp_last_wake_cause == ULP_WAKE_CAUSE_CRITICAL_BATTERY) {
        ESP_LOGE(TAG, "[ULP FAULT] Battery critically low: %lu mV (< %lu mV threshold)!", (unsigned long)ulp_last_vbat_mv, (unsigned long)LIFECYCLE_BATTERY_CRITICAL_CUTOFF_MV);
    }
    ESP_LOGI(TAG, "--------------------------------------------------------------------------------");
}

/**
 * @brief Logs a prominent, framed ASCII console banner identifying the active lifecycle flow.
 *
 * @param[in]    flow            Parameter flow.
 *
 * @return Return value of type static void.
 */
static void h1os_log_flow_banner(orch_flow_type_t flow)
{
    volatile orch_persisted_state_t *st = orch_state_get();
    const char *flow_title = "UNKNOWN FLOW";
    const char *trigger_desc = "None";

    switch (flow) {
    case ORCH_FLOW_BOOT:
        flow_title = "[COLD BOOT INITIALIZATION]";
        trigger_desc = "Power-On Reset / Hard Reset";
        break;
    case ORCH_FLOW_A_SAMPLE:
        flow_title = "[FLOW A - QUIESCENT SENSOR SAMPLE BURST]";
        trigger_desc = "ULP Periodic Sleep Timer (60s tick)";
        break;
    case ORCH_FLOW_B_MAIN_WAKE:
        if (ulp_last_wake_btn == H1OS_WAKE_BTN_BOOT) {
            flow_title = "[FLOW B - INTERACTIVE UI SESSION]";
            trigger_desc = "ULP Tactile Press (BOOT / GPIO 0)";
        } else if (ulp_last_wake_btn == H1OS_WAKE_BTN_POWER) {
            flow_title = "[FLOW B - INTERACTIVE UI SESSION]";
            trigger_desc = "ULP Tactile Press (POWER / GPIO 18)";
        } else {
            flow_title = "[FLOW B - UNATTENDED RTC REFRESH & SYNC]";
            trigger_desc = "External RTC Alarm / Timer Tick";
        }
        break;
    case ORCH_FLOW_CRITICAL_OFF:
        flow_title = "[CRITICAL LOW POWER SHUTDOWN]";
        trigger_desc = "Battery Brownout Guard (< 3.25V) / Power Key Hold";
        break;
    case ORCH_FLOW_BOOTLOADER_JUMP:
        flow_title = "[ROM BOOTLOADER JUMP MODE]";
        trigger_desc = "BOOT Button Long-Press (>= 2.5s)";
        break;
    default:
        flow_title = "[UNKNOWN / CORRUPTED FLOW STATE]";
        trigger_desc = "Invalid Flow Enum Trapped";
        ESP_LOGE(TAG, "Unhandled or corrupted lifecycle flow detected: %d", (int)flow);
        break;
    }

    ESP_LOGI(TAG, "================================================================================");
    ESP_LOGI(TAG, ">>> H1OS ACTIVE FLOW: %s <<<", flow_title);
    ESP_LOGI(TAG, ">>> Trigger Source  : %s", trigger_desc);
    ESP_LOGI(TAG, ">>> Boot: %lu | Wakes: %lu (FlowB: %lu, Btn: %lu) | Session Timeout: %lu s",
             (unsigned long)st->boot_count,
             (unsigned long)st->wake_count,
             (unsigned long)st->flow_b_counter,
             (unsigned long)st->button_wake_count,
             (unsigned long)s_app_lifecycle.session.inactivity_timeout_sec);
    ESP_LOGI(TAG, "================================================================================");
}

/**
 * @brief H1os early system bringup.
 *
 * @param[in]    config          Parameter config.
 * @param[out]   out_flow        Detected execution flow.
 *
 * @return ESP_OK on success, or an error code.
 */
static esp_err_t h1os_early_system_bringup(const h1os_lifecycle_t *config, orch_flow_type_t *out_flow)
{
    if (out_flow == NULL || config == NULL) {
        return ESP_ERR_INVALID_ARG;
    }

    s_app_lifecycle = *config;

    esp_err_t err = sub_power_init_dfs(s_app_lifecycle.session.clk_mode);
    if (err != ESP_OK) {
        ESP_LOGE(TAG, "sub_power_init_dfs failed: %s", esp_err_to_name(err));
        return err;
    }

    err = hal_io_early_init();
    if (err != ESP_OK) {
        ESP_LOGE(TAG, "hal_io_early_init failed: %s", esp_err_to_name(err));
        return err;
    }

    err = hal_i2c_init();
    if (err != ESP_OK) {
        ESP_LOGE(TAG, "hal_i2c_init failed: %s", esp_err_to_name(err));
        return err;
    }

    /* Initialize PCF85063A RTC (12.5pF load cap, disable 32.768 kHz CLKOUT) */
    err = sub_rtc_init();
    if (err != ESP_OK) {
        ESP_LOGE(TAG, "sub_rtc_init failed: %s", esp_err_to_name(err));
        return err;
    }

    /* Only sync POSIX system clock from RTC if the RTC oscillator is valid and running */
    if (sub_rtc_is_oscillator_valid()) {
        esp_err_t sync_err = h1os_time_sync_rtc_to_system();
        if (sync_err != ESP_OK) {
            ESP_LOGW(TAG, "h1os_time_sync_rtc_to_system non-fatal warning: %s", esp_err_to_name(sync_err));
        }
    } else {
        ESP_LOGI(TAG, "RTC oscillator stopped / uninitialized; skipping system clock synchronization");
    }

    err = sub_nvs_init();
    if (err != ESP_OK) {
        ESP_LOGE(TAG, "sub_nvs_init failed: %s", esp_err_to_name(err));
        return err;
    }

    /* Ensure ULP GPIO wakeup and CPU SW wakeup interrupt are cleared while Xtensa CPU owns the system */
    CLEAR_PERI_REG_MASK(RTC_CNTL_ULP_CP_TIMER_REG, RTC_CNTL_ULP_CP_GPIO_WAKEUP_ENA);
    CLEAR_PERI_REG_MASK(RTC_CNTL_STATE0_REG, RTC_CNTL_SW_CPU_INT);
    SET_PERI_REG_MASK(RTC_CNTL_INT_CLR_REG,
                      RTC_CNTL_SLP_REJECT_INT_CLR |
                          RTC_CNTL_SLP_WAKEUP_INT_CLR |
                          RTC_CNTL_COCPU_INT_CLR |
                          RTC_CNTL_COCPU_TRAP_INT_CLR |
                          RTC_CNTL_ULP_CP_INT_CLR);
    REG_SET_BIT(RTC_CNTL_STATE0_REG, RTC_CNTL_SLP_REJECT_CAUSE_CLR);
    REG_WRITE(RTC_GPIO_STATUS_W1TC_REG, RTC_GPIO_STATUS_INT_W1TC_M);
    asm volatile("memw" ::: "memory");

    orch_flow_type_t flow = orch_flow_determine_wakeup();

    /* Load persisted autonomy runtimes from NVS after cold-boot orch_state_reset() so NVS values are preserved */
    if (flow == ORCH_FLOW_BOOT) {
        orch_state_load_runtimes_from_nvs();
    } else {
        /* Dump ULP telemetry before any slice counter reset on wake */
        debug_dump_ulp_telemetry();
    }

    volatile orch_persisted_state_t *st = orch_state_get();

    /* Commit flow periods AFTER orch_flow_determine_wakeup() so cold-boot orch_state_reset() does not wipe them,
     * and deep-sleep wakes preserve runtime periods set via h1os_set_flow_periods() */
    if (flow == ORCH_FLOW_BOOT ||
        h1os_validate_flow_periods(st->sample_interval_sec, st->flow_b_period_sec, NULL, NULL) != ESP_OK) {
        err = h1os_apply_flow_periods(config->session.flow_a_period_sec,
                                      config->session.flow_b_period_sec,
                                      true);
        if (err != ESP_OK) {
            return err;
        }
    } else {
        err = h1os_apply_flow_periods(st->sample_interval_sec,
                                      st->flow_b_period_sec,
                                      false);
        if (err != ESP_OK) {
            return err;
        }
    }

    ESP_LOGI(TAG, "Booting %s (%s) Version %s [Flow A: %lus, Flow B: %lus]",
             H1OS_NAME,
             H1OS_SUBTITLE,
             h1os_version_get_string(),
             (unsigned long)st->sample_interval_sec,
             (unsigned long)st->flow_b_period_sec);

    h1os_log_flow_banner(flow);

    /* Initialize ULP on cold boot / non-ULP wake with validated non-zero sample_interval_sec */
    err = sub_power_init_ulp(st->sample_interval_sec);
    if (err != ESP_OK) {
        ESP_LOGE(TAG, "sub_power_init_ulp failed: %s", esp_err_to_name(err));
        return err;
    }

    *out_flow = flow;
    return ESP_OK;
}

/**
 * @brief H1os handle non ui flows.
 *
 * @param[in]    flow            Parameter flow.
 *
 * @return True on success, false otherwise.
 */
static bool h1os_handle_non_ui_flows(orch_flow_type_t flow)
{
    if (flow == ORCH_FLOW_CRITICAL_OFF) {
        ESP_LOGW(TAG, "Critical shutdown requested! Powering down.");
        h1os_shutdown();
        return true;
    }

    if (flow == ORCH_FLOW_BOOTLOADER_JUMP) {
        ESP_LOGW(TAG, "Entering ROM bootloader jump mode via RTC_CNTL_FORCE_DOWNLOAD_BOOT...");
        sub_display_wait_busy(pdMS_TO_TICKS(5000));
        sub_audio_standby();
        REG_WRITE(RTC_CNTL_OPTION1_REG, RTC_CNTL_FORCE_DOWNLOAD_BOOT);
        esp_restart();
        return true;
    }

    return false;
}

/**
 * @brief H1os launch interactive or unattended Flow B session with dual-core parallel sync barrier.
 *
 * @param[in]    flow            Parameter flow.
 *
 * @return ESP_OK on success, or an error code.
 */
static esp_err_t h1os_launch_interactive_session(orch_flow_type_t flow)
{
    ESP_LOGI(TAG, "Launching Flow B Main Session...");
    bool is_wake     = (flow != ORCH_FLOW_BOOT);
    bool is_rtc_wake = false;
    bool button_woke = false;
    uint32_t causes  = 0;

    if (is_wake) {
        causes = esp_sleep_get_wakeup_causes();
        if (causes & BIT(ESP_SLEEP_WAKEUP_COCPU_TRAP_TRIG)) {
            ESP_LOGE(TAG, "[ULP FAULT] Coprocessor trapped/crashed! Causes bitmask: 0x%08lx", (unsigned long)causes);
            is_rtc_wake = false;
        } else if (causes & BIT(ESP_SLEEP_WAKEUP_ULP)) {
            button_woke = (ulp_last_wake_btn != 0);
            if (!button_woke) {
                is_rtc_wake = true;
            }
        } else {
            is_rtc_wake = true;
        }
    }

    esp_err_t err = h1os_lvgl_init(is_wake);
    if (err != ESP_OK) {
        ESP_LOGE(TAG, "h1os_lvgl_init failed: %s", esp_err_to_name(err));
        return err;
    }

    if (is_wake) {
        esp_err_t r_err = orch_display_sync_restore_to_framebuffer();
        if (r_err != ESP_OK) {
            ESP_LOGW(TAG, "Display frame restore failed (%s), forcing full OTP refresh", esp_err_to_name(r_err));
            h1os_lvgl_set_first_flush_mode(true);
        }
    }

    bool is_user_wake = (!is_wake) || button_woke;
    if (is_user_wake) {
        s_audio_initialized = (sub_audio_init(s_app_lifecycle.presentation.volume_pct) == ESP_OK);
    } else {
        s_audio_initialized = false;
        ESP_LOGI(TAG, "Unattended wake event: Codec initialization skipped (audio sleep preserved)");
    }

    /* Always clear any latched PCF85063A interrupt flags on Flow B entry */
    bool alarm_f = false, timer_f = false;
    err = sub_rtc_get_and_clear_interrupts(&alarm_f, &timer_f);
    if (err != ESP_OK) {
        ESP_LOGW(TAG, "Failed to clear RTC interrupt flags (%s)", esp_err_to_name(err));
    }

    portENTER_CRITICAL(&s_session_mux);
    s_session_running = !is_rtc_wake;
    portEXIT_CRITICAL(&s_session_mux);

    volatile orch_persisted_state_t *st = orch_state_get();

    h1os_wake_state_t wake_state = H1OS_WAKE_STATE_BOOT;
    if (is_wake) {
        wake_state = button_woke ? H1OS_WAKE_STATE_INTERACTIVE_SESSION : H1OS_WAKE_STATE_RTC_FLOW_B;
    }

    h1os_wake_context_t ctx = {
        .reset_reason       = esp_reset_reason(),
        .wakeup_causes      = causes,
        .wake_state         = wake_state,
        .boot_count         = st->boot_count,
        .deep_sleep_count   = st->wake_count,
        .flow_b_count       = st->flow_b_counter,
        .button_wake_count  = st->button_wake_count,
        .woke_from_button   = button_woke,
        .wake_button        = button_woke ? (uint8_t)ulp_last_wake_btn : (uint8_t)H1OS_WAKE_BTN_NONE,
        .sleep_duration_sec = button_woke ? st->sample_interval_sec : st->flow_b_period_sec,
        .user_data          = s_app_lifecycle.user_data,
    };

    h1os_barrier_init_and_reset();

    if (flow == ORCH_FLOW_BOOT) {
        h1os_trigger_chime(H1OS_CHIME_BOOT);
        h1os_trigger_splash(H1OS_SPLASH_BOOT);
        if (s_app_lifecycle.on_boot != NULL) {
            s_app_lifecycle.on_boot(s_app_lifecycle.user_data);
        }
    } else if (s_app_lifecycle.on_wake != NULL) {
        s_app_lifecycle.on_wake(&ctx, s_app_lifecycle.user_data);
    }

    /* Arm inbound pre-flush gate if configured so initial widgets + inbound sync coalesce into one refresh */
    if (s_app_lifecycle.on_sync != NULL && s_app_lifecycle.session.sync_wait_ms > 0U) {
        h1os_lvgl_set_sync_gate(s_app_lifecycle.session.sync_wait_ms);
    } else {
        h1os_lvgl_set_sync_gate(0U);
    }

    err = h1os_lvgl_start(5, 1);
    if (err != ESP_OK) {
        ESP_LOGE(TAG, "h1os_lvgl_start failed: %s", esp_err_to_name(err));
        return err;
    }

    /* Dispatch parallel on_sync hook on Core 0 while Core 1 drives the LVGL / SSD1681 display pipeline */
    if (s_app_lifecycle.on_sync != NULL) {
        s_app_lifecycle.on_sync(&ctx, s_app_lifecycle.user_data);
        if (!s_sync_held) {
            h1os_sync_notify_complete();
        }
    } else {
        h1os_sync_notify_complete();
    }

    if (is_rtc_wake) {
        uint32_t sync_to_ms = (s_app_lifecycle.session.sync_timeout_ms > 0U)
                                  ? s_app_lifecycle.session.sync_timeout_ms
                                  : LIFECYCLE_DEFAULT_SYNC_TIMEOUT_MS;
        uint32_t barrier_to_ms = (sync_to_ms > LIFECYCLE_LVGL_DRAIN_TIMEOUT_MS)
                                     ? sync_to_ms
                                     : LIFECYCLE_LVGL_DRAIN_TIMEOUT_MS;

        EventBits_t bits = xEventGroupWaitBits(s_sleep_barrier_group,
                                               BARRIER_ALL_READY,
                                               pdFALSE,
                                               pdTRUE,
                                               pdMS_TO_TICKS(barrier_to_ms));
        if ((bits & BARRIER_ALL_READY) != BARRIER_ALL_READY) {
            ESP_LOGW(TAG, "Sleep barrier timeout after %lu ms (bits=0x%02lx: SYNC=%d, DISP=%d); releasing gate",
                     (unsigned long)barrier_to_ms,
                     (unsigned long)bits,
                     (bits & BARRIER_SYNC_DONE) ? 1 : 0,
                     (bits & BARRIER_DISPLAY_DONE) ? 1 : 0);
            h1os_lvgl_release_sync_gate();
        }

        /* Ensure any UI updates queued via h1os_ui_post() just prior to BARRIER_SYNC_DONE finish flushing */
        err = h1os_lvgl_wait_idle(LIFECYCLE_LVGL_DRAIN_TIMEOUT_MS);
        if (err != ESP_OK) {
            ESP_LOGW(TAG, "h1os_lvgl_wait_idle warning: %s", esp_err_to_name(err));
        }

        ESP_LOGI(TAG, "RTC Countdown wake completed parallel refresh & sync. Entering deep sleep immediately.");
        uint32_t sleep_sec = st->flow_b_period_sec;
        if (sleep_sec == 0) {
            ESP_LOGE(TAG, "Lifecycle configuration error: flow_b_period_sec is 0 on RTC wake. Aborting to safe shutdown.");
            h1os_shutdown();
            return ESP_ERR_INVALID_STATE;
        }
        return h1os_sleep(sleep_sec);
    } else {
        uint32_t timeout_sec = s_app_lifecycle.session.inactivity_timeout_sec;
        if (timeout_sec == 0) {
            ESP_LOGE(TAG, "Lifecycle configuration error: inactivity_timeout_sec is 0 for interactive session. Aborting to safe shutdown.");
            h1os_shutdown();
            return ESP_ERR_INVALID_ARG;
        }
        ESP_LOGI(TAG, "Arming %lu-second interactive session esp_timer alarm...", (unsigned long)timeout_sec);
        h1os_reset_session_timer();
    }

    return ESP_OK;
}

/**
 * @brief Validate Flow A and Flow B periods against all 6 MANDATE-02 silicon and slicing invariants.
 */
static esp_err_t h1os_validate_flow_periods(uint32_t flow_a_sec,
                                            uint32_t flow_b_sec,
                                            uint32_t *out_overflow,
                                            uint32_t *out_remainder)
{
    /* Invariant 1: Flow A bounds (60s .. 14400s / 4h) */
    if (flow_a_sec < H1OS_FLOW_A_MIN_SEC || flow_a_sec > H1OS_FLOW_A_MAX_SEC) {
        ESP_LOGE(TAG, "Flow A interval %lu s out of bounds [%u..%u]",
                 (unsigned long)flow_a_sec, H1OS_FLOW_A_MIN_SEC, H1OS_FLOW_A_MAX_SEC);
        return ESP_ERR_INVALID_ARG;
    }

    /* Invariant 2: Flow B bounds (300s .. 86400s / 24h) */
    if (flow_b_sec < H1OS_FLOW_B_MIN_SEC || flow_b_sec > H1OS_FLOW_B_MAX_SEC) {
        ESP_LOGE(TAG, "Flow B interval %lu s out of bounds [%u..%u]",
                 (unsigned long)flow_b_sec, H1OS_FLOW_B_MIN_SEC, H1OS_FLOW_B_MAX_SEC);
        return ESP_ERR_INVALID_ARG;
    }

    /* Invariant 3: Prescaler whole-minute alignment for Flow A (> 255s uses 1/60 Hz clock) */
    if (flow_a_sec > 255U && (flow_a_sec % 60U != 0U)) {
        ESP_LOGE(TAG, "Flow A interval %lu s > 255s must be an exact multiple of 60 seconds",
                 (unsigned long)flow_a_sec);
        return ESP_ERR_INVALID_ARG;
    }

    /* Invariant 4: Ordering (Flow B must be strictly greater than Flow A) */
    if (flow_b_sec <= flow_a_sec) {
        ESP_LOGE(TAG, "Flow B (%lu s) must be strictly greater than Flow A (%lu s)",
                 (unsigned long)flow_b_sec, (unsigned long)flow_a_sec);
        return ESP_ERR_INVALID_ARG;
    }

    uint32_t full_slices = flow_b_sec / flow_a_sec;
    uint32_t remainder   = flow_b_sec % flow_a_sec;

    /* Invariant 5: Remainder floor (remainder must be 0 or >= 60s) */
    if (remainder > 0U && remainder < H1OS_FLOW_REMAINDER_MIN_SEC) {
        ESP_LOGE(TAG, "Remainder slice duration %lu s is below minimum floor (%u s)",
                 (unsigned long)remainder, H1OS_FLOW_REMAINDER_MIN_SEC);
        return ESP_ERR_INVALID_ARG;
    }

    /* Invariant 6: Remainder prescaler whole-minute alignment (> 255s) */
    if (remainder > 255U && (remainder % 60U != 0U)) {
        ESP_LOGE(TAG, "Remainder slice %lu s > 255s must be an exact multiple of 60 seconds",
                 (unsigned long)remainder);
        return ESP_ERR_INVALID_ARG;
    }

    uint32_t overflow = full_slices + (remainder > 0U ? 1U : 0U);
    if (overflow < 2U) {
        ESP_LOGE(TAG, "Slicing overflow %lu < 2; Flow A must execute at least once before Flow B",
                 (unsigned long)overflow);
        return ESP_ERR_INVALID_ARG;
    }

    if (out_overflow != NULL) {
        *out_overflow = overflow;
    }
    if (out_remainder != NULL) {
        *out_remainder = remainder;
    }
    return ESP_OK;
}

/**
 * @brief Atomically commit validated Flow A and Flow B periods to RTC Slow SRAM and ULP slice registers.
 */
static esp_err_t h1os_apply_flow_periods(uint32_t flow_a_sec,
                                         uint32_t flow_b_sec,
                                         bool reset_slice_counter)
{
    uint32_t overflow  = 0;
    uint32_t remainder = 0;
    esp_err_t err = h1os_validate_flow_periods(flow_a_sec, flow_b_sec, &overflow, &remainder);
    if (err != ESP_OK) {
        return err;
    }

    /* Atomic commit to RTC Slow Memory */
    volatile orch_persisted_state_t *st = orch_state_get();
    st->sample_interval_sec = flow_a_sec;
    st->flow_b_period_sec   = flow_b_sec;
    asm volatile("memw" ::: "memory");

    /* Cache in active session descriptor */
    s_app_lifecycle.session.flow_a_period_sec = flow_a_sec;
    s_app_lifecycle.session.flow_b_period_sec = flow_b_sec;

    /* Synchronize ULP and power subsystem */
    sub_power_set_sleep_slices(flow_a_sec, flow_b_sec, overflow, remainder);
    if (reset_slice_counter) {
        ulp_slice_counter = 0;
    }
    asm volatile("memw" ::: "memory");

    ESP_LOGI(TAG, "Configured flow periods: Flow A = %lu s, Flow B = %lu s (Slices=%lu, Remainder=%lu s)",
             (unsigned long)flow_a_sec, (unsigned long)flow_b_sec,
             (unsigned long)overflow, (unsigned long)remainder);

    return ESP_OK;
}

esp_err_t h1os_set_flow_periods(uint32_t flow_a_sec, uint32_t flow_b_sec)
{
    esp_err_t err = h1os_apply_flow_periods(flow_a_sec, flow_b_sec, true);
    if (err != ESP_OK) {
        return err;
    }

    /* Immediately arm PCF85063A hardware countdown timer with the new Flow A duration */
    return sub_rtc_arm_countdown(flow_a_sec);
}

esp_err_t h1os_start(const h1os_lifecycle_t *config)
{
    if (config == NULL) {
        return ESP_ERR_INVALID_ARG;
    }

    /* Validate flow periods up front before touching hardware */
    esp_err_t flow_err = h1os_validate_flow_periods(
        config->session.flow_a_period_sec,
        config->session.flow_b_period_sec,
        NULL,
        NULL
    );
    if (flow_err != ESP_OK) {
        ESP_LOGE(TAG, "Fatal lifecycle configuration: flow periods failed validation (%s)", esp_err_to_name(flow_err));
        h1os_handle_fatal_startup_error(config, flow_err, "flow_period_validation");
        return flow_err;
    }

    orch_flow_type_t flow = ORCH_FLOW_BOOT;
    esp_err_t bringup_err = h1os_early_system_bringup(config, &flow);
    if (bringup_err != ESP_OK) {
        ESP_LOGE(TAG, "System bringup failed (%s)", esp_err_to_name(bringup_err));
        h1os_handle_fatal_startup_error(config, bringup_err, "early_system_bringup");
        return bringup_err;
    }

    if (h1os_handle_non_ui_flows(flow)) {
        return ESP_OK;
    }

    esp_err_t sess_err = h1os_launch_interactive_session(flow);
    if (sess_err != ESP_OK) {
        ESP_LOGE(TAG, "Interactive session launch failed (%s)", esp_err_to_name(sess_err));
        h1os_handle_fatal_startup_error(config, sess_err, "launch_interactive_session");
        return sess_err;
    }
    return ESP_OK;
}

/**
 * @brief Retrieve current Tri-Node environmental telemetry.
 *
 * @param[out]   out_telemetry   Parameter out_telemetry.
 *
 * @return ESP_OK on success, or an error code.
 */
esp_err_t h1os_get_telemetry(h1os_telemetry_t *out_telemetry)
{
    if (!out_telemetry) {
        return ESP_ERR_INVALID_ARG;
    }
    memset(out_telemetry, 0, sizeof(h1os_telemetry_t));

    float t = 0.0f, rh = 0.0f, dew = 0.0f;
    esp_err_t ret = orch_flow_query_telemetry(&t, &rh, &dew);
    volatile orch_persisted_state_t *st = orch_state_get();

    if (ret == ESP_OK) {
        out_telemetry->ambient_temp_c       = t;
        out_telemetry->ambient_temp_f       = H1OS_CELSIUS_TO_FAHRENHEIT(t);
        out_telemetry->ambient_temp_k       = H1OS_CELSIUS_TO_KELVIN(t);
        out_telemetry->ambient_rh_pct       = rh;
        out_telemetry->dew_point_c          = dew;
        out_telemetry->dew_point_f          = H1OS_CELSIUS_TO_FAHRENHEIT(dew);
        out_telemetry->dew_point_k          = H1OS_CELSIUS_TO_KELVIN(dew);
        out_telemetry->vapor_pressure_hpa   = st->vapor_pressure_hpa;
        out_telemetry->is_thermally_settled = !orch_flow_is_thermal_lockout();
        out_telemetry->absolute_humidity_g  = orch_math_calc_absolute_humidity(st->vapor_pressure_hpa, t);
    }

    out_telemetry->window_low_c           = (float)st->window_low_temp_centi_c / 100.0f;
    out_telemetry->window_high_c          = (float)st->window_high_temp_centi_c / 100.0f;
    out_telemetry->window_avg_shtc3_c     = st->window_avg_shtc3_c;
    out_telemetry->window_avg_die_c       = st->window_avg_die_c;
    out_telemetry->temp_historical_c      = st->temp_historical_c;
    out_telemetry->rh_historical_pct      = st->rh_historical_pct;
    out_telemetry->trinode_temp_c         = st->trinode_temp_c;
    out_telemetry->trinode_delta_c        = st->trinode_delta_c;
    out_telemetry->trinode_confidence_pct = st->trinode_confidence_pct;
    out_telemetry->valid_trend            = st->valid_trend;
    out_telemetry->epd_glass_temp_c       = (float)st->last_glass_temp_centi_c / 100.0f;

    orch_tri_node_sample_t latest_samp = {0};
    if (orch_state_get_latest_sample(&latest_samp)) {
        out_telemetry->raw_shtc3_temp_c = (float)latest_samp.shtc3_temp_centi_c / 100.0f;
        out_telemetry->mcu_die_temp_c   = (float)latest_samp.mcu_tsens_centi_c / 100.0f;
    } else {
        out_telemetry->raw_shtc3_temp_c = t;
        out_telemetry->mcu_die_temp_c   = st->window_avg_die_c;
    }
    out_telemetry->sample_count        = st->total_samples;
    out_telemetry->boot_count          = st->boot_count;
    out_telemetry->wake_count          = st->wake_count;
    out_telemetry->flow_b_count        = st->flow_b_counter;
    out_telemetry->button_wake_count   = st->button_wake_count;
    out_telemetry->ulp_dispatch_reason = st->ulp_dispatch_reason;
    out_telemetry->sensor_fail_count   = st->sensor_fail_count;
    out_telemetry->last_sensor_error   = st->last_sensor_error;
    out_telemetry->is_rh_alert_active  = ((st->flags & ORCH_FLAG_RH_ALERT_ACTIVE) != 0);
    out_telemetry->flow_a_period_sec   = st->sample_interval_sec;
    out_telemetry->flow_b_period_sec   = st->flow_b_period_sec;

    uint16_t vbat_mv = 0;
    uint8_t vbat_pct = 0;
    h1os_battery_state_t bat_state = H1OS_BATTERY_DISCHARGING;
    if (sub_power_get_battery_status(&vbat_mv, &vbat_pct, &bat_state) == ESP_OK) {
        out_telemetry->battery_mv      = vbat_mv;
        out_telemetry->battery_percent = vbat_pct;
        out_telemetry->is_usb_powered  = (bat_state == H1OS_BATTERY_CHARGED || sub_power_connected_usb());
        out_telemetry->battery_state   = bat_state;
        st->last_vbat_mv               = vbat_mv;
        if (!out_telemetry->is_usb_powered && (st->boot_vbat_mv == 0 || vbat_mv > st->boot_vbat_mv)) {
            st->boot_vbat_mv = vbat_mv;
        }
        out_telemetry->boot_vbat_mv = st->boot_vbat_mv;

        uint16_t current_soc_x10 = sub_power_mv_to_soc_tenths(vbat_mv);

        if (bat_state == H1OS_BATTERY_DISCHARGING) {
            bool state_transition_from_charge = (s_prev_bat_state == H1OS_BATTERY_CHARGING ||
                                                 s_prev_bat_state == H1OS_BATTERY_CHARGED);
            if (st->initial_soc_x10 == 0 ||
                state_transition_from_charge ||
                current_soc_x10 >= st->initial_soc_x10 + LIFECYCLE_BATTERY_REBOUND_GATE_TENTHS) {
                orch_state_reset_discharge_lap(current_soc_x10);
            }
        }
        s_prev_bat_state = bat_state;

        sub_power_calc_autonomy(st->initial_soc_x10,
                                current_soc_x10,
                                st->total_sleep_sec,
                                st->total_app_run_ms,
                                &out_telemetry->autonomy);
    }

    return ret;
}

/**
 * @brief Put the platform into ultra-low-power deep sleep.
 *
 * @param[in]    sleep_sec       Parameter sleep_sec.
 *
 * @return ESP_OK on success, or an error code.
 */
esp_err_t h1os_sleep(uint32_t sleep_sec)
{
    if (sleep_sec == 0) {
        ESP_LOGE(TAG, "Lifecycle error: h1os_sleep received sleep_sec = 0. Aborting sleep transition.");
        return ESP_ERR_INVALID_ARG;
    }
    bool was_session_running = false;
    portENTER_CRITICAL(&s_session_mux);
    was_session_running = s_session_running;
    s_session_running   = false;
    portEXIT_CRITICAL(&s_session_mux);
    if (s_session_timer != NULL) {
        esp_timer_stop(s_session_timer);
    }

    if (was_session_running) {
        volatile orch_persisted_state_t *st = orch_state_get();
        orch_state_save_runtimes_to_nvs();
        st->last_nvs_commit_sec = st->total_sleep_sec;
    }

    ESP_LOGI(TAG, "Entering coordinated sleep sequence (%lu sec)...", (unsigned long)sleep_sec);
    h1os_trigger_chime(H1OS_CHIME_SLEEP);
    h1os_trigger_splash(H1OS_SPLASH_SLEEP);
    if (s_app_lifecycle.on_pre_sleep != NULL) {
        s_app_lifecycle.on_pre_sleep(sleep_sec, s_app_lifecycle.user_data);
    }

    h1os_quiesce_lvgl_pipeline();
    return orch_flow_transition_to_sleep(sleep_sec);
}

/**
 * @brief Execute system shutdown.
 *
 * @param[in]    force_clean_white Parameter force_clean_white.
 *
 * @return Return value of type static void.
 */
static void execute_system_shutdown(bool force_clean_white)
{
    ESP_LOGI(TAG, "Executing system shutdown (%s)...", force_clean_white ? "storage mode: clean white" : "standard mode");
    portENTER_CRITICAL(&s_session_mux);
    s_session_running = false;
    portEXIT_CRITICAL(&s_session_mux);
    if (s_session_timer != NULL) {
        esp_timer_stop(s_session_timer);
    }

    esp_err_t cancel_err = sub_rtc_cancel_countdown();
    if (cancel_err != ESP_OK) {
        ESP_LOGW(TAG, "sub_rtc_cancel_countdown failed: %s", esp_err_to_name(cancel_err));
    }

    h1os_trigger_chime(H1OS_CHIME_SHUTDOWN);
    h1os_trigger_splash(H1OS_SPLASH_SHUTDOWN);
    if (s_app_lifecycle.on_shutdown != NULL) {
        s_app_lifecycle.on_shutdown(s_app_lifecycle.user_data);
    }

    h1os_quiesce_lvgl_pipeline();

    sub_audio_wait_idle(1500);
    sub_audio_standby();

    sub_display_wait_busy(pdMS_TO_TICKS(5000));
    if (force_clean_white) {
        sub_display_clear_to_white_full();
        orch_state_get()->flags &= ~ORCH_FLAG_EPD_FRAME_VALID;
    } else {
        orch_display_sync_save_if_dirty();
    }
    sub_display_enter_deep_sleep();

    /* Persist cumulative autonomy runtimes to NVS prior to releasing power latch */
    volatile orch_persisted_state_t *st = orch_state_get();
    st->total_app_run_ms += (uint32_t)(esp_timer_get_time() / 1000ULL);
    orch_state_save_runtimes_to_nvs();

    int32_t stable_high = 0;
    for (int32_t i = 0; i < (int32_t)LIFECYCLE_POWER_KEY_POLL_CYCLES && stable_high < (int32_t)LIFECYCLE_POWER_KEY_STABLE_THRESHOLD; i++) {
        stable_high = (gpio_get_level(HAL_PIN_BUTTON_POWER) == 1) ? stable_high + 1 : 0;
        vTaskDelay(pdMS_TO_TICKS(50));
    }

    sub_power_cut_power_latch();
    vTaskDelay(pdMS_TO_TICKS(200));

    ESP_LOGW(TAG, "External power detected; entering standby (wake: POWER button only)");
    esp_sleep_disable_wakeup_source(ESP_SLEEP_WAKEUP_ALL);
    rtc_gpio_pullup_en(HAL_PIN_BUTTON_POWER);
    rtc_gpio_pulldown_dis(HAL_PIN_BUTTON_POWER);
    esp_sleep_enable_ext0_wakeup(HAL_PIN_BUTTON_POWER, 0);
    esp_deep_sleep_start();
}

/**
 * @brief Orderly system shutdown and physical battery power cut.
 */
void h1os_shutdown(void)
{
#if CONFIG_H1OS_EPD_CLEAN_WHITE_ON_SHUTDOWN
    execute_system_shutdown(true);
#else
    execute_system_shutdown(false);
#endif
}

/**
 * @brief Shutdown for long-term storage: clears display to pure white before cutting power.
 *
 * @details Protects e-Paper electrophoretic microcapsules against permanent dye migration and burn-in.
 */
void h1os_shutdown_for_storage(void)
{
    execute_system_shutdown(true);
}

/**
 * @brief Set audio subsystem output volume percentage (0% = Mute, 100% = 0 dB Max).
 *
 * @param[in]    volume_pct      Parameter volume_pct.
 *
 * @return ESP_OK on success, or an error code.
 */
esp_err_t h1os_set_volume(uint8_t volume_pct)
{
    return sub_audio_set_volume(volume_pct);
}

/**
 * @brief Retrieve historical Tri-Node telemetry samples from the RTC Slow SRAM ring buffer in chronological order.
 */
esp_err_t h1os_get_telemetry_history(orch_tri_node_sample_t *out_samples, size_t max_samples, size_t *out_count)
{
    if (out_samples == NULL || max_samples == 0 || out_count == NULL) {
        return ESP_ERR_INVALID_ARG;
    }
    return orch_state_get_ring_chronological(out_samples, max_samples, out_count) ? ESP_OK : ESP_FAIL;
}

/**
 * @brief Configure relative humidity target alert thresholds in centi-percent (1% = 100, e.g. 6200..7200).
 */
esp_err_t h1os_set_rh_alert_bounds(uint16_t rh_low_centi_pct, uint16_t rh_high_centi_pct)
{
    if (rh_high_centi_pct > 10000U || (rh_high_centi_pct > 0U && rh_low_centi_pct > rh_high_centi_pct)) {
        return ESP_ERR_INVALID_ARG;
    }
    volatile orch_persisted_state_t *st = orch_state_get();
    st->rh_alert_low_centi_pct  = rh_low_centi_pct;
    st->rh_alert_high_centi_pct = rh_high_centi_pct;
    if (rh_high_centi_pct == 0U) {
        st->flags &= (uint8_t)~ORCH_FLAG_RH_ALERT_ACTIVE;
    }
    return ESP_OK;
}

/**
 * @brief Force a driver-level electrophoretic display clear and full waveform scrub.
 */
esp_err_t h1os_display_force_clear(void)
{
    ESP_LOGI(TAG, "Forced display clear: executing driver-level SSD1681 full OTP scrub to pure white...");
    esp_err_t err = sub_display_clear_to_white_full();
    if (err == ESP_OK) {
        orch_display_sync_mark_dirty();
    }
    return err;
}

/* =========================================================================
 * Layer 4 Public Audio, MicroSD Storage, and Status LED API Implementations
 * ========================================================================= */

esp_err_t h1os_audio_play_raw(const int16_t *ptr, size_t len, size_t *bytes_written)
{
    if (ptr == NULL || len < sizeof(int16_t)) {
        return ESP_ERR_INVALID_ARG;
    }
    esp_err_t err = sub_audio_play(SUB_AUDIO_PCM, ptr, len);
    if (err == ESP_OK && bytes_written != NULL) {
        *bytes_written = len;
    }
    return err;
}

esp_err_t h1os_audio_play_tone(uint32_t freq_hz, uint32_t duration_ms)
{
    if (freq_hz < 100U || freq_hz > 10000U || duration_ms < 10U || duration_ms > 5000U) {
        return ESP_ERR_INVALID_ARG;
    }
    uint32_t params[2] = {freq_hz, duration_ms};
    return sub_audio_play(SUB_AUDIO_TONE, params, sizeof(params));
}

esp_err_t h1os_audio_play_chime(h1os_chime_type_t chime_type)
{
    uint8_t type_val = (uint8_t)chime_type;
    return sub_audio_play(SUB_AUDIO_CHIME, &type_val, sizeof(type_val));
}

bool h1os_sdcard_is_mounted(void)
{
    return sub_sdcard_is_mounted();
}

esp_err_t h1os_sdcard_get_capacity_mb(uint32_t *out_capacity_mb)
{
    return sub_sdcard_get_capacity_mb(out_capacity_mb);
}

esp_err_t h1os_sdcard_mount_async(void)
{
    return sub_sdcard_mount_async();
}

esp_err_t h1os_sdcard_unmount(void)
{
    return sub_sdcard_unmount();
}

void h1os_led_start_breathing(uint32_t period_ms)
{
    hal_led_start_breathing(period_ms);
}

void h1os_led_stop_breathing(void)
{
    hal_led_stop_breathing();
}

void h1os_led_set(bool on)
{
    hal_io_set_led(on);
}
