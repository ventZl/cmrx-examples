#pragma once

/** Early initialization of the UART driver.
 *
 * This routine runs before the CMRX kernel has been started up
 * so it has full hardware access. It can be used to configure
 * the peripheral, such as switching pins into AF mode, enabling
 * clocks, power, etc.
 *
 * It is meant for one-time post-boot initialization which is dependant
 * on the hardware config, rather than application configuration.
 */
void uart_init();
