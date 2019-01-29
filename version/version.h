/**
 * @file    version.h
 * @author  Bojan Potočnik <info@bojanpotocnik.com>
 * @date    29 Jan 2019
 * @brief   Version information

 * This file contains date and time information about latest (re)build.
 */

#ifndef VERSION_H_INCLUDED
#define VERSION_H_INCLUDED


static const unsigned char VERSION_FW_MAJOR = 1;
static const unsigned char VERSION_FW_MINOR = 0;
static const unsigned char VERSION_FW_BUILD = 0;

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
