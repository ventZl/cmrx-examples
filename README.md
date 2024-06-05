# cmrx-examples
Examples of CMRX use

This repository contains simple examples of CMRX use. You can use them to understand how CMRX is being used in your project.

Each subdirectory contains one independent project that uses CMRX.

This repository submodules CMRX repository and repositories needed to build some of examples, so make sure to run:

~~~~~~~~~~~~
git submodule update --init --recursive
~~~~~~~~~~~~

In order to build any of the examples, enter the subdirectory of the example and run:

~~~~~~~~~~~~
mkdir build
cd build && cmake ..
make -j
~~~~~~~~~~~~

It is the nature of CMRX build, that you may see a following message in the build output:
~~~~~~~~~~~~
Updating linker script for correct MPU operation
Linker script updated, please rebuild the target...
~~~~~~~~~~~~
This is not an error. CMRX builds are two-pass. The first build will determine size of the data
that has to be protected by MPU and the second build will adjust MPU settings according to it.

If you see this message, then no executable is generated. Run the build again to obtain
the executable.
