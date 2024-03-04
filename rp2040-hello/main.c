//#include <cmrx/os/sched.h>
#include <pico/stdlib.h>
#include <cmrx/cmrx.h>
#include <aux/systick.h>

int main(void)
{
//    SystemInit();
	timing_provider_setup(1);
    os_start();
    return 0;
}
