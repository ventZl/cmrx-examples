#include <cmrx/application.h>
#include <hal/nrf_gpio.h>
#include <cmrx/ipc/timer.h>

char data[128];

#define GPIO_BL_HI     23
#define GPIO_BL_MED     22
#define GPIO_BL_LOW     14

int init_main(void * unused)
{
    nrf_gpio_cfg_output(GPIO_BL_HI);
    nrf_gpio_cfg_output(GPIO_BL_MED);
    nrf_gpio_cfg_output(GPIO_BL_LOW);

    nrf_gpio_pin_set(GPIO_BL_HI);
    nrf_gpio_pin_set(GPIO_BL_MED);
    nrf_gpio_pin_set(GPIO_BL_LOW);
    while (1) {
        nrf_gpio_pin_clear(GPIO_BL_HI);
        usleep(500000);
        nrf_gpio_pin_set(GPIO_BL_HI);
        usleep(500000);

    }
    return 0;
}

OS_APPLICATION_MMIO_RANGES(init, 0x40000000, 0x50000000, 0xd0000000, 0xe0000000);
OS_APPLICATION(init);
OS_THREAD_CREATE(init, init_main, NULL, 64);
