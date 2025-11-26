#include <cmrx/application.h>
#include <uart_driver/uart.h>
#include <cmrx/ipc/rpc.h>

int app_main(void * data)
{
    (void) data;

    while (1) {
        uint8_t buffer;
        buffer = rpc_call(&uart_device, read);
        rpc_call(&uart_device, write, buffer);
    }

    return 0;
}

OS_APPLICATION_MMIO_RANGE(app, 0, 0);
OS_APPLICATION(app);
OS_THREAD_CREATE(app, app_main, NULL, 64);
