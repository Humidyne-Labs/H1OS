/**
 * @file orch_state.c
 * @brief Layer 3: Persistent RTC Slow SRAM state implementation
 *
 * Copyright (c) 2026 Humidyne Labs
 * SPDX-License-Identifier: MIT
 */

#include "h1os/orch_state.h"
#include "h1os/sub_nvs.h"

#include "esp_attr.h"
#include "esp_system.h"

#include <string.h>

RTC_NOINIT_ATTR static volatile orch_persisted_state_t s_persisted_state;

volatile orch_persisted_state_t *RTC_IRAM_ATTR orch_state_get(void)
{
    if (s_persisted_state.magic != ORCH_RTC_MAGIC) {
        orch_state_reset();
    }
    return &s_persisted_state;
}

/**
 * @brief Reset persisted RTC state to default values.
 *
 * @return Return value of type void RTC_IRAM_ATTR.
 */
void RTC_IRAM_ATTR orch_state_reset(void)
{
    volatile uint8_t *p = (volatile uint8_t *)&s_persisted_state;
    for (size_t i = 0; i < sizeof(s_persisted_state); i++) {
        p[i] = 0;
    }

    s_persisted_state.magic                    = ORCH_RTC_MAGIC;
    s_persisted_state.sample_interval_sec      = 0;
    s_persisted_state.flow_b_period_sec        = 0;
    s_persisted_state.window_low_temp_centi_c  = 0;
    s_persisted_state.window_high_temp_centi_c = 0;
    s_persisted_state.last_glass_temp_centi_c  = 0;
    s_persisted_state.trinode_confidence_pct   = 0;
    s_persisted_state.tsens_offset_centi_c     = 2052;
    s_persisted_state.total_sleep_sec          = 0;
    s_persisted_state.total_app_run_ms         = 0;
    s_persisted_state.initial_soc_x10          = 0;
}

void orch_state_save_runtimes_to_nvs(void)
{
    volatile orch_persisted_state_t *st = orch_state_get();
    (void)sub_nvs_set_u32("pwr_sleep_s", st->total_sleep_sec);
    (void)sub_nvs_set_u32("pwr_app_ms", st->total_app_run_ms);
    (void)sub_nvs_set_u32("pwr_init_s10", (uint32_t)st->initial_soc_x10);
}

void orch_state_load_runtimes_from_nvs(void)
{
    volatile orch_persisted_state_t *st = orch_state_get();
    uint32_t val = 0;
    if (sub_nvs_get_u32("pwr_sleep_s", &val) == ESP_OK) {
        st->total_sleep_sec = val;
    }
    if (sub_nvs_get_u32("pwr_app_ms", &val) == ESP_OK) {
        st->total_app_run_ms = val;
    }
    if (sub_nvs_get_u32("pwr_init_s10", &val) == ESP_OK) {
        st->initial_soc_x10 = (uint16_t)val;
    }
}

void orch_state_reset_discharge_lap(uint16_t current_soc_x10)
{
    volatile orch_persisted_state_t *st = orch_state_get();
    st->initial_soc_x10  = (current_soc_x10 > 0) ? current_soc_x10 : 1000;
    st->total_sleep_sec  = 0;
    st->total_app_run_ms = 0;
    orch_state_save_runtimes_to_nvs();
}

/**
 * @brief Push a new Tri-Node telemetry sample into the RTC ring buffer.
 *
 * @param[in]    sample          Pointer to sample data to commit.
 *
 * @return Return value of type void RTC_IRAM_ATTR.
 */
void RTC_IRAM_ATTR orch_state_push_sample(const orch_tri_node_sample_t *sample)
{
    if (sample == NULL)
        return;

    volatile orch_persisted_state_t *st = orch_state_get();
    st->ring[st->ring_head] = *sample;
    st->ring_head = (st->ring_head + 1) % ORCH_RING_CAPACITY;
    st->total_samples++;
}

/**
 * @brief Get the latest committed sample from the ring buffer.
 *
 * @param[out]   out_sample      Destination pointer.
 *
 * @return true if reading present, false if buffer empty.
 */
bool orch_state_get_latest_sample(orch_tri_node_sample_t *out_sample)
{
    if (out_sample == NULL)
        return false;

    volatile orch_persisted_state_t *st = orch_state_get();
    if (st->total_samples == 0)
        return false;

    uint8_t latest_idx = (st->ring_head == 0) ? (ORCH_RING_CAPACITY - 1) : (st->ring_head - 1);
    *out_sample = st->ring[latest_idx];
    return true;
}

/**
 * @brief Get the newest sample in the ring buffer marked SAMPLE_FLAG_VALID_COLD.
 *
 * @details Defaults to the latest sample if no sample has been marked valid yet.
 *
 * @param[out]   out_sample      Destination pointer.
 *
 * @return true if a sample is returned, false if buffer empty.
 */
bool orch_state_get_latest_valid_sample(orch_tri_node_sample_t *out_sample)
{
    if (out_sample == NULL)
        return false;

    volatile orch_persisted_state_t *st = orch_state_get();
    if (st->total_samples == 0)
        return false;

    uint32_t count = (st->total_samples < ORCH_RING_CAPACITY) ? st->total_samples : ORCH_RING_CAPACITY;
    for (uint32_t step = 1; step <= count; step++) {
        uint8_t idx = (uint8_t)((st->ring_head + ORCH_RING_CAPACITY - (step % ORCH_RING_CAPACITY)) % ORCH_RING_CAPACITY);
        if (st->ring[idx].quality_flags & SAMPLE_FLAG_VALID_COLD) {
            *out_sample = st->ring[idx];
            return true;
        }
    }

    uint8_t latest_idx = (st->ring_head == 0) ? (ORCH_RING_CAPACITY - 1) : (st->ring_head - 1);
    *out_sample = st->ring[latest_idx];
    return true;
}
