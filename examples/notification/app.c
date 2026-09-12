#include <cmrx/application.h>
#include "data.h"
#include <cmrx/ipc/notify.h>

static int waiting_thread(void * data)
{
    while (1) {
        wait_for_object(&synchronization_object, 0);
    }
}

OS_APPLICATION_MMIO_RANGE(app, 0, 0);
OS_APPLICATION(app);
OS_THREAD_CREATE(app, waiting_thread, NULL, 16);

