/**
 * @file    version.h
 * @author  Bojan Potočnik <info@bojanpotocnik.com>
 * @date    29 Jan 2019
 * @brief   Version information

 * This file contains date and time information about latest (re)build.
 */

#ifndef VERSION_H_INCLUDED
#define VERSION_H_INCLUDED


static const unsigned char VERSION_HW[] = "TemplateHW v1.0";
/* Hardware version number is only checked in DFU bootloader to match exactly,
 * therefore increasing number is not important. As currently string is used
 * as a hardware version descriptor, the following Python code is used to
 * calculate integer version of the HW version (yes, it is true that hash()
 * function uses random seed, however the VERSION_HW_INT is hardcoded in the
 * update FW binary):
 * > VERSION_HW = "TemplateHW v1.0"
 * > hash(VERSION_HW) % 0x7FFFFFFF
 */
static const unsigned int VERSION_HW_INT = 967924031ul;


static const unsigned char VERSION_FW_MAJOR = 1;
static const unsigned char VERSION_FW_MINOR = 0;
static const unsigned char VERSION_FW_BUILD = 0;
/* Application/Firmware version is checked in the DFU bootloader to prevent
 * downgrade of the application version. Therefore it must match predefined
 * algorithm which is also used when generating DFU .zip file on the PC.
 */
static const unsigned int VERSION_FW_INT = 10000ul * VERSION_FW_MAJOR + 100ul * VERSION_FW_MINOR + VERSION_FW_BUILD;


/* FW Version Change Log:
 *
 * 1.0.0
 *  - Working on PCA10056 board.
 */


/**@brief Compiler build time in format "??:??:??"
 */
extern const char VERSION_FW_BUILD_TIME[9];

/**@brief Compiler build date in format "??? ?? ????"
 */
extern const char VERSION_FW_BUILD_DATE[12];


#endif /* VERSION_H_INCLUDED */
