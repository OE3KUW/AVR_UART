# AVR_UART

Small ATmega328P/Arduino Uno UART example built with PlatformIO.

The program sends `start!` after initialization. Every received character is echoed via
UART. Receiving `x` toggles the onboard LED.

Serial configuration: 9600 baud, 8 data bits, no parity, one stop bit.
