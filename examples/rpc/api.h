#pragma once

#include <stdint.h>
#include <cmrx/rpc/interface.h>

/* Type that declares the API service will implement */
struct ServiceAPI {
    /* INSTANCE(this) is an idiom that marks an argument referncing to service instance */
    void (*set_internal)(INSTANCE(this), uint32_t argument);
    uint32_t (*get_internal)(INSTANCE(this));
};
