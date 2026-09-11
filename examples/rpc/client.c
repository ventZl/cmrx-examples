#include <cmrx/application.h>
#include <cmrx/ipc/rpc.h>
#include "service.h"

static int thread_main(void * data)
{
    while (1) {
        uint32_t tmp = rpc_call(&service, get_internal);
        tmp++;
        rpc_call(&service, set_internal, tmp);
    }
}

OS_APPLICATION_MMIO_RANGE(client, 0, 0);
OS_APPLICATION(client);
OS_THREAD_CREATE(client, thread_main, NULL, 64);


