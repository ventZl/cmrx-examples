#include <cmrx/application.h>

int app_main(void * data)
{
    while (1) {
    }
}

OS_APPLICATION_MMIO_RANGE(app, 0, 0);
OS_APPLICATION(app);
OS_THREAD_CREATE(app, app_main, NULL, 64);
