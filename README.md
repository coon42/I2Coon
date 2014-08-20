I2Coon
======

A working I2C library for the ATmega 328p.

The Wire library delived with the Arduino IDE is crap. It hangs the microcontroller if there is noise on the bus. I also tried the WSWire library. This will circumvent the freezes by using timeouts but at some point the library blocks the whole bus randomly. That's why I will rewrite the library from scratch with correct error handling.
