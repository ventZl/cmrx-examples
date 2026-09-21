---
title: Timers
id: 5
---
{{< gh >}}

This example demonstrates the use of periodic timers and delays. Basic difference between periodic timers and delays is that delays are one-shot while periodic timers fire until they are disabled. These timers also differ in way how they affect the running thread and in inherent properties. This example demonstrates:

1. How to use periodic timer using `setitimer`
2. How to use one-shot delay using `usleep`
3. That periodic timer doesn't drift while repeated delays do drift

## Building and running

To build this example choose your target platform (more in [Examples](/examples)) and run following commands:

~~~~~sh
$ cd <target>
$ cmake [--preset=<preset>] -DEXAMPLE=timers -B build
$ cmake --build build
~~~~~

Resulting binary will be called `timers.elf` or `timers`. To run it, follow instructions on running binaries on your selected target platform.

## See also

* [Reference manual - Processes](/documentation/timers/)
* [API documentation - Static Initialization](/documentation/api/timer/)
