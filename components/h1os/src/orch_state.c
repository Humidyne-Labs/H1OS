/**
 * @file orch_state.c
 * @brief Layer 3: Persistent RTC Slow SRAM state implementation
 *
 * Copyright (c) 2026 Humidyne Labs
 * SPDX-License-Identifier: MIT
 */

#include "h1os/orch_state.h"

#include "esp_attr.h"
#include "esp_system.h"

#include <string.h>

RTC_NOINIT_ATTR static orch_persisted_state_t s_persisted_state;

orch_persisted_state_t *RTC_IRAM_ATTR orch_state_get(void)
{
    if (s_persisted_state.magic != ORCH_RTC_MAGIC) {
        orch_state_reset();
    }
    return &s_persisted_state;
}

void RTC_IRAM_ATTR orch_state_reset(void)
{
    uint8_t *p = (uint8_t *)&s_persisted_state;
    for (size_t i = 0; i < sizeof(s_persisted_state); i++) {
        p[i] = 0;
    }
    s_persisted_state.magic = ORCH_RTC_MAGIC;
    s_persisted_state.sample_interval_sec = 60;
    s_persisted_state.flow_b_period_sec = 300;
    s_persisted_state.amb_floor_temp_centi_c = 0;
    s_persisted_state.window_low_temp_centi_c = 0;
    s_persisted_state.window_high_temp_centi_c = 0;
    s_persisted_state.last_glass_temp_centi_c = 0;
    s_persisted_state.trinode_confidence_pct = 0;
}

void RTC_IRAM_ATTR orch_state_push_sample(const orch_tri_node_sample_t *sample)
{
    if (sample == NULL)
        return;

    orch_persisted_state_t *st = orch_state_get();
    st->ring[st->ring_head] = *sample;
    st->ring_head = (st->ring_head + 1) % ORCH_RING_CAPACITY;
    st->total_samples++;
}

bool orch_state_get_latest_sample(orch_tri_node_sample_t *out_sample)
{
    if (out_sample == NULL)
        return false;

    orch_persisted_state_t *st = orch_state_get();
    if (st->total_samples == 0)
        return false;

    uint8_t latest_idx = (st->ring_head == 0) ? (ORCH_RING_CAPACITY - 1) : (st->ring_head - 1);
    *out_sample = st->ring[latest_idx];
    return true;
}

bool orch_state_get_latest_valid_sample(orch_tri_node_sample_t *out_sample)
{
    if (out_sample == NULL)
        return false;

    orch_persisted_state_t *st = orch_state_get();
    if (st->total_samples == 0)
        return false;

    uint32_t count = (st->total_samples < ORCH_RING_CAPACITY) ? st->total_samples : ORCH_RING_CAPACITY;
    for (uint32_t step = 1; step <= count; step++) {
        uint8_t idx =
            (uint8_t)((st->ring_head + ORCH_RING_CAPACITY - (step % ORCH_RING_CAPACITY)) % ORCH_RING_CAPACITY);
        if (st->ring[idx].quality_flags & SAMPLE_FLAG_VALID_COLD) {
            *out_sample = st->ring[idx];
            return true;
        }
    }

    uint8_t latest_idx = (st->ring_head == 0) ? (ORCH_RING_CAPACITY - 1) : (st->ring_head - 1);
    *out_sample = st->ring[latest_idx];
    return true;
}
