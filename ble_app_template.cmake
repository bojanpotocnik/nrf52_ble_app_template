# Made with CMake <> uVision project file synchronizer# https://github.com/bojanpotocnik/cmake-uvision-syncer


# Common definitions
set(DEFINES_COMMON
	-DCONFIG_GPIO_AS_PINRESET
	-DFLOAT_ABI_HARD
	-DNRF52840_XXAA
	-DNRF_SD_BLE_API_VERSION=6
	-DS140
	-DSOFTDEVICE_PRESENT
	-DSWI_DISABLE0
	-D__HEAP_SIZE=8192
	-D__STACK_SIZE=8192
)

# Assembler specific definitions
set(DEFINES_ASM
)

# C specific definitions
set(DEFINES_C
)


# Common un-defines
set(UNDEFINES_COMMON
	
)

# Assembler specific un-defines
set(UNDEFINES_ASM
)

# C specific un-defines
set(UNDEFINES_C
)


# Common include directories
set(INCLUDE_DIRS_COMMON
	nRF5_SDK_15/components
	nRF5_SDK_15/components/ble/ble_advertising
	nRF5_SDK_15/components/ble/ble_dtm
	nRF5_SDK_15/components/ble/ble_racp
	nRF5_SDK_15/components/ble/ble_services/ble_ancs_c
	nRF5_SDK_15/components/ble/ble_services/ble_ans_c
	nRF5_SDK_15/components/ble/ble_services/ble_bas
	nRF5_SDK_15/components/ble/ble_services/ble_bas_c
	nRF5_SDK_15/components/ble/ble_services/ble_cscs
	nRF5_SDK_15/components/ble/ble_services/ble_cts_c
	nRF5_SDK_15/components/ble/ble_services/ble_dfu
	nRF5_SDK_15/components/ble/ble_services/ble_dis
	nRF5_SDK_15/components/ble/ble_services/ble_gls
	nRF5_SDK_15/components/ble/ble_services/ble_hids
	nRF5_SDK_15/components/ble/ble_services/ble_hrs
	nRF5_SDK_15/components/ble/ble_services/ble_hrs_c
	nRF5_SDK_15/components/ble/ble_services/ble_hts
	nRF5_SDK_15/components/ble/ble_services/ble_ias
	nRF5_SDK_15/components/ble/ble_services/ble_ias_c
	nRF5_SDK_15/components/ble/ble_services/ble_lbs
	nRF5_SDK_15/components/ble/ble_services/ble_lbs_c
	nRF5_SDK_15/components/ble/ble_services/ble_lls
	nRF5_SDK_15/components/ble/ble_services/ble_nus
	nRF5_SDK_15/components/ble/ble_services/ble_nus_c
	nRF5_SDK_15/components/ble/ble_services/ble_rscs
	nRF5_SDK_15/components/ble/ble_services/ble_rscs_c
	nRF5_SDK_15/components/ble/ble_services/ble_tps
	nRF5_SDK_15/components/ble/common
	nRF5_SDK_15/components/ble/nrf_ble_gatt
	nRF5_SDK_15/components/ble/nrf_ble_qwr
	nRF5_SDK_15/components/ble/peer_manager
	nRF5_SDK_15/components/boards
	nRF5_SDK_15/components/drivers_nrf/usbd
	nRF5_SDK_15/components/libraries/atomic
	nRF5_SDK_15/components/libraries/atomic_fifo
	nRF5_SDK_15/components/libraries/atomic_flags
	nRF5_SDK_15/components/libraries/balloc
	nRF5_SDK_15/components/libraries/bootloader/ble_dfu
	nRF5_SDK_15/components/libraries/bsp
	nRF5_SDK_15/components/libraries/button
	nRF5_SDK_15/components/libraries/cli
	nRF5_SDK_15/components/libraries/crc16
	nRF5_SDK_15/components/libraries/crc32
	nRF5_SDK_15/components/libraries/crypto
	nRF5_SDK_15/components/libraries/csense
	nRF5_SDK_15/components/libraries/csense_drv
	nRF5_SDK_15/components/libraries/delay
	nRF5_SDK_15/components/libraries/ecc
	nRF5_SDK_15/components/libraries/experimental_section_vars
	nRF5_SDK_15/components/libraries/experimental_task_manager
	nRF5_SDK_15/components/libraries/fds
	nRF5_SDK_15/components/libraries/fstorage
	nRF5_SDK_15/components/libraries/gfx
	nRF5_SDK_15/components/libraries/gpiote
	nRF5_SDK_15/components/libraries/hardfault
	nRF5_SDK_15/components/libraries/hci
	nRF5_SDK_15/components/libraries/led_softblink
	nRF5_SDK_15/components/libraries/log
	nRF5_SDK_15/components/libraries/log/src
	nRF5_SDK_15/components/libraries/low_power_pwm
	nRF5_SDK_15/components/libraries/mem_manager
	nRF5_SDK_15/components/libraries/memobj
	nRF5_SDK_15/components/libraries/mpu
	nRF5_SDK_15/components/libraries/mutex
	nRF5_SDK_15/components/libraries/pwm
	nRF5_SDK_15/components/libraries/pwr_mgmt
	nRF5_SDK_15/components/libraries/queue
	nRF5_SDK_15/components/libraries/ringbuf
	nRF5_SDK_15/components/libraries/scheduler
	nRF5_SDK_15/components/libraries/sdcard
	nRF5_SDK_15/components/libraries/sensorsim
	nRF5_SDK_15/components/libraries/slip
	nRF5_SDK_15/components/libraries/sortlist
	nRF5_SDK_15/components/libraries/spi_mngr
	nRF5_SDK_15/components/libraries/stack_guard
	nRF5_SDK_15/components/libraries/strerror
	nRF5_SDK_15/components/libraries/svc
	nRF5_SDK_15/components/libraries/timer
	nRF5_SDK_15/components/libraries/twi_mngr
	nRF5_SDK_15/components/libraries/twi_sensor
	nRF5_SDK_15/components/libraries/usbd
	nRF5_SDK_15/components/libraries/usbd/class/audio
	nRF5_SDK_15/components/libraries/usbd/class/cdc
	nRF5_SDK_15/components/libraries/usbd/class/cdc/acm
	nRF5_SDK_15/components/libraries/usbd/class/hid
	nRF5_SDK_15/components/libraries/usbd/class/hid/generic
	nRF5_SDK_15/components/libraries/usbd/class/hid/kbd
	nRF5_SDK_15/components/libraries/usbd/class/hid/mouse
	nRF5_SDK_15/components/libraries/usbd/class/msc
	nRF5_SDK_15/components/libraries/util
	nRF5_SDK_15/components/nfc/ndef/conn_hand_parser
	nRF5_SDK_15/components/nfc/ndef/conn_hand_parser/ac_rec_parser
	nRF5_SDK_15/components/nfc/ndef/conn_hand_parser/ble_oob_advdata_parser
	nRF5_SDK_15/components/nfc/ndef/conn_hand_parser/le_oob_rec_parser
	nRF5_SDK_15/components/nfc/ndef/connection_handover/ac_rec
	nRF5_SDK_15/components/nfc/ndef/connection_handover/ble_oob_advdata
	nRF5_SDK_15/components/nfc/ndef/connection_handover/ble_pair_lib
	nRF5_SDK_15/components/nfc/ndef/connection_handover/ble_pair_msg
	nRF5_SDK_15/components/nfc/ndef/connection_handover/common
	nRF5_SDK_15/components/nfc/ndef/connection_handover/ep_oob_rec
	nRF5_SDK_15/components/nfc/ndef/connection_handover/hs_rec
	nRF5_SDK_15/components/nfc/ndef/connection_handover/le_oob_rec
	nRF5_SDK_15/components/nfc/ndef/generic/message
	nRF5_SDK_15/components/nfc/ndef/generic/record
	nRF5_SDK_15/components/nfc/ndef/launchapp
	nRF5_SDK_15/components/nfc/ndef/parser/message
	nRF5_SDK_15/components/nfc/ndef/parser/record
	nRF5_SDK_15/components/nfc/ndef/text
	nRF5_SDK_15/components/nfc/ndef/uri
	nRF5_SDK_15/components/nfc/t2t_lib
	nRF5_SDK_15/components/nfc/t2t_lib/hal_t2t
	nRF5_SDK_15/components/nfc/t2t_parser
	nRF5_SDK_15/components/nfc/t4t_lib
	nRF5_SDK_15/components/nfc/t4t_lib/hal_t4t
	nRF5_SDK_15/components/nfc/t4t_parser/apdu
	nRF5_SDK_15/components/nfc/t4t_parser/cc_file
	nRF5_SDK_15/components/nfc/t4t_parser/hl_detection_procedure
	nRF5_SDK_15/components/nfc/t4t_parser/tlv
	nRF5_SDK_15/components/softdevice/common
	nRF5_SDK_15/components/softdevice/s140/headers
	nRF5_SDK_15/components/softdevice/s140/headers/nrf52
	nRF5_SDK_15/external/fprintf
	nRF5_SDK_15/external/segger_rtt
	nRF5_SDK_15/external/utf_converter
	nRF5_SDK_15/integration/nrfx
	nRF5_SDK_15/integration/nrfx/legacy
	nRF5_SDK_15/modules/nrfx
	nRF5_SDK_15/modules/nrfx/drivers/include
	nRF5_SDK_15/modules/nrfx/hal
	nRF5_SDK_15/modules/nrfx/mdk
	config
)

# Assembler specific include directories
set(INCLUDE_DIRS_ASM
)

# C specific include directories
set(INCLUDE_DIRS_C
	version
	ble
)


# Common source files
set(SOURCES_COMMON
)

# Assembler specific source files
set(SOURCES_ASM
	# RTE::Device
	RTE/Device/nRF52840_xxAA/arm_startup_nrf52840.s
)

# C specific source files
set(SOURCES_C
	# Application
	main.c
	version/version.c
	# Board Definition
	nRF5_SDK_15/components/boards/boards.c
	# Board Support
	nRF5_SDK_15/components/libraries/bsp/bsp.c
	nRF5_SDK_15/components/libraries/bsp/bsp_btn_ble.c
	# UTF8/UTF16 converter
	nRF5_SDK_15/external/utf_converter/utf.c
	# nRF_BLE
	nRF5_SDK_15/components/ble/peer_manager/auth_status_tracker.c
	nRF5_SDK_15/components/ble/common/ble_advdata.c
	nRF5_SDK_15/components/ble/ble_advertising/ble_advertising.c
	nRF5_SDK_15/components/ble/common/ble_conn_params.c
	nRF5_SDK_15/components/ble/common/ble_conn_state.c
	nRF5_SDK_15/components/ble/common/ble_srv_common.c
	nRF5_SDK_15/components/ble/peer_manager/gatt_cache_manager.c
	nRF5_SDK_15/components/ble/peer_manager/gatts_cache_manager.c
	nRF5_SDK_15/components/ble/peer_manager/id_manager.c
	nRF5_SDK_15/components/ble/nrf_ble_gatt/nrf_ble_gatt.c
	nRF5_SDK_15/components/ble/nrf_ble_qwr/nrf_ble_qwr.c
	nRF5_SDK_15/components/ble/peer_manager/peer_data_storage.c
	nRF5_SDK_15/components/ble/peer_manager/peer_database.c
	nRF5_SDK_15/components/ble/peer_manager/peer_id.c
	nRF5_SDK_15/components/ble/peer_manager/peer_manager.c
	nRF5_SDK_15/components/ble/peer_manager/peer_manager_handler.c
	nRF5_SDK_15/components/ble/peer_manager/pm_buffer.c
	nRF5_SDK_15/components/ble/peer_manager/security_dispatcher.c
	nRF5_SDK_15/components/ble/peer_manager/security_manager.c
	# nRF_Drivers
	nRF5_SDK_15/integration/nrfx/legacy/nrf_drv_clock.c
	nRF5_SDK_15/integration/nrfx/legacy/nrf_drv_uart.c
	nRF5_SDK_15/modules/nrfx/drivers/src/nrfx_clock.c
	nRF5_SDK_15/modules/nrfx/drivers/src/nrfx_gpiote.c
	nRF5_SDK_15/modules/nrfx/drivers/src/nrfx_power_clock.c
	nRF5_SDK_15/modules/nrfx/drivers/src/prs/nrfx_prs.c
	nRF5_SDK_15/modules/nrfx/drivers/src/nrfx_uart.c
	nRF5_SDK_15/modules/nrfx/drivers/src/nrfx_uarte.c
	# nRF_Libraries
	nRF5_SDK_15/components/libraries/button/app_button.c
	nRF5_SDK_15/components/libraries/util/app_error.c
	nRF5_SDK_15/components/libraries/util/app_error_handler_keil.c
	nRF5_SDK_15/components/libraries/util/app_error_weak.c
	nRF5_SDK_15/components/libraries/scheduler/app_scheduler.c
	nRF5_SDK_15/components/libraries/timer/app_timer.c
	nRF5_SDK_15/components/libraries/util/app_util_platform.c
	nRF5_SDK_15/components/libraries/crc16/crc16.c
	nRF5_SDK_15/components/libraries/fds/fds.c
	nRF5_SDK_15/components/libraries/hardfault/hardfault_implementation.c
	nRF5_SDK_15/components/libraries/util/nrf_assert.c
	nRF5_SDK_15/components/libraries/atomic_fifo/nrf_atfifo.c
	nRF5_SDK_15/components/libraries/atomic_flags/nrf_atflags.c
	nRF5_SDK_15/components/libraries/atomic/nrf_atomic.c
	nRF5_SDK_15/components/libraries/balloc/nrf_balloc.c
	nRF5_SDK_15/external/fprintf/nrf_fprintf.c
	nRF5_SDK_15/external/fprintf/nrf_fprintf_format.c
	nRF5_SDK_15/components/libraries/fstorage/nrf_fstorage.c
	nRF5_SDK_15/components/libraries/fstorage/nrf_fstorage_sd.c
	nRF5_SDK_15/components/libraries/memobj/nrf_memobj.c
	nRF5_SDK_15/components/libraries/pwr_mgmt/nrf_pwr_mgmt.c
	nRF5_SDK_15/components/libraries/ringbuf/nrf_ringbuf.c
	nRF5_SDK_15/components/libraries/experimental_section_vars/nrf_section_iter.c
	nRF5_SDK_15/components/libraries/strerror/nrf_strerror.c
	nRF5_SDK_15/components/libraries/sensorsim/sensorsim.c
	# nRF_Log
	nRF5_SDK_15/components/libraries/log/src/nrf_log_backend_rtt.c
	nRF5_SDK_15/components/libraries/log/src/nrf_log_backend_serial.c
	nRF5_SDK_15/components/libraries/log/src/nrf_log_backend_uart.c
	nRF5_SDK_15/components/libraries/log/src/nrf_log_default_backends.c
	nRF5_SDK_15/components/libraries/log/src/nrf_log_frontend.c
	nRF5_SDK_15/components/libraries/log/src/nrf_log_str_formatter.c
	# nRF_Segger_RTT
	nRF5_SDK_15/external/segger_rtt/SEGGER_RTT.c
	nRF5_SDK_15/external/segger_rtt/SEGGER_RTT_Syscalls_KEIL.c
	nRF5_SDK_15/external/segger_rtt/SEGGER_RTT_printf.c
	# nRF_SoftDevice
	nRF5_SDK_15/components/softdevice/common/nrf_sdh.c
	nRF5_SDK_15/components/softdevice/common/nrf_sdh_ble.c
	nRF5_SDK_15/components/softdevice/common/nrf_sdh_soc.c
	# Application - BLE
	ble/app_ble.c
	# RTE::Device
	RTE/Device/nRF52840_xxAA/system_nrf52840.c
)


# Other files
set(OTHER_FILES
	# Application
	config/sdk_config.h
)
