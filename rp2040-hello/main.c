//#include <cmrx/os/sched.h>
#include <pico/stdlib.h>
#include <cmrx/cmrx.h>
#include <extra/systick.h>

int main(void)
{
	timing_provider_setup(1);
    os_start();
    return 0;
}
