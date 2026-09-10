#include <cmrx/application.h>
#include "data.h"

int thread_main(void * data)
{
    struct ThreadData * var = (struct ThreadData *) data;
    while (1) {
        var->counter++;
    }
}

static struct ThreadData thread_data = { 0 };

OS_APPLICATION_MMIO_RANGE(app, 0, 0);
OS_APPLICATION(app);
OS_THREAD_CREATE(app, thread_main, &thread_data, 64);

