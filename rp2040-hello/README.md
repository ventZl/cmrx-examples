RP2040 example running CMRX
===========================

This example demonstrates how to implement blinky using CMRX and RPi-Pico SDK.

Build instructions
------------------

Assuming you cloned this from git and actually ran git submodule update --init in the root
of this repository, build is rather straightforward. Make sure you have ARM cross-compile 
toolchain installed on your machine and it is present in the path (e.g. `arm-none-eabi-gcc`
can be found). Then use following commands:

~~~~~~~~~~~~~~~
cmake -B build .
cmake --build build -- -j
~~~~~~~~~~~~~~~

File `build/helloworld.elf` should be created. You can flash it into your Raspberry Pi Pico 
using debugger. If you don't have debug probe, then you can use the file `build/helloworld.uf2`
which can be flashed directly into Rasperry Pi Pico via USB port. Just hold the BOOTSEL button
while connecting your Pico to USB. It will appear as a USB stick. You can copy the 
`helloworld.uf2` there and it will be flashed automatically.


