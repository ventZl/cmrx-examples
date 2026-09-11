#pragma once

#include <stdint.h>
#include <cmrx/rpc/interface.h>

/* Type that declares the API service will implement */
struct ServiceAPI {
    /* INSTANCE(this) is an idiom that marks an argument referncing to service instance */
    uint32_t (*count_r_s)(INSTANCE(this), const uint8_t * buffer, uint32_t bufsize);
};
