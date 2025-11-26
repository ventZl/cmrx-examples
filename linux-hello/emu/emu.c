#include "uart.h"
#include "emu_priv.h"
#include "emu.h"

#include <stdio.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <string.h>
#include <unistd.h>
#include <extra/emulator.h>

#include <threads.h>

#define UART_SOCK_FILE "uart0.sock"

static int sock_fd = -1;

static void uart_emu_write(volatile void * addr);
static void uart_emu_read(const volatile void * addr);

/* Create peripheral emulator instance. This instance will be called `uart_emu` */
CMRX_PERIPHERAL_EMULATOR(UART_Device_t, uart_emu, uart_emu_read, uart_emu_write);

static struct sockaddr_un uart_other_endpoint;
static socklen_t uart_other_endpoint_len = sizeof(uart_other_endpoint);

/** Emulated UART register write callback.
 *
 * If TXD register is written, then it will try to
 * transmit the data.
 *
 * If CR register is written and bit RESET is set
 * then peripheral is reset into default state.
 */
static void uart_emu_write(volatile void * addr)
{
    if (addr == &uart_emu.device.TXD)
    {
        uint8_t buff = *((uint8_t *) addr);
        if (sock_fd == -1)
        {
            uart_emu.device_full.STS |= UART_STS_ERR;
            return;
        }

        int ret = -1;

        ret = sendto(sock_fd, &buff, sizeof(buff), 0, (struct sockaddr *)&uart_other_endpoint, uart_other_endpoint_len);
        if (ret < 0) {
            uart_emu.device_full.STS |= UART_STS_ERR;
        }
    } else {
        if (addr == &uart_emu.device.CR)
        {
            uint32_t cr = *((uint32_t *) addr);

            if (cr & UART_CR_RESET)
            {
                uart_emu.device_full.STS = UART_STS_TXRDY;
                uart_emu.device_full.CR = 0;
                uart_emu.device_full.RXD = 0;
                uart_emu.device_full.TXD = 0;
            }
        }
    }
}

/** Emulated UART register read callback.
 *
 * After data is read from the RXD register, the
 * RXRDY flag is cleared.
 */
static void uart_emu_read(const volatile void * addr)
{
    // Clear the RX ready flag. This will be done slightly before
    // the data is actually read but it doesn't matter as from the
    // CMRX application's point of view it happend simultaneously.
    if (addr == &uart_emu.device.RXD)
    {
        uart_emu.device.STS &= ~UART_STS_RXRDY;
    }
}

/** Emulated UART instance application is seeing and can reference */
UART_Device_t * UART0 = &uart_emu.device;

/** Main emulator thread.
 *
 * This opens the UNIX domain socket outer world
 * can interact with and then waits for data being received.
 * Once data is received, it is put into RXD register, so application
 * can read it and IRQ 15 is generated.
 */
int uart_emulation_main(void * nothing)
{
    (void) nothing;

    struct sockaddr_un addr;
    int ret;
    unsigned char buff[1];
    int ok = 1;
    int len;

    while (1) {
        if ((sock_fd = socket(PF_UNIX, SOCK_DGRAM, 0)) < 0) {
            ok = 0;
        }

        if (ok) {
            memset(&addr, 0, sizeof(addr));
            addr.sun_family = AF_UNIX;
            strcpy(addr.sun_path, UART_SOCK_FILE);
            unlink(UART_SOCK_FILE);
            if (bind(sock_fd, (struct sockaddr *)&addr, sizeof(addr)) < 0) {
                ok = 0;
            }
        }

        static struct sockaddr_un from;
        static socklen_t fromlen = sizeof(from);
        while ((len = recvfrom(sock_fd, buff, 1, 0, (struct sockaddr *)&from, &fromlen)) > 0) {
            memcpy(&uart_other_endpoint, &from, sizeof(from));
            // Signal that data is ready
            uart_emu.device_full.STS |= UART_STS_RXRDY;
            generate_interrupt(15);

            // Drop constness
            uart_emu.device_full.RXD = buff[0];
        }


        if (sock_fd >= 0) {
            close(sock_fd);
        }
    }
    return 0;
}

thrd_t emu_thread;

/** Initialize the emulator.
 *
 * This will start the UART emulator thread.
 */
void uart_emulation_init()
{
    thrd_create(&emu_thread, uart_emulation_main, NULL);
}
