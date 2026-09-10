---
title: Examples
draft: no
layout: category
---
Here are some examples showing how the CMRX-based ecosystem works. There is a [CMRX examples repository](https://github.com/ventZl/cmrx-examples) online which contains examples complete with hardware integration demonstrated using STM32 hardware.

Examples in this section demonstrate how individual parts of CMRX work. They can be used to quickly discover how certain concepts in CMRX work. For a detailed step-by-step guide on how to create new CMRX-based project from scratch, follow getting started guides:
* [Get started with STM32](https://cmrxrtos.org/get-started/stm32/)
* [Get started with Raspberry Pi RP2040](https://cmrxrtos.org/get-started/rp2040/)

## Building and running

Provided examples depend on minimal set of tools in order to be built:
* CMake at least version 3.22
* Python 3
* GNU Make or Ninja
* GNU compiler toolchain for target platform (see below for details)

Examples are written to be platform-independent, so you can build any example against one of provided targets. CMRX itself is designed to be platform-independent and your application code can be so too. In order to build any example, first choose target for which the example will be built. As of now there are three targets:

* `stm32f4` - ST Microelectronics STM32F4-based target, suitable for running in Renode emulator
* `rp2350` - Raspberry Pi's RP2350-based target, suitable for running on Pico development boards
* `linux` - target implementing hosted execution on Linux, MacOS or WSL with virtualized peripherals

Each of targets resides in examples repository subdirectory named after target, containing top-level `CMakeLists.txt` file and itself is a root of a project. To select which example shall be built, pass `EXAMPLE` argument to CMake, such as:

~~~~~~bash
$ cd cmrx-examples/linux
$ cmake [--preset=<preset>] -DEXAMPLE=hello_world --B build
$ cmake --build build
~~~~~~

This will select example `hello_world` to be built for hosted execution on POSIX-compatible machine. When example is built, a binary having same name as example will be created. In the example above, file `build/hello_world` will be created which is a Linux executable and can be launched directly.

Note that some targets may depend on presets and that `--preset` option is mandatory. See below for details on which presets are available and if they are mandatory.

### Linux target

Linux hosted target generates ELF executables that can be executed directly on machine they were built on. The target provides virtualized peripherals external applications can interact with similarly to peripherals Renode simulates. In this case, system is not simulated. CMRX is compiled as native host binary, just peripherals themselves are virtualized.

Building this target requires compiler for native platform.

### STM32 target

STM32 target generates ELF firmware images which are directly executable on target hardware and/or can be executed in Renode simulator.

This project is generated using recent CubeMX tool which moves toolchain configuration into presets. `--preset` switch is mandatory, otherwise toolchain won't be detected. In order to build this target, `arm-none-eabi` toolchain should be present in `PATH`.

### RP2350 target

RP2350 target generates ELF and UF2 firmware images which can be directly executed on target hardware. In order to build this target, `arm-none-eabi` toolchain should be present in `PATH`.

