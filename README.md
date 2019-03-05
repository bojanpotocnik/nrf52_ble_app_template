# BLE+USB template project for nRF52840

This project enables writing code in [CLion](https://www.jetbrains.com/clion/) (in my opinion one of the best C/C++ IDEs available - user friendly yet powerful and packed with useful features) while compiling and debugging it with [Keil µVision®](http://www2.keil.com/mdk5/uvision/) (in my opinion Keil® MDK  is one of the most comprehensive software development solution for Arm®-based microcontrollers, integrating powerful, feature rich compiler and debugger).

After many embedded projects, one can figure out that properly configuring CLion as a compiler (using GCC ARM Embedded) and sophisticated debugger is almost as hard as writing a lot of code in the µVision.

As a quick solution [CMake ⇄ µVision Synchronizer](https://github.com/bojanpotocnik/cmake-uvision-syncer) was created, however until that project is ready for the actual use, this template is used for new projects.


## Prerequisite

#### Nordic's nRF5 SDK
[Nordic's nRF5 SDK 15.0.2](http://developer.nordicsemi.com/nRF5_SDK/nRF5_SDK_v15.x.x/) shall be located in the `nRF5_SDK_15` subdirectory.

If the SDK is located somewhere else, symlink can be used.
As example, if using Windows 10 and the SDK is located in `G:\SDK\nRF5_SDK_15.2.0_9412b96` then the symlink is created with the command:

`mklink /D nRF5_SDK_15 G:\SDK\nRF5_SDK_15.2.0_9412b96`

#### ARM Compiler paths configuration for CMake
Machine-specific CMake file _[environment.cmake.template](environment.cmake.template)_ shall be copied to _environment.cmake_ and edited according to the host machine and AMR Compiler installation.


## Build

Building is done using Keil uVision using the project file [ble_app_template.uvprojx](ble_app_template.uvprojx).


## Downloading and running

As the _ble_app_template.uv**opt**x_ file is excluded from this repository, the debugger settings are also lost
 (they are per-user-hardware specific anyway).
Take note that when the debugger is selected in µVision (under _Options for Target..._ → _Debug_) one should also
 tick _Download and Run_ checkbox in _Download Function_ section on _Flash Download_ tab in the debugger settings.
 This checkbox is not enabled by default, but can cause _a lot_ of frustration when just pressing _Download_ button and wondering why the program does not work, despite being identical to example project.
