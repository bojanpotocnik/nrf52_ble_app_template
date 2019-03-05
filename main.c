/** @file
 *
 * @defgroup ble_sdk_app_template_main main.c
 * @{
 * @ingroup ble_sdk_app_template
 * @brief Template project main file.
 *
 * This file contains a template for creating a new application. It has the code
 * necessary to advertise, get a connection restart advertising on disconnect
 * and if no new connection created go back to system-off mode.
 *
 * It can easily be used as a starting point for creating a new application, the
 * comments identified with 'YOUR_JOB' indicates where and how you can customize.
 */

#include <stdbool.h>
#include <stdint.h>
#include <string.h>

#include "nordic_common.h"
#include "nrf.h"
#include "app_error.h"
#include "app_timer.h"
#include "fds.h"
#include "nrf_pwr_mgmt.h"
#include "nrf_log.h"
#include "nrf_log_ctrl.h"
#include "nrf_log_default_backends.h"

#include "app_ble.h"
#include "version.h"


/**@brief Function for the Timer initialization.
 *
 * @details Initializes the timer module. This creates and starts application timers.
 */
static void timers_init(void) {
    // Initialize timer module.
    ret_code_t err_code = app_timer_init();
    APP_ERROR_CHECK(err_code);

    // Create timers.

    /* YOUR_JOB: Create any timers to be used by the application.
                 Below is an example of how to create a timer.
                 For every new timer needed, increase the value of the macro APP_TIMER_MAX_TIMERS by
                 one.
       ret_code_t err_code;
       err_code = app_timer_create(&m_app_timer_id, APP_TIMER_MODE_REPEATED, timer_timeout_handler);
       APP_ERROR_CHECK(err_code); */
}


/**@brief Function for starting timers.
 */
static void application_timers_start(void) {
    /* YOUR_JOB: Start your timers. below is an example of how to start a timer.
       ret_code_t err_code;
       err_code = app_timer_start(m_app_timer_id, TIMER_INTERVAL, NULL);
       APP_ERROR_CHECK(err_code); */

}


/**@brief Function for putting the chip into sleep mode.
 *
 * @note This function will not return.
 */
static void sleep_mode_enter(void) {
    ret_code_t err_code;

    //err_code = bsp_indication_set(BSP_INDICATE_IDLE);
    //APP_ERROR_CHECK(err_code);

    // Prepare wakeup buttons.
    //err_code = bsp_btn_ble_sleep_mode_prepare();
    //APP_ERROR_CHECK(err_code);

    // Go to system-off mode (this function will not return; wakeup will cause a reset).
    err_code = sd_power_system_off();
    APP_ERROR_CHECK(err_code);
}


/**@brief Function for initializing the nrf log module.
 */
static void log_init(void) {
    ret_code_t err_code = NRF_LOG_INIT(NULL);
    APP_ERROR_CHECK(err_code);

    NRF_LOG_DEFAULT_BACKENDS_INIT();

    NRF_LOG_DEBUG("\r\n\r\n##### v%d.%d.%d compiled on %s at %s #####\r\n",
        VERSION_FW_MAJOR, VERSION_FW_MINOR, VERSION_FW_BUILD, VERSION_FW_BUILD_DATE, VERSION_FW_BUILD_TIME);
}


/**@brief Function for initializing power management.
 */
static void power_management_init(void) {
    ret_code_t err_code;
    err_code = nrf_pwr_mgmt_init();
    APP_ERROR_CHECK(err_code);
}


/**@brief Function for handling the idle state (main loop).
 *
 * @details If there is no pending log operation, then sleep until next the next event occurs.
 */
static void idle_state_handle(void) {
    if (NRF_LOG_PROCESS() == false) {
        nrf_pwr_mgmt_run();
    }
}


/**@brief Function for application main entry.
 */
int main(void) {
    bool erase_bonds = false;

    // Initialize.
    log_init();
    timers_init();
    power_management_init();
    ble_stack_init();
    gap_params_init();
    gatt_init();
    advertising_init();
    services_init();
    conn_params_init();
    peer_manager_init();

    // Start execution.
    NRF_LOG_INFO("Template example started.");
    NRF_LOG_FLUSH();
    application_timers_start();

    advertising_start(erase_bonds);
    NRF_LOG_DEBUG("Advertising");
    NRF_LOG_FLUSH();

    // Enter main loop.
    for (;;) {
        idle_state_handle();
    }
}


// If DEBUG is defined then app_error_weak.c module provides good and explanatory error handler.
#ifndef DEBUG
/**@brief Callback function for asserts in the SoftDevice.
 *
 * @details This function will be called in case of an assert in the SoftDevice.
 *
 * @warning This handler is an example only and does not fit a final product. You need to analyze
 *          how your product is supposed to react in case of Assert.
 * @warning On assert from the SoftDevice, the system can only recover on reset.
 *
 * @param[in] line_num   Line number of the failing ASSERT call.
 * @param[in] file_name  File name of the failing ASSERT call.
 */
void assert_nrf_callback(uint16_t line_num, const uint8_t *p_file_name) {
    /* 0xDEADBEEF is value used as error code on stack dump, can be used to identify stack location on stack unwind. */
    app_error_handler(0xDEADBEEF, line_num, p_file_name);
}
#endif


/**
 * @}
 */
