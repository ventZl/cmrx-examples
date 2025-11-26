#pragma once

#include <extra/emulator/peripheral.h>

/* Emulated minimalistic UART peripheral.
 *
 * This is an interface of UART peripheral that is emulated
 * in software as CMRX ecosystem sees it.
 *
 * It presents a structure type that collects a few registers
 * that this simple peripheral provides and two functions
 * _R() and _W() which are used to simulate register read
 * and write.
 */

#include <stdint.h>

#define UART_STS_TXRDY      (1 << 0)
#define UART_STS_RXRDY      (1 << 1)
#define UART_STS_ERR        (1 << 2)

#define UART_CR_RESET       (1 << 0)

/** Type that describes emulated peripheral register layout.
 */
typedef struct {
    volatile uint32_t CR;
    volatile const uint32_t RXD;
    volatile uint32_t TXD;
    volatile uint32_t STS;
} UART_Device_t;

/** Instance of the peripheral in memory. Actual address
 * doesn't matter now.
 */
extern UART_Device_t * UART0;


#if 0
/** Simulate register read.
 *
 * @param x address of peripheral register. May be 8-, 16- or 32-bits large
 * @returns value of that register as provided by the peripheral
 */
#define _R(x)   _Generic((x), \
uint8_t : _R8,\
uint16_t : _R16,\
uint32_t : _R32)(&x)

/** Simulate register write.
 *
 * @param x address of peripheral register. May be 8-, 16- or 32-bits large
 * @param y value to be written. Type must match the register size.
 */
#define _W(x, y)  _Generic((x), \
uint8_t : _W8,\
uint16_t : _W16,\
uint32_t : _W32)(&x, y)

uint8_t _R8(const volatile uint8_t * source);
uint16_t _R16(const volatile uint16_t * source);
uint32_t _R32(const volatile uint32_t * source);

void _W8(volatile uint8_t * dest, uint8_t value);
void _W16(volatile uint16_t * dest, uint16_t value);
void _W32(volatile uint32_t * dest, uint32_t value);

#endif
