---
title: 'Shared Memory'
id: 3
---
{{< gh >}}

This example demonstrates how to share memory between two processes. In CMRX, unconditional sharing of memory is not possible. Memory can be shared only during RPC call execution. This example builds on [RPC example](../rpc). In order to share variable with function called via RPC, mark this variable as `SHARED`. This example shows:
* Use of `SHARED` to determine variables that are shared with RPC servers

## Building and running

To build this example choose your target platform (more in Examples) and run following commands:

~~~
$ cd <target>
$ cmake [--preset=<preset>] -DEXAMPLE=shared_memory -B build
$ cmake --build build
~~~

Resulting binary will be called `shared_memory.elf` or `shared_memory`. To run it, follow instructions on running binaries on your selected target platform.

## See also

* [Reference manual - Sharing Memory](/documentation/ipc/#shared-memory)
* [API documentation - Shared Memory](/documentation/api/shared/)
