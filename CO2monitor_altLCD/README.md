## alternate sketch for alternate LCD display

We bought some LCD displays with I2C integrated from digikey.
They turned out to be quite different from the other ones we were
using.

[Orient Display AMC1602AR-B-B6WTDW-I2C](https://www.digikey.com/en/products/detail/orient-display/AMC1602AR-B-B6WTDW-I2C/12089223)

They use an RW1063 controller, which is apparently takes the same
instructions as the HD44780.

The display has 10 pins:

- pin 1: LED backlight, connect to 5V
- pin 2: LED backlight, connect to GND
- pin 3: connect to GND
- pin 4: connect to 5V
- pin 5: SDA, connect to arduino A4
- pin 6: SCL, connect to arduino A5
- pin 7: controls LCD contrast; connect to GND, through 4K Ohm
  resistor
- pins 8-10: unused

We use the library
[LiquidCrystalWired](https://www.arduino.cc/reference/en/libraries/liquidcrystalwired/).
The address for the LCD display is `0x3C`.
