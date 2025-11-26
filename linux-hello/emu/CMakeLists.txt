add_library(uart_emu STATIC emu.c)
target_link_libraries(uart_emu stdlib phy_emu)
