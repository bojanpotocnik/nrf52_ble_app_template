//
// Created by Bojan on 29/01/2019.
//

#ifndef APP_BLE_H_INCLUDED
#define APP_BLE_H_INCLUDED

#include <stdbool.h>
#include "sdk_errors.h"


/**@brief Function for initializing the BLE stack.
 *
 * @details Initializes the SoftDevice and the BLE event interrupt.
 */
void ble_stack_init(void);

/**@brief Function for the GAP initialization.
 *
 * @details This function sets up all the necessary GAP (Generic Access Profile) parameters of the
 *          device including the device name, appearance, and the preferred connection parameters.
 */
void gap_params_init(void);

/**@brief Function for initializing the GATT module.
 */
void gatt_init(void);

/**@brief Function for initializing the Advertising functionality.
 */
void advertising_init(void);

/**@brief Function for initializing services that will be used by the application.
 */
void services_init(void);

/**@brief Function for initializing the Connection Parameters module.
 */
void conn_params_init(void);

/**@brief Function for the Peer Manager initialization.
 */
void peer_manager_init(void);


/**@brief Function for starting advertising.
 */
void advertising_start(bool erase_bonds);


#endif /* APP_BLE_H_INCLUDED */
