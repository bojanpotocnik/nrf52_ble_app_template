//
// Created by Bojan on 29/01/2019.
//

#include "app_ble.h"
// nRF SDK
#include "nordic_common.h"
#include "nrf.h"
#include "app_error.h"
// nRF SDK Logging
#include "nrf_log.h"
#include "nrf_log_ctrl.h"
// SoftDevice Handler
#include "nrf_sdh.h"
#include "nrf_sdh_soc.h"
#include "nrf_sdh_ble.h"
// BLE
#include "ble.h"
#include "ble_hci.h"
#include "ble_config.h"
#include "ble_advdata.h"
#include "ble_advertising.h"
#include "ble_srv_common.h"
#include "ble_conn_params.h"
#include "ble_conn_state.h"
#include "nrf_ble_gatt.h"
#include "nrf_ble_qwr.h"
#include "peer_manager.h"
#include "peer_manager_handler.h"
// BLE Services
#include "ble_dis.h"
#include "ble_bas.h"
// Other application includes
#include "version.h"


#define APP_BLE_CONN_CFG_TAG 1              /**< A tag identifying the SoftDevice BLE configuration. */


static void on_ble_event(ble_evt_t const *p_ble_evt, void *p_context);

static void on_gatt_event(nrf_ble_gatt_t *p_gatt, nrf_ble_gatt_evt_t const *p_evt);

static void on_advertising_event(ble_adv_evt_t ble_adv_evt);

static void on_conn_params_event(ble_conn_params_evt_t *p_evt);

static void on_peer_manager_event(pm_evt_t const *p_evt);


NRF_BLE_GATT_DEF(m_gatt);                   /**< GATT module instance. */
NRF_BLE_QWR_DEF(m_qwr);                     /**< Context for the Queued Write module.*/

BLE_ADVERTISING_DEF(m_advertising);         /**< Advertising module instance. */

BLE_BAS_DEF(m_bas);                         /**< Battery Service instance. */
/* FIXME: Declare all other services structure your application is using */


// YOUR_JOB: Use UUIDs for service(s) used in your application.

/** Device's current transmit power level when in a connection.
 *  Supported values: -40dBm, -20dBm, -16dBm, -12dBm, -8dBm, -4dBm, 0dBm, +2dBm,
 *                    +3dBm, +4dBm, +5dBm, +6dBm, +7dBm and +8dBm.
 */
static int8_t m_tx_power = 0;


/** The UUIDs for service(s) used in the application.
 *  FIXME: Add your services.
 */
static ble_uuid_t m_adv_uuids[] = {
    {BLE_UUID_DEVICE_INFORMATION_SERVICE, BLE_UUID_TYPE_BLE}
};

/** Advertising configuration, initially initialized in advertising_init().
 */
static ble_advertising_init_t m_adv_init = {
    // Advertising data
    .advdata = {
        .name_type = BLE_ADVDATA_FULL_NAME,
        .include_appearance = true,
        .flags = BLE_GAP_ADV_FLAGS_LE_ONLY_GENERAL_DISC_MODE,
        .p_tx_power_level = &m_tx_power,
        .uuids_more_available = {
            .uuid_cnt = 0,
            .p_uuids = NULL
        },
        .uuids_complete = {
            .uuid_cnt = sizeof(m_adv_uuids) / sizeof(m_adv_uuids[0]),
            .p_uuids = m_adv_uuids
        },
        .uuids_solicited = {
            .uuid_cnt = 0,
            .p_uuids = NULL
        },
        .p_slave_conn_int = NULL,
        .p_manuf_specific_data = NULL,
        .p_service_data_array = NULL,
        .service_data_count = 0,
        .include_ble_device_addr = false
    },
    // Scan response data
    /*.srdata = {
        .name_type = BLE_ADVDATA_FULL_NAME,
        .short_name_len = 0,
        .include_appearance = true,
        .flags = BLE_GAP_ADV_FLAGS_LE_ONLY_GENERAL_DISC_MODE,
        .p_tx_power_level = NULL,
        .uuids_more_available = {
            .uuid_cnt = 0,
            .p_uuids = NULL
        },
        .uuids_complete = {
            .uuid_cnt = sizeof(m_adv_uuids) / sizeof(m_adv_uuids[0]),
            .p_uuids = m_adv_uuids
        },
        .uuids_solicited = {
            .uuid_cnt = 0,
            .p_uuids = NULL
        },
        .p_slave_conn_int = NULL,
        .p_manuf_specific_data = NULL,
        .p_service_data_array = NULL,
        .service_data_count = 0,
        .include_ble_device_addr = false
    },*/
    // Advertising modes and intervals
    .config = {
        .ble_adv_on_disconnect_disabled = false,
        .ble_adv_whitelist_enabled = false,
        .ble_adv_directed_high_duty_enabled = false,
        .ble_adv_directed_enabled = false,
        .ble_adv_fast_enabled = true,
        .ble_adv_slow_enabled = true,
        .ble_adv_directed_interval = 0,
        .ble_adv_directed_timeout = 0,
        .ble_adv_fast_interval = APP_ADV_FAST_INTERVAL,
        .ble_adv_fast_timeout = APP_ADV_FAST_DURATION,
        .ble_adv_slow_interval = APP_ADV_SLOW_INTERVAL,
        .ble_adv_slow_timeout = APP_ADV_SLOW_DURATION,
        .ble_adv_extended_enabled = false
    },
    // Event handler that will be called upon advertising events
    .evt_handler = on_advertising_event,
    // Error handler that will propagate internal errors to the main applications.
    .error_handler = app_error_handler_bare
};


static uint16_t m_conn_handle = BLE_CONN_HANDLE_INVALID;                        /**< Handle of the current connection. */


// region Public functions

void ble_stack_init(void) {
    ret_code_t err_code;

    err_code = nrf_sdh_enable_request();
    APP_ERROR_CHECK(err_code);

    // Configure the BLE stack using the default settings.
    // Fetch the start address of the application RAM.
    uint32_t ram_start = 0;
    err_code = nrf_sdh_ble_default_cfg_set(APP_BLE_CONN_CFG_TAG, &ram_start);
    APP_ERROR_CHECK(err_code);

    // Enable BLE stack.
    err_code = nrf_sdh_ble_enable(&ram_start);
    APP_ERROR_CHECK(err_code);

    // Register a handler for BLE events.
    NRF_SDH_BLE_OBSERVER(m_ble_observer, APP_BLE_OBSERVER_PRIO, on_ble_event, NULL);
}


void gap_params_init(void) {
    ret_code_t err_code;
    ble_gap_conn_params_t gap_conn_params = {0};
    ble_gap_conn_sec_mode_t sec_mode;

    BLE_GAP_CONN_SEC_MODE_SET_OPEN(&sec_mode);

    err_code = sd_ble_gap_device_name_set(&sec_mode,
                                          (const uint8_t *) DEVICE_NAME,
                                          strlen(DEVICE_NAME));
    APP_ERROR_CHECK(err_code);

    // TODO: Use an appearance value matching the application's use case.
    err_code = sd_ble_gap_appearance_set(BLE_APPEARANCE_UNKNOWN);
    APP_ERROR_CHECK(err_code);

    gap_conn_params.min_conn_interval = MIN_CONN_INTERVAL;
    gap_conn_params.max_conn_interval = MAX_CONN_INTERVAL;
    gap_conn_params.slave_latency = SLAVE_LATENCY;
    gap_conn_params.conn_sup_timeout = CONN_SUP_TIMEOUT;

    err_code = sd_ble_gap_ppcp_set(&gap_conn_params);
    APP_ERROR_CHECK(err_code);
}


void gatt_init(void) {
    ret_code_t err_code = nrf_ble_gatt_init(&m_gatt, on_gatt_event);
    APP_ERROR_CHECK(err_code);
}


void advertising_init(void) {
    ret_code_t err_code;

    err_code = ble_advertising_init(&m_advertising, &m_adv_init);
    APP_ERROR_CHECK(err_code);

    ble_advertising_conn_cfg_tag_set(&m_advertising, APP_BLE_CONN_CFG_TAG);

    // Set initial power level for advertising.
    // Advertising must first be initialized for handle to be valid.
    err_code = sd_ble_gap_tx_power_set(BLE_GAP_TX_POWER_ROLE_ADV, m_advertising.adv_handle, m_tx_power);
    APP_ERROR_CHECK(err_code);
}


void advertising_start(bool erase_bonds) {
    if (erase_bonds == true) {
        NRF_LOG_INFO("Erase bonds!");

        ret_code_t err_code = pm_peers_delete();
        APP_ERROR_CHECK(err_code);
        // Advertising is started by PM_EVT_PEERS_DELETED_SUCEEDED event
    }
    else {
        ret_code_t err_code = ble_advertising_start(&m_advertising, BLE_ADV_MODE_FAST);

        APP_ERROR_CHECK(err_code);
    }
}


void services_init(void) {
    ret_code_t err_code;
    uint16_t max_char_length = 0;

    // region Initialize Queued Write Module
    nrf_ble_qwr_init_t qwr_init = {0};

    qwr_init.error_handler = app_error_handler_bare;

    err_code = nrf_ble_qwr_init(&m_qwr, &qwr_init);
    APP_ERROR_CHECK(err_code);
    // endregion Initialize Queued Write Module

    // region Initialize Device Information Service
    ble_dis_init_t dis_init = {0};

    ble_srv_ascii_to_utf8(&dis_init.manufact_name_str, "info@bojanpotocnik.com");
    ble_srv_ascii_to_utf8(&dis_init.model_num_str, "Model Template");
    ble_srv_ascii_to_utf8(&dis_init.hw_rev_str, (char *) VERSION_HW);

    // Automatic MAC + UUID as a serial number.
    char ser_num_str[sizeof("001122334455-0011223344556677") + 1];
    sprintf(ser_num_str, "%04X%08X-%08X%08X",
            (uint16_t) NRF_FICR->DEVICEADDR[1], NRF_FICR->DEVICEADDR[0],
            NRF_FICR->DEVICEID[1], NRF_FICR->DEVICEID[0]);
    ble_srv_ascii_to_utf8(&dis_init.serial_num_str, ser_num_str);

    // Automatic version and build date/time as a FW Revision String.
    char fw_rev_str[sizeof("MMM.mmm.bbb ( )") + sizeof(VERSION_FW_BUILD_DATE) + sizeof(VERSION_FW_BUILD_TIME) + 1];
    sprintf(fw_rev_str, "%d.%d.%d (%s %s)",
            VERSION_FW_MAJOR, VERSION_FW_MINOR, VERSION_FW_BUILD,
            VERSION_FW_BUILD_DATE, VERSION_FW_BUILD_TIME);
    ble_srv_ascii_to_utf8(&dis_init.fw_rev_str, fw_rev_str);

    dis_init.dis_char_rd_sec = SEC_OPEN;

    // Check for maximum length
    max_char_length = MAX(max_char_length, dis_init.manufact_name_str.length);
    max_char_length = MAX(max_char_length, dis_init.model_num_str.length);
    max_char_length = MAX(max_char_length, dis_init.serial_num_str.length);
    max_char_length = MAX(max_char_length, dis_init.hw_rev_str.length);
    max_char_length = MAX(max_char_length, dis_init.fw_rev_str.length);
    max_char_length = MAX(max_char_length, dis_init.sw_rev_str.length);
    if (dis_init.p_sys_id != NULL) {
        max_char_length = MAX(max_char_length, sizeof(*dis_init.p_sys_id));
    }
    if (dis_init.p_reg_cert_data_list != NULL) {
        max_char_length = MAX(max_char_length, dis_init.p_reg_cert_data_list->list_len);
    }
    if (dis_init.p_pnp_id != NULL) {
        max_char_length = MAX(max_char_length, sizeof(*dis_init.p_pnp_id));
    }

    err_code = ble_dis_init(&dis_init);
    APP_ERROR_CHECK(err_code);
    // endregion Initialize Device Information Service

    // region Initialize Battery Service
    ble_bas_init_t bas_init = {0};

    bas_init.support_notification = true;
    bas_init.initial_batt_level = 99;

    bas_init.bl_rd_sec = SEC_OPEN;
    bas_init.bl_cccd_wr_sec = SEC_OPEN;
    bas_init.bl_report_rd_sec = SEC_OPEN;

    max_char_length = MAX(max_char_length, (uint8_t) 2);

    err_code = ble_bas_init(&m_bas, &bas_init);
    APP_ERROR_CHECK(err_code);
    // endregion Initialize Battery Service


    /* FIXME: Add code to initialize the services used by the application.
       ble_xxs_init_t                     xxs_init;
       ble_yys_init_t                     yys_init;

       // Initialize XXX Service.
       memset(&xxs_init, 0, sizeof(xxs_init));

       xxs_init.evt_handler                = NULL;
       xxs_init.is_xxx_notify_supported    = true;
       xxs_init.ble_xx_initial_value.level = 100;

       err_code = ble_bas_init(&m_xxs, &xxs_init);
       APP_ERROR_CHECK(err_code);

       // Initialize YYY Service.
       memset(&yys_init, 0, sizeof(yys_init));
       yys_init.evt_handler                  = on_yys_evt;
       yys_init.ble_yy_initial_value.counter = 0;

       err_code = ble_yy_service_init(&yys_init, &yy_init);
       APP_ERROR_CHECK(err_code);
     */


    /* Now, when all of the characteristics are added, maximum length can be retrieved and the
     * desired MTU size used for new connection can be updated to the length of the largest
     * characteristics value for for the maximum performance.
     *
     * The ATT_MTU size can be modified freely between BLE_GATT_ATT_MTU_DEFAULT and NRF_SDH_BLE_GATT_MAX_MTU_SIZE.
     * This value shall be updated before GATT initialization so all new connections will be updates to this
     * desired MTU size. For the maximum performance this values should be set to the maximum length of any
     * of the defined characteristic (but still limited to NRF_SDH_BLE_GATT_MAX_MTU_SIZE).
     *
     * There is also 1 byte used for the OP-code and 2 bytes for the Handle ID.
     */
    const uint16_t mtu_size = (uint16_t)
        MIN(MAX(max_char_length + 3, (BLE_GATT_ATT_MTU_DEFAULT)), (NRF_SDH_BLE_GATT_MAX_MTU_SIZE));
    NRF_LOG_DEBUG("Desired MTU size = %d (largest char. = %d)", mtu_size, max_char_length);

    err_code = nrf_ble_gatt_att_mtu_periph_set(&m_gatt, mtu_size);
    APP_ERROR_CHECK(err_code);
}


void conn_params_init(void) {
    ret_code_t err_code;
    ble_conn_params_init_t cp_init = {0};

    cp_init.p_conn_params = NULL;
    cp_init.first_conn_params_update_delay = FIRST_CONN_PARAMS_UPDATE_DELAY;
    cp_init.next_conn_params_update_delay = NEXT_CONN_PARAMS_UPDATE_DELAY;
    cp_init.max_conn_params_update_count = MAX_CONN_PARAMS_UPDATE_COUNT;
    cp_init.start_on_notify_cccd_handle = BLE_GATT_HANDLE_INVALID;
    cp_init.disconnect_on_fail = false;
    cp_init.evt_handler = on_conn_params_event;
    cp_init.error_handler = app_error_handler_bare;

    err_code = ble_conn_params_init(&cp_init);
    APP_ERROR_CHECK(err_code);
}


void peer_manager_init(void) {
    ret_code_t err_code;
    ble_gap_sec_params_t sec_param = {0};

    err_code = pm_init();
    APP_ERROR_CHECK(err_code);

    // Security parameters to be used for all security procedures.
    sec_param.bond = SEC_PARAM_BOND;
    sec_param.mitm = SEC_PARAM_MITM;
    sec_param.lesc = SEC_PARAM_LESC;
    sec_param.keypress = SEC_PARAM_KEYPRESS;
    sec_param.io_caps = SEC_PARAM_IO_CAPABILITIES;
    sec_param.oob = SEC_PARAM_OOB;
    sec_param.min_key_size = SEC_PARAM_MIN_KEY_SIZE;
    sec_param.max_key_size = SEC_PARAM_MAX_KEY_SIZE;
    sec_param.kdist_own.enc = 1;
    sec_param.kdist_own.id = 1;
    sec_param.kdist_peer.enc = 1;
    sec_param.kdist_peer.id = 1;

    err_code = pm_sec_params_set(&sec_param);
    APP_ERROR_CHECK(err_code);

    err_code = pm_register(on_peer_manager_event);
    APP_ERROR_CHECK(err_code);
}

// endregion Public functions



/**@brief Function for handling BLE events.
 *
 * @param[in]   p_ble_evt   Bluetooth stack event.
 * @param[in]   p_context   Unused.
 */
static void on_ble_event(ble_evt_t const *p_ble_evt, void *p_context) {
    ret_code_t err_code;

    switch (p_ble_evt->header.evt_id) {
        case BLE_GAP_EVT_CONNECTED: {
            // p_ble_evt->evt.gap_evt.params.connected
            NRF_LOG_INFO("Connected.");
            m_conn_handle = p_ble_evt->evt.gap_evt.conn_handle;
            err_code = nrf_ble_qwr_conn_handle_assign(&m_qwr, m_conn_handle);
            APP_ERROR_CHECK(err_code);
            break;
        }
        case BLE_GAP_EVT_DISCONNECTED: {
            // p_ble_evt->evt.gap_evt.params.disconnected
            NRF_LOG_INFO("Disconnected.");
            // LED indication will be changed when advertising starts.
            break;
        }
        case BLE_GAP_EVT_PHY_UPDATE_REQUEST: {
            // p_ble_evt->evt.gap_evt.params.phy_update_request
            NRF_LOG_DEBUG("PHY update request.");
            ble_gap_phys_t const phys = {
                .rx_phys = BLE_GAP_PHY_AUTO,
                .tx_phys = BLE_GAP_PHY_AUTO,
            };
            err_code = sd_ble_gap_phy_update(p_ble_evt->evt.gap_evt.conn_handle, &phys);
            APP_ERROR_CHECK(err_code);
            break;
        }
        case BLE_GATTC_EVT_TIMEOUT: {
            // Disconnect on GATT Client timeout event.
            NRF_LOG_DEBUG("GATT Client Timeout.");
            err_code = sd_ble_gap_disconnect(p_ble_evt->evt.gattc_evt.conn_handle,
                                             BLE_HCI_REMOTE_USER_TERMINATED_CONNECTION);
            APP_ERROR_CHECK(err_code);
            break;
        }
        case BLE_GATTS_EVT_TIMEOUT: {
            // Disconnect on GATT Server timeout event.
            NRF_LOG_DEBUG("GATT Server Timeout.");
            err_code = sd_ble_gap_disconnect(p_ble_evt->evt.gatts_evt.conn_handle,
                                             BLE_HCI_REMOTE_USER_TERMINATED_CONNECTION);
            APP_ERROR_CHECK(err_code);
            break;
        }
        case BLE_GAP_EVT_SEC_PARAMS_REQUEST: {
            // Pairing not supported.
            err_code = sd_ble_gap_sec_params_reply(m_conn_handle, BLE_GAP_SEC_STATUS_PAIRING_NOT_SUPP, NULL, NULL);
            APP_ERROR_CHECK(err_code);
            break;
        }
        case BLE_GATTS_EVT_SYS_ATTR_MISSING: {
            // No system attributes have been stored.
            err_code = sd_ble_gatts_sys_attr_set(m_conn_handle, NULL, 0, 0);
            APP_ERROR_CHECK(err_code);
            break;
        }
        case BLE_EVT_USER_MEM_REQUEST: {
            err_code = sd_ble_user_mem_reply(p_ble_evt->evt.gattc_evt.conn_handle, NULL);
            APP_ERROR_CHECK(err_code);
            break;
        }
        case BLE_GAP_EVT_DATA_LENGTH_UPDATE_REQUEST: {
            ble_gap_data_length_params_t dl_params = {0};
            // Clearing the struct will effectively set members to @ref BLE_GAP_DATA_LENGTH_AUTO.
            err_code = sd_ble_gap_data_length_update(p_ble_evt->evt.gap_evt.conn_handle, &dl_params, NULL);
            APP_ERROR_CHECK(err_code);
            break;
        }
        case BLE_GATTS_EVT_EXCHANGE_MTU_REQUEST: {
            const uint16_t mtu_requested = p_ble_evt->evt.gatts_evt.params.exchange_mtu_request.client_rx_mtu;
            NRF_LOG_DEBUG("Exchange MTU Request (to %d for 0x%x)", mtu_requested, m_conn_handle);

            err_code = sd_ble_gatts_exchange_mtu_reply(p_ble_evt->evt.gatts_evt.conn_handle, mtu_requested);
            APP_ERROR_CHECK(err_code);
            break;
        }
        default:
            // No implementation needed.
            break;
    }
}


/**@brief Function for handling events from the GATT library.
 */
static void on_gatt_event(nrf_ble_gatt_t *p_gatt, nrf_ble_gatt_evt_t const *p_evt) {
    switch (p_evt->evt_id) {
        case NRF_BLE_GATT_EVT_ATT_MTU_UPDATED: {
            NRF_LOG_INFO("ATT MTU updated (central %d, periph. %d) to %d B on connection 0x%x",
                         p_gatt->att_mtu_desired_central, p_gatt->att_mtu_desired_periph,
                         p_evt->params.att_mtu_effective, p_evt->conn_handle);
            // Note that the actual payload length is att_mtu_effective - Op. Code length (1) - Handle length (2).
            break;
        }

        case NRF_BLE_GATT_EVT_DATA_LENGTH_UPDATED:
            NRF_LOG_INFO("ATT data length updated to %u B on connection 0x%x",
                         p_evt->params.data_length, p_evt->conn_handle);
            break;
    }

    // TODO: Call any service-specific GATT event handler or update their MTU/data sizes.
    // ble_xxx_on_gatt_evt(&m_xxx, p_evt);
}


/**@brief Function for handling advertising events.
 *
 * @details This function will be called for advertising events which are passed to the application.
 *
 * @param[in] ble_adv_evt  Advertising event.
 */
static void on_advertising_event(ble_adv_evt_t ble_adv_evt) {
    // uint32_t err_code;

    switch (ble_adv_evt) {
        case BLE_ADV_EVT_FAST:
            //err_code = bsp_indication_set(BSP_INDICATE_ADVERTISING);
            //APP_ERROR_CHECK(err_code);
            break;

        case BLE_ADV_EVT_IDLE:
            //sleep_mode_enter();
            break;

        default:
            break;
    }
}


/**@brief Function for handling the Connection Parameters Module.
 *
 * @details This function will be called for all events in the Connection Parameters Module which
 *          are passed to the application.
 *          @note All this function does is to disconnect. This could have been done by simply
 *                setting the disconnect_on_fail config parameter, but instead we use the event
 *                handler mechanism to demonstrate its use.
 *
 * @param[in] p_evt  Event received from the Connection Parameters Module.
 */
static void on_conn_params_event(ble_conn_params_evt_t *p_evt) {
    ret_code_t err_code;

    if (p_evt->evt_type == BLE_CONN_PARAMS_EVT_FAILED) {
        err_code = sd_ble_gap_disconnect(m_conn_handle, BLE_HCI_CONN_INTERVAL_UNACCEPTABLE);
        APP_ERROR_CHECK(err_code);
    }
}


/**@brief Function for handling Peer Manager events.
 *
 * @param[in] p_evt  Peer Manager event.
 */
static void on_peer_manager_event(pm_evt_t const *p_evt) {
    pm_handler_on_pm_evt(p_evt);
    pm_handler_flash_clean(p_evt);

    switch (p_evt->evt_id) {
        case PM_EVT_PEERS_DELETE_SUCCEEDED:
            advertising_start(false);
            break;

        default:
            break;
    }
}


/**@brief Function for handling the YYY Service events.
 * YOUR_JOB implement a service handler function depending on the event the service you are using can generate
 *
 * @details This function will be called for all YY Service events which are passed to
 *          the application.
 *
 * @param[in]   p_yy_service   YY Service structure.
 * @param[in]   p_evt          Event received from the YY Service.
 *
 *
static void on_yys_evt(ble_yy_service_t     * p_yy_service,
                       ble_yy_service_evt_t * p_evt)
{
    switch (p_evt->evt_type)
    {
        case BLE_YY_NAME_EVT_WRITE:
            APPL_LOG("[APPL]: charact written with value %s. ", p_evt->params.char_xx.value.p_str);
            break;

        default:
            // No implementation needed.
            break;
    }
}
*/




