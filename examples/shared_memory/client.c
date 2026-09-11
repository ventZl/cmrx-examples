#include <cmrx/application.h>
#include <cmrx/ipc/rpc.h>
#include <cmrx/ipc/shmem.h>
#include "service.h"

#define BUFSIZE 32
SHARED uint8_t buffer[BUFSIZE];

static int thread_main(void * data)
{
    while (1) {
        uint32_t tmp = rpc_call(&service, count_r_s, buffer, BUFSIZE);
    }
}

OS_APPLICATION_MMIO_RANGE(client, 0, 0);
OS_APPLICATION(client);
OS_THREAD_CREATE(client, thread_main, NULL, 64);


