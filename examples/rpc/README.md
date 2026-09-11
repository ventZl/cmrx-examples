---
title: 'Remote Procedure Call'
id: 2
---
{{< gh >}}

This example demonstrates how to create RPC service and how to call it from another process. In this example two processes are created. Instead it defines `service` variable which serves as RPC service. This service is then called from `client` process. This example shows:
* Declaration of shared interface `ServiceAPI`
* Use of `INSTANCE(this)` to refer to service instance
* Use of `IMPLEMENTATION_OF()` macro to declare implementation of `ServiceAPI` for specific service type
* Calling of RPC server via `rpc_call` macro

Notice that `rpcserver` process does not define any own threads. All RPC calls are processed in contexts of threads that started RPC call via `rpc_call` macro.

## Building and running

To build this example choose your target platform (more in Examples) and run following commands:

$ cd <target>
$ cmake [--preset=<preset>] -DEXAMPLE=rpc -B build
$ cmake --build build

Resulting binary will be called `rpc.elf` or `rpc`. To run it, follow instructions on running binaries on your selected target platform.


