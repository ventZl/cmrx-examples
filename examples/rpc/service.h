#pragma once

#include "api.h"

typedef struct {
    const struct ServiceAPI * vtable;
    uint32_t internal_data;
} RPCService;

extern RPCService service;
