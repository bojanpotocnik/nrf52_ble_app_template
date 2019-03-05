/******************************************************************************
 * @file     nrf_utils.h
 * @brief    Utility functions related to Nordic nRF SDK.
 * @version  V1.0
 * @author   Bojan Potočnik <info@bojanpotocnik.com>
 * @date     25. August 2018
 ******************************************************************************/

#ifndef NRF_UTILS_H_INCLUDED
#define NRF_UTILS_H_INCLUDED

#include "app_timer.h"

/**
 * @brief Function for retrieving milliseconds since RTC was initialized.
 *
 * @note The RTC counts using a 24 bit register and will overflow, which
 *       this function does not handle.
 *
 * @return Time difference [ms].
 */
static inline uint32_t millis() {
    return app_timer_cnt_get() * ((APP_TIMER_CONFIG_RTC_FREQUENCY + 1) * 1000ul) / APP_TIMER_CLOCK_FREQ;
}

/**
 * @brief Function for calculation time difference between two timestamps.
 *
 * @details This function handle one timer value wrap around.
 *
 * @param now      Current time.
 * @param previous Past time.
 *
 * @return Time difference [ms].
 */
static inline uint32_t millis_diff(uint32_t now, uint32_t previous) {
    // 0x00FFFFFF is MAX_RTC_COUNTER_VAL defined in app_timer.c and app_timer_rtx.c
    const uint32_t millis_max = 0x00FFFFFFul * ((APP_TIMER_CONFIG_RTC_FREQUENCY + 1) * 1000ul) / APP_TIMER_CLOCK_FREQ;
    // Handle single wrap-around.
    return ((now >= previous) ? (now - previous) : (millis_max - previous + now));
}


#endif // NRF_UTILS_H_INCLUDED
