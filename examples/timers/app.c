#include <cmrx/application.h>
#include <cmrx/ipc/timer.h>
#include <cmrx/ipc/signal.h>
#include <cmrx/ipc/thread.h>
/* Non-recursive implementation of fibonacci sequence */
unsigned long long fib(unsigned long n)
{
    if (n == 0)
    {
        return 0;
    }
    if (n == 1)
    {
        return 1;
    }

    unsigned long long gp = 1ULL;
    unsigned long long p = 3ULL;
    for (int q = 2; q <= n; ++q)
    {
        unsigned long long out = 3ULL * p - gp;
        gp = p;
        p = out;
    }
    return p;
}

/* Thread that performs one calculation per second.
 * This thread uses periodic timers to get its timing. It won't
 * slow down or speed up if there is less or more amount
 * of work to be done. Interval timer is always delivered
 * in regular intervals.
 * Note that when thread has no more work to do and wants to
 * wait for timer arrival, it suspends itself by sending SIGSTOP
 * signal to itself.
 */
int app_periodic(void * data)
{
    // Initial 500ms sleep to shift the phase of the sleep
    // by 500ms so both threads won't affect each other
    usleep(500000UL);
    static volatile unsigned long long out = 0;
    unsigned q = 0;
    // Set 1 second periodic timer
    setitimer(1000000UL);
    while (1) {
         out = fib(q);
         q++;
         // Pause processing
         send_signal(get_tid(), SIGSTOP);
    }
}

/* Thread that waits one second after each calculation.
 * This thread uses delay timer to get its timing. As there's
 * more work to be done in order to calculate fibonacci sequence,
 * this thread will gradually slow down over time. The reason is
 * that period of no-op is fixed between computations.
 */
int app_usleep(void * data)
{
    static volatile unsigned long long out = 0;
    unsigned q = 0;
    while (1) {
        out = fib(q);
        q++;
        // Pause processing for 1 second
        usleep(1000000UL);
    }
}

OS_APPLICATION_MMIO_RANGE(app, 0, 0);
OS_APPLICATION(app);
OS_THREAD_CREATE(app, app_periodic, NULL, 64);
OS_THREAD_CREATE(app, app_usleep, NULL, 64);
