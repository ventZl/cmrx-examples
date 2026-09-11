#include <cmrx/application.h>
#include "api.h"
#include "service.h"
#include <cmrx/rpc/implementation.h>
#include <stdio.h>

IMPLEMENTATION_OF(RPCService, struct ServiceAPI);

void rpcservice_set_internal(INSTANCE(this), uint32_t value)
{
    this->internal_data = value;
}

uint32_t rpcservice_get_internal(INSTANCE(this))
{
    return this->internal_data;
}

VTABLE struct ServiceAPI vtable = {
    &rpcservice_set_internal,
    &rpcservice_get_internal
};

RPCService service = {
    &vtable,
    0
};

OS_APPLICATION_MMIO_RANGE(rpcserver, 0, 0);
OS_APPLICATION(rpcserver);

