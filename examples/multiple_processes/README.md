---
title: 'Multiple processes'
id: 1
---
{{< gh >}}

This example demonstrates how to create additional process. In this example two processes are created each with its own thread. Each of processes has its own variable which can be only access by the code running in threads created by that particular process. This example shows:
* Declaration of secondary process by using another call to `add_application` in CMakeLists.txt
* Defining process by using `OS_APPLICATION` in `init.c`
* Adding process into firmware by including it into `target_add_applications` call
* Process can have any name that is valid C symbol as long as CMake and C portion agree on it

Also note that both processes call their thread entrypoint function `thread_main` and variable holding thread state `thread_data`. This is possible because thread entrypoint function is not referenced by its name from outside of the process and thus it can be defined as `static`. Nothing outside the process needs to know it exists.

Despite same names, both variables and functions are different objects.

## Building and running

To build this example choose your target platform (more in Examples) and run following commands:

$ cd <target>
$ cmake [--preset=<preset>] -DEXAMPLE=multiple_processes -B build
$ cmake --build build

Resulting binary will be called `multiple_processes.elf` or `multiple_processes`. To run it, follow instructions on running binaries on your selected target platform.

