/**
 * @file    ble_config.h
 * @author  Bojan Potočnik <info@bojanpotocnik.com>
 * @date    29 Jan 2019
 * @brief   File containing BLE configuration definitions.
 *
 * BLE configuration constants are moved from main.c to this file for clarity.
 */

#ifndef BLE_CONFIG_H_INCLUDED
#define BLE_CONFIG_H_INCLUDED

#include <stdbool.h>
#include "app_util.h"
#include "ble_gap.h"
#include "app_timer.h"


/* Many of the parameters below are set based on the following document:
 *
 *   Accessory Design Guidelines for Apple Devices, Release R7
 *   https://developer.apple.com/accessories/Accessory-Design-Guidelines.pdf
 *
 * Android devices does not have such specifications as they usually accepts any
 * set of valid parameters. However as this device shall also be iPhone
 * compatible, use Apple specs whenever possible.
 *
 * Below are the extracts from section 11. Bluetooth Low Energy.
 */


/* 11.5 Advertising Interval
 *      To be discovered by the device, the accessory should first use the
 *      recommended advertising interval of 20 ms for at least 30 seconds.
 *      If it is not discovered within the initial 30 seconds, Apple
 *      recommends using one of the following longer intervals to increase
 *      chances of discovery by the device:
 *       [152.5, 211.25, 318.75, 417.5, 546.25, 760, 852.5, 1022.5, 1285] ms
 */
/** The fast-advertising interval (in units of 0.625 ms). When set to 0, fast advertising is disabled. */
#define APP_ADV_FAST_INTERVAL   MSEC_TO_UNITS(20u, UNIT_0_625_MS)
/** The fast-advertising time-out (in units of 10 ms). When set to 0, fast-advertising will never timeout. */
#define APP_ADV_FAST_DURATION   MSEC_TO_UNITS(30000lu, UNIT_10_MS)

/** The slow-advertising interval (in units of 0.625 ms).
 *  When set to 0, slow advertising is disabled, otherwise it follows the fast advertising. */
#define APP_ADV_SLOW_INTERVAL   MSEC_TO_UNITS(852.5, UNIT_0_625_MS)
/** The slow-advertising time-out (in units of 10 ms). When set to 0, slow-advertising will never timeout. */
#define APP_ADV_SLOW_DURATION   MSEC_TO_UNITS(BLE_GAP_ADV_TIMEOUT_GENERAL_UNLIMITED, UNIT_10_MS)

/* 11.6 Connection Parameters
 *      The accessory is responsible for the connection parameters used for
 *      the Low Energy connection. The accessory should request connection
 *      parameters appropriate for its use case by sending an L2CAP Connection
 *      Parameter Update Request at the appropriate time. See the
 *      Bluetooth 4.0 specification, Volume 3, Part A, Section 4.20 for
 *      details.
 *      The connection parameter request may be rejected if it does not comply
 *      with all of these rules:
 *       - Slave Latency ≤30
 *       - 2 seconds ≤ connSupervisionTimeout ≤ 6 seconds
 *       - Interval Min modulo 15 ms == 0
 *       - Interval Min ≥15 ms
 *       - One of the following:
 *          - Interval Min + 15 ms ≤ Interval Max
 *          - Interval Min == Interval Max == 15 ms
 *             In this case, some devices will scale the interval to 30 ms
 *             to balance power and performance constraints.
 *       - Interval Max * (Slave Latency + 1) ≤ 2 seconds
 *       - Interval Max * (Slave Latency + 1) * 3 < connSupervisionTimeout
 *
 *       The device will not read or use the parameters in the Peripheral
 *       Preferred Connection Parameters characteristic.
 *       See the Bluetooth 4.0 specification, Volume 3, Part C, Section 12.5.
 */
#define SLAVE_LATENCY       0                                   /**< Slave latency (in number of connection events). */
#define CONN_SUP_TIMEOUT    MSEC_TO_UNITS(4000, UNIT_10_MS)     /**< Connection supervision timeout (in 10 ms units). */
#define MIN_CONN_INTERVAL   MSEC_TO_UNITS(15, UNIT_1_25_MS)     /**< Minimum acceptable connection interval (in 1.25 ms units). */
#define MAX_CONN_INTERVAL   MSEC_TO_UNITS(500, UNIT_1_25_MS)    /**< Maximum acceptable connection interval (in 1.25 ms units). */

/** Time from initiating event (connect or start of notification) to first time sd_ble_gap_conn_param_update is called (in app-timer ticks). */
#define FIRST_CONN_PARAMS_UPDATE_DELAY  APP_TIMER_TICKS(5000)
/** Time between each call to sd_ble_gap_conn_param_update after the first call (in app-timer ticks). */
#define NEXT_CONN_PARAMS_UPDATE_DELAY   APP_TIMER_TICKS(30000)
/** Number of attempts before giving up the connection parameter negotiation. */
#define MAX_CONN_PARAMS_UPDATE_COUNT    3

/* Security Parameters */
#define SEC_PARAM_BOND                  true                                /**< Whether to Perform bonding. */
#define SEC_PARAM_MITM                  false                               /**< Whether the Man In The Middle protection is required. */
#define SEC_PARAM_LESC                  false                               /**< Whether the LE Secure Connections is enabled. */
#define SEC_PARAM_KEYPRESS              false                               /**< Whether the Keypress notifications are enabled. */
#define SEC_PARAM_IO_CAPABILITIES       BLE_GAP_IO_CAPS_NONE                /**< Available I/O capabilities. */
#define SEC_PARAM_OOB                   false                               /**< Whether the Out Of Band data is available. */
#define SEC_PARAM_MIN_KEY_SIZE          7                                   /**< Minimum encryption key size. */
#define SEC_PARAM_MAX_KEY_SIZE          16                                  /**< Maximum encryption key size. */


/* 11.4 Advertising Data
 *      The Local Name should match the accessory's markings and packaging and not contain ':' or ';'.
 */
/** Initial name of the BLE device. Will be included in the advertising data. */
#define DEVICE_NAME                     "BLE Template"


#endif /* BLE_CONFIG_H_INCLUDED */
