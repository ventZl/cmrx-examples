---
title: Notification
id: 4
---
{{< gh >}}


This example demonstrates how two threads can synchronize using notifications. The example creates three threads running in two different processes. Threads have different priorities so that `waiting_thread` will be executed the first. It gets blocked waiting for notification, which allows `notifier_thread` to perform notification. These two threads reside in different processes but that doesn't prevent notification from being delivered. There's also third thread `dormant_thread` which is waiting for notification on the same object as `waiting_thread`. As this thread has lower priority than `waiting_thread`, it will never receive the notification. If there are multiple waiting threads, then the notification is delivered to the thread with highest priority.

This example shows how:

1. Wait for a notification on object
2. Send a notification
3. Notifications deal with priority if there are multiple waiters
4. Notifications aren't limited by memory protection domains

Notice how "notification object" is just a plain 32-bit integer variable. In fact, notification objects are just a convenient way how to generate uniquely random ID. If you wish, you could use hardcoded numbers to identify "objects" but doing so creates burden of managing IDs and/or risk of their duplication. This also answers why notifications are not blocked by memory protection boundaries.

## Building and running

To build this example choose your target platform (more in [Examples](/examples)) and run following commands:

~~~~~sh
$ cd <target>
$ cmake [--preset=<preset>] -DEXAMPLE=notification -B build
$ cmake --build build
~~~~~

Resulting binary will be called `notification.elf` or `notification`. To run it, follow instructions on running binaries on your selected target platform.

## See also

* [Reference manual - Notifications](/documentation/ipc/#notifications)
* [API documentation - Notifications](/documentation/api/notify/)
