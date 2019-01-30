/* The SDK does not include system include files if build is cross-platform build.
 * Proper toolchain can be defined in the CMake, but that requires more effort and complications.
 * As a workaround this file is included with
 *  `add_definitions(-include cmake_cross_platform.h)`
 * in the CMakeLists.txt to include it in every source file.
 *
 * The following is copied from nRF5_SDK_15/components/modules/nrfx/mdk/nrf.h,
 * undef's are added to prevent not-including the files.
 *
 * Include guards are not required as this file does not define anything,
 * but it shall always un-define specified defines.
 */

#if defined(_WIN32)
/* Do not include nrf specific files when building for PC host */
#undef _WIN32
#endif /* _WIN32 */

#if defined(__unix)
/* Do not include nrf specific files when building for PC host */
#undef __unix
#endif /* __unix */

#if defined(__APPLE__)
/* Do not include nrf specific files when building for PC host */
#undef __APPLE__
#endif /* __APPLE__ */


/* Include all ARM and nRF system files. */
