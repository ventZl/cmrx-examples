Temporary mashup directory for porting of CMRX onto CMSIS-based HALs
====================================================================

This is a mashup of three distinct things:
* RPi-Pico SDK, which contains CMSIS for Cortex-M0+ and RPi Pico peripherals
* CMRX tree where shim for pico is being developped. This shim is named as rpi-pico, but
  in fact it may serve as basis for any CMSIS-based HAL (hopefully)
* small main.c carrying one CMRX process + thread and CMakeLists.txt gluing everything together
