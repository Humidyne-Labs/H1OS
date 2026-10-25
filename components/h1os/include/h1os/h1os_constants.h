/**
 * @file h1os_constants.h
 * @brief Canonical architectural constants, hardware timing budgets, and default configuration macros.
 *
 * @copyright Copyright (c) 2026
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

/**
 * @defgroup H1OS_Hardware_Timing Hardware Acquisition & Polling Timing Bounds
 * @{
 */
#define H1OS_TSENS_SETTLING_DELAY_US          400U   /**< Minimum analog settling delay following TSENS power-up (400 µs). */
#define H1OS_TSENS_READY_POLL_INTERVAL_US     5U     /**< Polling step interval while awaiting TSENS ready bit (5 µs).    */
#define H1OS_TSENS_READY_TIMEOUT_CYCLES       100U   /**< Maximum polling loop iterations (100 * 5 µs = 500 µs bound).     */
#define H1OS_SHTC3_CONVERSION_TOTAL_US        14500U /**< Sensirion SHTC3 maximum measurement duration (14.5 ms).        */
#define H1OS_TSENS_ESTIMATED_SAMPLE_US         450U   /**< Nominal TSENS acquisition duration (settling + ready poll).    */
#define H1OS_SHTC3_POST_TSENS_DELAY_US        (H1OS_SHTC3_CONVERSION_TOTAL_US - H1OS_TSENS_ESTIMATED_SAMPLE_US) /**< Remainder wait: 14,050 µs */
/** @} */

/**
 * @defgroup H1OS_System_Intervals System Intervals, Buffer Sizes & Thresholds
 * @{
 */
#define H1OS_NVS_AUTONOMY_COMMIT_INTERVAL_SEC 3600U  /**< Minimum elapsed deep sleep interval between unattended NVS commits (1 hour). */
#define H1OS_TELEMETRY_RING_CAPACITY          32U    /**< Fixed capacity of historical telemetry sample circular ring buffer. */
#define H1OS_TSENS_DEFAULT_INTERCEPT_CENTI_C  2052   /**< Default TSENS Q12 fixed-point intercept in centi-°C (20.52°C).     */
#define H1OS_RTC_STATE_MAGIC                  0x534C4154U /**< RTC state validation magic word ('SLAT').                  */
/** @} */

/**
 * @defgroup H1OS_RTOS_Tasks FreeRTOS Task Stacks & Scheduler Priorities
 * @{
 */
#define H1OS_TASK_STACK_SESSION_MONITOR       4096U  /**< Stack allocation for h1os_sess lifecycle monitor task (4 KB floor). */
#define H1OS_TASK_PRIO_SESSION_MONITOR        3      /**< FreeRTOS priority for session monitor task.                     */
#define H1OS_TASK_STACK_LVGL                  8192U  /**< Stack allocation for h1os_lvgl graphics rendering task (8 KB).  */
#define H1OS_TASK_PRIO_LVGL                   5      /**< Default FreeRTOS priority for LVGL graphics rendering task.     */
#define H1OS_TASK_STACK_AUDIO                 4096U  /**< Stack allocation for h1os_audio pipeline task (4 KB floor).     */
#define H1OS_TASK_PRIO_AUDIO                  6      /**< High-priority audio DMA pump FreeRTOS priority.                 */
#define H1OS_TASK_STACK_SD_MOUNT              4096U  /**< Stack allocation for sd_mount async worker task (4 KB floor).   */
#define H1OS_TASK_PRIO_SD_MOUNT               2      /**< Background FreeRTOS priority for MicroSD filesystem mount task. */
#define H1OS_TASK_STACK_LED_BREATH            2048U  /**< Stack allocation for led_breath PWM fading task.                */
#define H1OS_TASK_PRIO_LED_BREATH             1      /**< Idle-level FreeRTOS priority for LED breath animation task.     */
/** @} */

/**
 * @defgroup H1OS_Timeouts System Timeouts & Busy-Wait Poll Windows
 * @{
 */
#define H1OS_LVGL_DRAIN_TIMEOUT_MS            6000U  /**< Maximum wait time to drain in-flight LVGL rendering before sleep (6s). */
#define H1OS_LVGL_DRAIN_POLL_STEP_MS          20U    /**< Polling interval step during LVGL queue drain (20 ms).          */
#define H1OS_LVGL_SHUTDOWN_TIMEOUT_MS         6000U  /**< Maximum wait time for LVGL task deletion on shutdown (6s).      */
#define H1OS_LVGL_SHUTDOWN_STEP_MS            20U    /**< Polling interval step during LVGL shutdown wait (20 ms).        */
#define H1OS_ORCH_I2C_RECOVERY_TIMEOUT_US     20000U /**< Timeout for RTC I2C bus clock toggle recovery sequence (20 ms).*/
#define H1OS_ORCH_I2C_RECOVERY_STEP_US        500U   /**< Polling step interval during RTC I2C bus recovery (500 µs).     */
#define H1OS_SUB_POWER_RTC_INT_DRAIN_TIMEOUT_US 50000U /**< Timeout awaiting PCF85063A INT pin release to HIGH (50 ms).     */
#define H1OS_SUB_POWER_RTC_INT_DRAIN_STEP_US  500U   /**< Step delay while polling PCF85063A INT pin release (500 µs).    */
#define H1OS_SUB_SDCARD_COMMAND_TIMEOUT_MS    100U   /**< SDMMC host controller command response timeout margin (100 ms). */
#define H1OS_SUB_AUDIO_AMP_POWER_ON_DELAY_MS  120U   /**< Class-D audio amplifier power-up output stage settling delay.   */
#define H1OS_SUB_AUDIO_AMP_POWER_OFF_DELAY_MS 80U    /**< Class-D audio amplifier power-down muting delay.                */
#define H1OS_SUB_AUDIO_DEFAULT_WAIT_TIMEOUT_MS 500U  /**< Default playback completion wait timeout in milliseconds.       */
/** @} */

/**
 * @defgroup H1OS_Battery_Thresholds Battery, Power & Brownout Thresholds
 * @{
 */
#define H1OS_BATTERY_CRITICAL_CUTOFF_MV       3250U  /**< Hardware low-voltage critical cut-off threshold (3.25V).        */
#define H1OS_BATTERY_REBOUND_GATE_TENTHS_PCT  30U    /**< Diurnal thermal relaxation gate: minimum 3.0% SoC rebound jump. */
#define H1OS_BATTERY_ZERO_VOLT_GUARD_MV       3300U  /**< Lower voltage floor below which USB connection assumes charged. */
#define H1OS_BATTERY_ASSUMED_CHARGED_MV       4200U  /**< Assumed full cell potential when zero-volt USB guard activates. */
#define H1OS_BATTERY_NOMINAL_FALLBACK_MV      4000U  /**< Safe nominal default cell potential when uninitialized or out-of-range (4.0V). */
#define H1OS_BATTERY_FULL_CHARGE_THRESHOLD_MV 4180U  /**< Cell potential threshold indicating fully charged state (4.18V).*/
#define H1OS_BATTERY_CHARGING_RAMP_DELTA_MV   15U    /**< Minimum voltage rise delta confirming active charging ramp (15mV).*/
#define H1OS_BATTERY_CHARGING_FLOAT_DELTA_MV  5U     /**< Maximum float variation at CV top-off confirming charged state. */
/** @} */

/**
 * @defgroup H1OS_Loop_Bounds Hardware Loop Retry Bounds & Debounce Limits
 * @{
 */
#define H1OS_RTC_ARM_RETRY_LIMIT              3U     /**< Maximum retry attempts when arming external PCF85063A countdown.*/
#define H1OS_POWER_KEY_POLL_CYCLES            200U   /**< Maximum loop iterations when polling power button key release.  */
#define H1OS_POWER_KEY_STABLE_THRESHOLD       4U     /**< Required consecutive HIGH samples confirming power key release. */
#define H1OS_SDCARD_UNMOUNT_DRAIN_CYCLES      25U    /**< Maximum wait cycles draining pending async MicroSD mount tasks. */
#define H1OS_DISPLAY_IDLE_POLL_BOUND          60U    /**< Maximum polling loop iterations awaiting EPD busy pin release.  */
/** @} */

/**
 * @defgroup H1OS_UI_Parameters UI & User Experience Operation Parameters
 * @{
 */
#define H1OS_KEYPAD_LONG_PRESS_MS             2000U  /**< Long-press actuation duration for keypad navigation (2.0s).     */
#define H1OS_LVGL_BUFFER_LINES                40U    /**< Number of horizontal display lines allocated per LVGL draw buf. */
#define H1OS_DEFAULT_BREATH_PERIOD_MS         2000U  /**< Default period for user LED breathing PWM cycle (2.0s).         */
/** @} */

/**
 * @defgroup H1OS_Default_Config Default Presets for Application Lifecycle Configuration
 * @{
 */
#define H1OS_DEFAULT_INACTIVITY_TIMEOUT_SEC   30U    /**< Recommended default interactive session inactivity sleep timeout in seconds. */
#define H1OS_DEFAULT_FLOW_A_PERIOD_SEC        60U    /**< Recommended default Flow A headless sensor sample burst period in seconds.    */
#define H1OS_DEFAULT_FLOW_B_PERIOD_SEC        300U   /**< Recommended default Flow B unattended presentation refresh period in seconds. */
/** @} */

#ifdef __cplusplus
}
#endif
