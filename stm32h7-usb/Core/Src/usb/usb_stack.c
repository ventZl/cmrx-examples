#include <cmrx/application.h>
#include <cmrx/ipc/notify.h>
#include <cmrx/ipc/shmem.h>
#include <tusb.h>

SHARED unsigned char defer_buffer[32];
volatile osal_queue_t defer_queue;
volatile bool defer_busy = false;

int usb_stack_main(void * none)
{
    (void) none;

    tusb_init();

    while (1) {
        tud_task();
    }
}

#if 0
int usb_stack_isr_defer_queue_send(void * none)
{
    (void) none;
    while (1) {
        wait_for_object(defer_buffer, 0);
        rpc_call(defer_queue, send, (uint8_t *) defer_buffer);
        defer_busy = false;
    }

}
#endif

OS_APPLICATION_MMIO_RANGES(usb_stack, 0x40080000, 0x400C0000, 0x58024400, 0x58024800);
OS_APPLICATION(usb_stack);
OS_THREAD_CREATE(usb_stack, usb_stack_main, NULL, 64);
//OS_THREAD_CREATE(usb_stack, usb_stack_isr_defer_queue_send, NULL, 1);
