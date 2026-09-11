#include <cmrx/application.h>
#include "api.h"
#include "service.h"
#include <cmrx/rpc/implementation.h>
#include <stdio.h>

IMPLEMENTATION_OF(RPCService, struct ServiceAPI);

uint32_t rpcservice_count_r_s(INSTANCE(this), const uint8_t * buffer, uint32_t bufsize)
{
    uint32_t ret = 0;
    for (uint32_t q = 0; q < bufsize; ++q)
    {
        if (buffer[q] == 'r' || buffer[q] == 'R')
        {
            ret++;
        }
    }
    return ret;
}

VTABLE struct ServiceAPI vtable = {
    &rpcservice_count_r_s,
};

RPCService service = {
    &vtable,
    0
};

OS_APPLICATION_MMIO_RANGE(rpcserver, 0, 0);
OS_APPLICATION(rpcserver);

