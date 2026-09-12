#include <cmrx/application.h>
#include "data.h"
#include <cmrx/ipc/notify.h>

uint32_t synchronization_object;

static int notification_thread(void * data)
{
    while (1) {
        notify_object(&synchronization_object);
    }
}

static int dormant_thread(void * data)
{
    while (1) {
        wait_for_object(&synchronization_object, 0);
    }
}

OS_APPLICATION_MMIO_RANGE(init, 0, 0);
OS_APPLICATION(init);
OS_THREAD_CREATE(init, notification_thread, NULL, 64);
OS_THREAD_CREATE(init, dormant_thread, NULL, 128);


