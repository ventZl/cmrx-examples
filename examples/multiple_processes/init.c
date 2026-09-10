#include <cmrx/application.h>
#include "data.h"

static int thread_main(void * data)
{
    struct ThreadData * var = (struct ThreadData *) data;
    while (1) {
        var->counter++;
    }
}

static struct ThreadData thread_data = { 0 };

OS_APPLICATION_MMIO_RANGE(init, 0, 0);
OS_APPLICATION(init);
OS_THREAD_CREATE(init, thread_main, &thread_data, 64);


