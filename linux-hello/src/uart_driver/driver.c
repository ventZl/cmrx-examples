#include "uart.h"
#include <emu/uart.h>

#include <cmrx/rpc/implementation.h>
#include <cmrx/application.h>
#include <cmrx/ipc/notify.h>
#include <cmrx/ipc/isr.h>

/** Handler of emulated IRQ signal.
 *
 * This function will be called asynchronously
 * preempting whatever other code was running
 * except of thread switcher which "disables
 * interrupts".
 *
 * Drivers can trigger interrupts by using
 * @ref generate_interrupt function.
 *
 * You can treat this function as if it was
 * an interrupt handler on real hardware - it
 * preempts all the non-interrupt code. It
 * *can't* use system calls either, because it
 * preempts even the kernel.
 *
 * You can only use functions in group of ISR
 * API, which boils down to two functions:
 *
 * - isr_kill()
 * - isr_notify_object()
 *
 * Other than that you can work with all the memory,
 * but beware - while this handler is running all the
 * normal system services are disabled, so you better
 * don't do any long-term work in here.
 */
void IRQ_15()
{
    isr_notify_object(&uart_device);
}

IMPLEMENTATION_OF(struct UART, struct UARTVtable);

static uint8_t uart_read(INSTANCE(this))
{
    while (!(_R(UART0, STS) & UART_STS_RXRDY))
    {
        wait_for_object(&uart_device, 0);
    }
    return _R(UART0, RXD);
}

static void uart_write(INSTANCE(this), uint8_t data)
{
    while (!(_R(UART0, STS) & UART_STS_TXRDY))
    {
        wait_for_object(&uart_device, 0);
    }
    return _W(UART0, TXD, data);
}

VTABLE struct UARTVtable uart_vtable = {
    &uart_read,
    &uart_write
};

struct UART uart_device = {
    &uart_vtable
};

OS_APPLICATION_MMIO_RANGE(uart, 0, 0);
OS_APPLICATION(uart);
