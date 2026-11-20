/**
 * @file test_orch_math.c
 * @brief Host C11 verification suite for Layer 3 August-Roche-Magnus psychrometrics & EWMA math.
 */

#include "h1os/orch_math.h"

#include <math.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static int s_failures = 0;

static void check_near(const char *label, float actual, float expected, float tol)
{
    float diff = fabsf(actual - expected);
    if (isnan(actual) || diff > tol) {
        fprintf(stderr, "FAIL [%s]: got=%.6f expected=%.6f tol=%.6f\n",
                label, (double)actual, (double)expected, (double)tol);
        s_failures++;
    }
}

static void check_bool(const char *label, bool actual, bool expected)
{
    if (actual != expected) {
        fprintf(stderr, "FAIL [%s]: got=%d expected=%d\n",
                label, actual ? 1 : 0, expected ? 1 : 0);
        s_failures++;
    }
}

int main(void)
{
    /* 1. Saturation vapor pressure e_s(T) = 6.112 * expf((17.625 * T) / (243.04 + T)) */
    check_near("es_0C", orch_math_calc_sat_vapor_pressure(0.0f), 6.112f, 0.005f);
    check_near("es_20C", orch_math_calc_sat_vapor_pressure(20.0f), 23.38f, 0.05f);
    check_near("es_25C", orch_math_calc_sat_vapor_pressure(25.0f), 31.68f, 0.05f);
    check_near("es_40C", orch_math_calc_sat_vapor_pressure(40.0f), 73.81f, 0.10f);

    /* 2. Vapor pressure with [0, 100]% clamping */
    float es25 = orch_math_calc_sat_vapor_pressure(25.0f);
    check_near("vp_50pct", orch_math_calc_vapor_pressure(25.0f, 50.0f), 0.5f * es25, 0.01f);
    check_near("vp_neg_clamp", orch_math_calc_vapor_pressure(25.0f, -15.0f), 0.0f, 0.0001f);
    check_near("vp_over_clamp", orch_math_calc_vapor_pressure(25.0f, 125.0f), es25, 0.01f);

    /* 3. Dew point (RH=100% equals T; RH=0% clamps cleanly; 25C/50% ~ 13.86C) */
    check_near("dew_100pct", orch_math_calc_dew_point(22.5f, 100.0f), 22.5f, 0.01f);
    check_near("dew_25C_50pct", orch_math_calc_dew_point(25.0f, 50.0f), 13.86f, 0.05f);
    float dew_zero = orch_math_calc_dew_point(20.0f, 0.0f);
    if (!isfinite(dew_zero) || dew_zero >= 0.0f) {
        fprintf(stderr, "FAIL [dew_0pct_finite]: got=%.6f\n", (double)dew_zero);
        s_failures++;
    }

    /* 4. Combined psychrometrics & NULL output guard */
    float out_vp = 0.0f;
    float out_dew = 0.0f;
    orch_math_calc_psychrometrics(25.0f, 50.0f, &out_vp, &out_dew);
    check_near("psychro_vp", out_vp, 0.5f * es25, 0.01f);
    check_near("psychro_dew", out_dew, 13.86f, 0.05f);
    orch_math_calc_psychrometrics(25.0f, 50.0f, NULL, NULL);

    /* 5. Absolute humidity d_v = 216.7 * e / (273.15 + T) */
    check_near("abs_hum_25C_50pct", orch_math_calc_absolute_humidity(out_vp, 25.0f), 11.51f, 0.08f);
    check_near("abs_hum_kelvin_guard", orch_math_calc_absolute_humidity(10.0f, -273.2f), 0.0f, 0.0001f);

    /* 6. EWMA filter boundaries and recurrence */
    check_near("ewma_alpha0", orch_math_update_ewma(30.0f, 20.0f, 0.0f), 20.0f, 0.0001f);
    check_near("ewma_alpha_neg", orch_math_update_ewma(30.0f, 20.0f, -0.5f), 20.0f, 0.0001f);
    check_near("ewma_alpha1", orch_math_update_ewma(30.0f, 20.0f, 1.0f), 30.0f, 0.0001f);
    check_near("ewma_alpha_over", orch_math_update_ewma(30.0f, 20.0f, 1.5f), 30.0f, 0.0001f);
    check_near("ewma_qtr", orch_math_update_ewma(24.0f, 20.0f, 0.25f), 21.0f, 0.0001f);

    /* 7. Thermal plateau gate in centi-degrees across negative and positive bounds [-40C..+85C] */
    check_bool("plateau_exact", orch_math_is_plateau_settled(2100, 2120, 20), true);
    check_bool("plateau_neg_dir", orch_math_is_plateau_settled(2120, 2100, 20), true);
    check_bool("plateau_exceed", orch_math_is_plateau_settled(2100, 2121, 20), false);
    check_bool("plateau_subzero_ok", orch_math_is_plateau_settled(-4000, -3985, 20), true);
    check_bool("plateau_hot_exceed", orch_math_is_plateau_settled(8450, 8500, 20), false);

    if (s_failures > 0) {
        fprintf(stderr, "test_orch_math: %d assertion(s) failed\n", s_failures);
        return EXIT_FAILURE;
    }
    printf("test_orch_math: all assertions passed\n");
    return EXIT_SUCCESS;
}
