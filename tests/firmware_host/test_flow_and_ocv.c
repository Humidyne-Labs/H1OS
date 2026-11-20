/**
 * @file test_flow_and_ocv.c
 * @brief Host C11 verification suite for 13-point LiPo OCV piecewise curve and MANDATE-02 flow slicing invariants.
 */

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

/* Flow bounds from components/h1os/include/h1os/h1os.h */
#define TEST_FLOW_A_MIN_SEC         60U
#define TEST_FLOW_A_MAX_SEC         14400U
#define TEST_FLOW_B_MIN_SEC         300U
#define TEST_FLOW_B_MAX_SEC         86400U
#define TEST_FLOW_REMAINDER_MIN_SEC 60U

typedef struct {
    uint16_t mv;
    uint16_t soc_x10;
} test_lipo_knot_t;

/* Authoritative 13-point LiPo OCV table matching components/h1os/src/sub_power.c */
static const test_lipo_knot_t s_lipo_table[] = {
    {4200U, 1000U},
    {4120U, 950U},
    {4040U, 880U},
    {3960U, 800U},
    {3890U, 730U},
    {3820U, 600U},
    {3780U, 480U},
    {3750U, 360U},
    {3720U, 250U},
    {3680U, 150U},
    {3600U, 80U},
    {3450U, 30U},
    {3300U, 0U}
};

static uint16_t ref_mv_to_soc_tenths(uint16_t mv)
{
    size_t count = sizeof(s_lipo_table) / sizeof(s_lipo_table[0]);
    if (mv >= s_lipo_table[0].mv) {
        return 1000U;
    }
    if (mv <= s_lipo_table[count - 1U].mv) {
        return 0U;
    }
    for (size_t i = 0U; i < count - 1U; i++) {
        if (mv <= s_lipo_table[i].mv && mv >= s_lipo_table[i + 1U].mv) {
            uint32_t span_mv  = (uint32_t)s_lipo_table[i].mv - (uint32_t)s_lipo_table[i + 1U].mv;
            uint32_t span_soc = (uint32_t)s_lipo_table[i].soc_x10 - (uint32_t)s_lipo_table[i + 1U].soc_x10;
            uint32_t diff_mv  = (uint32_t)mv - (uint32_t)s_lipo_table[i + 1U].mv;
            return (uint16_t)((uint32_t)s_lipo_table[i + 1U].soc_x10 + ((diff_mv * span_soc) / span_mv));
        }
    }
    return 0U;
}

static bool ref_validate_flow_periods(uint32_t flow_a_sec,
                                      uint32_t flow_b_sec,
                                      uint32_t *out_overflow,
                                      uint32_t *out_remainder)
{
    if (flow_a_sec < TEST_FLOW_A_MIN_SEC || flow_a_sec > TEST_FLOW_A_MAX_SEC) {
        return false;
    }
    if (flow_b_sec < TEST_FLOW_B_MIN_SEC || flow_b_sec > TEST_FLOW_B_MAX_SEC) {
        return false;
    }
    if (flow_a_sec > 255U && (flow_a_sec % 60U != 0U)) {
        return false;
    }
    if (flow_b_sec <= flow_a_sec) {
        return false;
    }

    uint32_t full_slices = flow_b_sec / flow_a_sec;
    uint32_t remainder   = flow_b_sec % flow_a_sec;

    if (remainder > 0U && remainder < TEST_FLOW_REMAINDER_MIN_SEC) {
        return false;
    }
    if (remainder > 255U && (remainder % 60U != 0U)) {
        return false;
    }

    uint32_t overflow = full_slices + (remainder > 0U ? 1U : 0U);
    if (overflow < 2U) {
        return false;
    }

    if (out_overflow != NULL) {
        *out_overflow = overflow;
    }
    if (out_remainder != NULL) {
        *out_remainder = remainder;
    }
    return true;
}

int main(void)
{
    int failures = 0;

    /* 1. Verify OCV clamp bounds & exact 13-point knot outputs */
    if (ref_mv_to_soc_tenths(4350U) != 1000U || ref_mv_to_soc_tenths(4200U) != 1000U) {
        fprintf(stderr, "FAIL: OCV upper clamp\n");
        failures++;
    }
    if (ref_mv_to_soc_tenths(3300U) != 0U || ref_mv_to_soc_tenths(2500U) != 0U) {
        fprintf(stderr, "FAIL: OCV lower clamp\n");
        failures++;
    }
    size_t knot_count = sizeof(s_lipo_table) / sizeof(s_lipo_table[0]);
    for (size_t i = 0U; i < knot_count; i++) {
        uint16_t got = ref_mv_to_soc_tenths(s_lipo_table[i].mv);
        if (got != s_lipo_table[i].soc_x10) {
            fprintf(stderr, "FAIL: OCV knot %u mV -> %u (expected %u)\n",
                    s_lipo_table[i].mv, got, s_lipo_table[i].soc_x10);
            failures++;
        }
    }

    /* 2. Verify monotonicity across entire [3200..4300 mV] range */
    uint16_t prev = 0U;
    for (uint16_t mv = 3200U; mv <= 4300U; mv++) {
        uint16_t cur = ref_mv_to_soc_tenths(mv);
        if (cur < prev || cur > 1000U) {
            fprintf(stderr, "FAIL: OCV non-monotonic at %u mV (%u < %u)\n", mv, cur, prev);
            failures++;
            break;
        }
        prev = cur;
    }

    /* 3. Verify MANDATE-02 6 flow-period invariants */
    uint32_t overflow = 0U;
    uint32_t rem      = 0U;
    if (!ref_validate_flow_periods(60U, 300U, &overflow, &rem) || overflow != 5U || rem != 0U) {
        fprintf(stderr, "FAIL: valid (60, 300)\n");
        failures++;
    }
    if (!ref_validate_flow_periods(300U, 1800U, &overflow, &rem) || overflow != 6U || rem != 0U) {
        fprintf(stderr, "FAIL: valid (300, 1800)\n");
        failures++;
    }
    if (!ref_validate_flow_periods(3600U, 86400U, &overflow, &rem) || overflow != 24U || rem != 0U) {
        fprintf(stderr, "FAIL: valid (3600, 86400)\n");
        failures++;
    }
    if (!ref_validate_flow_periods(240U, 600U, &overflow, &rem) || overflow != 3U || rem != 120U) {
        fprintf(stderr, "FAIL: valid (240, 600) with 120s remainder\n");
        failures++;
    }

    if (!ref_validate_flow_periods(300U, 360U, &overflow, &rem) || overflow != 2U || rem != 60U) {
        fprintf(stderr, "FAIL: valid (300, 360) overflow=2\n");
        failures++;
    }

    /* Invalid cases across all 6 invariants */
    if (ref_validate_flow_periods(59U, 300U, NULL, NULL))      { fprintf(stderr, "FAIL: A<60\n"); failures++; }
    if (ref_validate_flow_periods(14460U, 86400U, NULL, NULL)) { fprintf(stderr, "FAIL: A>14400\n"); failures++; }
    if (ref_validate_flow_periods(60U, 299U, NULL, NULL))      { fprintf(stderr, "FAIL: B<300\n"); failures++; }
    if (ref_validate_flow_periods(3600U, 86460U, NULL, NULL))  { fprintf(stderr, "FAIL: B>86400\n"); failures++; }
    if (ref_validate_flow_periods(256U, 1024U, NULL, NULL))    { fprintf(stderr, "FAIL: A>255 not mult 60\n"); failures++; }
    if (ref_validate_flow_periods(300U, 300U, NULL, NULL))     { fprintf(stderr, "FAIL: B<=A\n"); failures++; }
    if (ref_validate_flow_periods(180U, 400U, NULL, NULL))     { fprintf(stderr, "FAIL: rem<60\n"); failures++; }
    if (ref_validate_flow_periods(360U, 640U, NULL, NULL))     { fprintf(stderr, "FAIL: rem>255 not mult 60\n"); failures++; }

    if (failures > 0) {
        fprintf(stderr, "test_flow_and_ocv: %d assertion(s) failed\n", failures);
        return EXIT_FAILURE;
    }
    printf("test_flow_and_ocv: all assertions passed\n");
    return EXIT_SUCCESS;
}
