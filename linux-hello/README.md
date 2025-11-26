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

Building
--------

Enter the subdirectory `linux-hello` of the repository, update git submodules and run:

~~~~~~~
cmake -B build 
cmake --build build
build/linux-hello
~~~~~~~

This will start the hosted instance of CMRX system running the application, driver and emulated UART peripheral. In the current working directory, new UNIX socket file will be created, called `uart0.sock`. You can attach `socat` to this socket like this:

~~~~~~~
socat -,rawer UNIX-SENDTO:uart0.sock,bind=uart0-receiver.sock,unlink-early=1
~~~~~~~

This command will pipe whatever you type on your keyboard directly into the socket. The data will be received by the emulated peripheral. Data reception will be signalled by emulated IRQ which will be caught by UART driver in CMRX userland. The data will be read from emulated peripheral and then accessed by the application via RPC. It will echo this data back the opposite way.

You have to run the socat from the same working directory as `linux-hello` is running otherwise the socket file won't be found.
