add_application(usb_stack msc_disk.c usb_descriptors.c usb_stack.c)
add_tinyusb(usb_stack)
target_link_libraries(usb_stack PRIVATE stdlib tinyusb_config cmsis_headers)
