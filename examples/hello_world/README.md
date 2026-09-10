---
title: Hello World
id: 0
---
{{< gh >}}


This example demonstrates the simplest possible application written for CMRX RTOS. This application will do nothing (as opposed to typical Hello World of embedded development, which blinks LED). This example shows how to:

1. Declare userspace application using `OS_APPLICATION` and `OS_APPLICATION_MMIO_RANGE` macros
2. Auto-Create application thread during system startup using `OS_THREAD_CREATE` macro
3. How a thread entry-point function looks like
4. How to add an application to firmware

## Basic Application Code

Here's the simplest possible CMRX application:

~~~c
#include <cmrx/application.h>

int app_main(void * data)
{
    while (1) {
    }
}

OS_APPLICATION_MMIO_RANGE(app, 0, 0)
OS_APPLICATION(app)
OS_THREAD_CREATE(app, app_main, NULL, 64)
~~~

This application can be built and added to firmware using following snipet of CMake:

~~~cmake
add_application(app app.c)
target_add_applications(firmware app)
~~~

Note that `app` passed as argument to both `OS_APPLICATION` macro in C source code and `add_application` function in CMake script must match, otherwise the build will fail.

## Building and running

To build this example choose your target platform (more in [Examples](/examples)) and run following commands:

~~~~~sh
$ cd <target>
$ cmake [--preset=<preset>] -DEXAMPLE=hello_world -B build
$ cmake --build build
~~~~~

Resulting binary will be called `hello_world.elf` or `hello_world`. To run it, follow instructions on running binaries on your selected target platform.
