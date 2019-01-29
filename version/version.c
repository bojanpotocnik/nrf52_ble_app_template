/**
 * @file    version.c
 * @author  Bojan Potočnik <info@bojanpotocnik.com>
 * @date    29 Jan 2019
 * @brief   Version information

 * This file must be rebuilt every time to update variables.
 * This is usually done by adding "After Build" task to the compiler.
 */

#include "version.h"


const char VERSION_FW_BUILD_TIME[9] = __TIME__; /*< "??:??:??" */
const char VERSION_FW_BUILD_DATE[12] = __DATE__; /*< "??? ?? ????" */
