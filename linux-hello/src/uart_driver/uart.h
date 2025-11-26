#pragma once

#include <stdint.h>
#include <cmrx/rpc/interface.h>

struct UARTVtable {
    uint8_t (*read)(INSTANCE(this));
    void (*write)(INSTANCE(thuis), uint8_t data);
};

struct UART {
    const struct UARTVtable * vtable;
    /* This peripheral has no data */
};

extern struct UART uart_device;
