# BLE+USB template project for nRF52840

This project enables writing code in [CLion](https://www.jetbrains.com/clion/) (in my opinion one of the best C/C++ IDEs available - user friendly yet powerful and packed with useful features) while compiling and debugging it with [Keil µVision®](http://www2.keil.com/mdk5/uvision/) (in my opinion Keil® MDK  is one of the most comprehensive software development solution for Arm®-based microcontrollers, integrating powerful, feature rich compiler and debugger).

After many embedded projects, one can figure out that properly configuring CLion as a compiler (using GCC ARM Embedded) and sophisticated debugger is almost as hard as writing a lot of code in the µVision.

As a quick solution [CMake ⇄ µVision Synchronizer](https://github.com/bojanpotocnik/cmake-uvision-syncer) was created, however until that project is ready for the actual use, this template is used for new projects.

## Prerequisite

[Nordic's nRF5 SDK 15.0.2](http://developer.nordicsemi.com/nRF5_SDK/nRF5_SDK_v15.x.x/) shall be located in the `nRF5_SDK_15` subdirectory.

If the SDK is located somewhere else, symlink can be used.
As example, if using Windows 10 and the SDK is located in `G:\SDK\nRF5_SDK_15.2.0_9412b96` then the symlink is created with the command:

`mklink /D nRF5_SDK_15 G:\SDK\nRF5_SDK_15.2.0_9412b96`

## Build

Building is done using Keil uVision using the project file [ble_app_template.uvprojx](ble_app_template.uvprojx).
