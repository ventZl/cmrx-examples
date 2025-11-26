#pragma once

#include "uart.h"

/* Emulator-private header. Not for inclusion in the app */

/** Private version of the peripheral register set.
 * This is a private version of the peripheral register file.
 * The layout of this set must be the same as the layout
 * visible by the application. The only difference is that
 * we can add/remove const here to reflect the peripheral's
 * ability to access the register.
 *
 * E.g. the TXD register is writable from the CPU's point of view
 * but is readable from the peripheral's POV. In reality, all registers
 * are writable by the peripheral, if not anything else, then at
 * least for resetting purposes.
 */
typedef struct {
    volatile uint32_t CR;
    volatile uint32_t RXD;
    volatile uint32_t TXD;
    volatile uint32_t STS;
} Full_UART_Device_t;

#if 0
/** Guard to check if internal and external structures are the same. */
_Static_assert(sizeof(UART_Device_t) == sizeof(UART_Emu_Device_t), "Internal and public types that describe emulated UART differ in size!");

/** Internal structure of the emulator. _R and _W both call-in here. */
typedef struct {
    void (*emu_write_cb)(volatile void * addr);
    void (*emu_read_cb)(const volatile void * addr);
    union {
        UART_Device_t device;
        UART_Emu_Device_t device_full;
    };
} UART_Emulation_t;
#endif
