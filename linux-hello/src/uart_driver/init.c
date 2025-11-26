#include "init.h"
#include <emu/uart.h>

void uart_init()
{
    /* Intentionally left empty. Peripheral
     * is so simple it doesn't need any
     * initialization. */
    _W(UART0, CR, UART_CR_RESET);
}
