#include <cmrx/cmrx.h>
#include <cmrx/clock.h>
#include "uart_driver/init.h"
#include <emu/emu.h>
#include <signal.h>
#include <pthread.h>
#include <stdio.h>

void timing_provider_setup(unsigned timeout_ms);

/* Disable reception of these signals globally.
 * CMRX Linux port is using these signals to implement
 * kernel features.
 *
 * These expect to be only serviced in the context of
 * CMRX thread.
 *
 * By disabling it early - ideally as the very first thing
 * that the program does - we ensure that only those threads
 * which later enable these signals will really get them.
 */
void arch_early_init()
{
    sigset_t set;

    sigemptyset(&set);
    sigaddset(&set, SIGALRM);
    sigaddset(&set, SIGUSR1);
    sigaddset(&set, SIGUSR2);
    sigaddset(&set, SIGURG);
    pthread_sigmask(SIG_BLOCK, &set, NULL);
}

int main(int argc, char ** argv)
{
    arch_early_init();
    uart_emulation_init();

    uart_init();
    timing_provider_setup(1000);
    os_start();
}

