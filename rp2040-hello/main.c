#include <pico/stdlib.h>
#include <cmrx/cmrx.h>
#include <extra/systick.h>
#include <RTE_Components.h>
#include CMSIS_device_header

long timing_get_current_cpu_freq(void)
{
    return SystemCoreClock;
}

int main(void)
{
	timing_provider_setup(1);
    os_start();
    return 0;
}
