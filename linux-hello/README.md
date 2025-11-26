Linux CMRX example
==================

This is a short example that demonstrates how to use CMRX hosted environment that runs on Linux. In this example a simple UART emulation is created that connects to UNIX socket accessible from the outside world.

There is a driver exposing RPC interface, that provides an interface to this device, (almost) completely unaware of the software-defined nature of the device.

And there's an application that listens to whatever was sent on the UART and echoes is back, once received.

Organization
------------

The code in `emu` subdirectory belongs to the emulated UART port. This code is not using any of CMRX services and is exposing only three objects:
* _R() and _W() are functions that emulate read- and write-triggered device response. This is to ease driver implementation as automatic triggering of code execution done just by pure reading or writing a piece of memory is non-trivial and slow in Linux
* UART0 is a variable that resembles register set of an UART peripheral. You can use above functions to read/write from/to this and trigger the emulated peripheral to act.

All the remaining code in `src` uses CMRX and does not use code of the Linux platform at all. Code in subdirectories of directory `src` creates two processes. One of them is actually a driver. These are using CMRX services exclusively. The `main.c` file is a startup file that creates the instance of emulated UART, performs the early initialization of "hardware" and then starts-up the CMRX operating system.
