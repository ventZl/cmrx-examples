Platform-independent examples for CMRX RTOS
===========================================

Examples in this subdirectory are platform-independent and can be built against any target which supports facilities required by the example.

To build example, first select a platform, navigate to platform subdirectory (cmrx-examples/<platform>) and run:

~~~~~
$ cd cmrx-examples/<platform>
$ cmake -DEXAMPLE=<example-name> -B build
$ cmake --build build
~~~~~

Some targets use CMake presets, thus `--preset` shall be used. For more documentation on available targets check the top-level README in examples repository.