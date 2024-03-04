#include <cmrx/application.h>
#include <pico/stdlib.h>
#include <cmrx/ipc/timer.h>
#error "boo"

char data[128];

int init_main(void * unused)
{
    gpio_init(PICO_DEFAULT_LED_PIN);
    gpio_set_dir(PICO_DEFAULT_LED_PIN, GPIO_OUT);
    while (1) {
        gpio_put(PICO_DEFAULT_LED_PIN, 1);
        usleep(500000);
        gpio_put(PICO_DEFAULT_LED_PIN, 0);
        usleep(500000);

    }
    return 0;
}

OS_APPLICATION_MMIO_RANGES(init, 0x40000000, 0x50000000, 0xd0000000, 0xe0000000);
OS_APPLICATION(init);
OS_THREAD_CREATE(init, init_main, NULL, 64);
