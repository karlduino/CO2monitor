## CO2 monitor based on an Arduino and a SenseAir S8 sensor

This is a low-cost do-it-yourself CO2 monitor based on the [SenseAir
S8](https://senseair.com/products/size-counts/s8-lp/) sensor, an
[Arduino Nano
Every](https://store.arduino.cc/products/arduino-nano-every), and a
16x2 LCD display.

The goal is assess air quality, particularly in classrooms and meeting
rooms and with concern about COVID-19. The main source of my
understanding was
[LibreCO2](https://github.com/danielbernalb/LibreCO2).

Here are the parts I used:

- [SenseAir S8](https://senseair.com/products/size-counts/s8-lp/)
  [![shopping cart icon](docs/pics/shopping-cart.png)](https://amzn.to/3AyzQMa)

- [Arduino Nano Every](https://store.arduino.cc/products/arduino-nano-every)
  or [Arduino Nano](https://store.arduino.cc/products/arduino-nano)

- 16x2 display with I2C chip
  [![shopping cart icon](docs/pics/shopping-cart.png)](https://amzn.to/3AwG3Z7)

- clear plastic box
  [![shopping cart icon](docs/pics/shopping-cart.png)](https://amzn.to/3R24kxb)


To connect the components, you will need some female-to-female jumper
wires, solder, male header pins, and a soldering iron (for the
SenseAir S8 sensor, and maybe also for the Arduino if you got one
without headers installed).

To attach components to the box, you'll need some
small screws (I used 1/2" 4/40 screws for the LCD display), as well as
some _very_ small screws (I used **" 0/80 screws for the Arduino).

If you're using an Arduino Nano Every, I found that, in the Arduino
IDE, you need to first use the Board Manager to install the drivers
for the megaAVR boards, and then when you select Nano Every, use
`Registers emulation: None (ATMEGA4809)`.

My code for interacting with the SenseAir S8 sensor is based on the
example code in the [S8_UART
library](https://github.com/jcomas/S8_UART).

My code for writing on the LCD (including making the custom character
for the subscript 2) was based on the example code with the
older [LiquidCrystal_I2C
library](https://github.com/johnrickman/LiquidCrystal_I2C) (which is
not compatible with the Arduino Nano Every).

## Libraries

- [S8_UART](https://www.arduino.cc/reference/en/libraries/s8_uart/)
  [![github](https://kbroman.org/icons16/github-icon.png)](https://github.com/jcomas/S8_UART)

- [LCD_I2C](https://www.arduino.cc/reference/en/libraries/lcd_i2c/)
  [![github](https://kbroman.org/icons16/github-icon.png)](https://github.com/blackhack/LCD_I2C)


## Connections

- The 16x2 LCD with I2C has a 4-pin connector:

  - 16x2 GND -> Arduino GND (black)

  - 16x2 VCC -> Arduino VIN (red)

  - 16x2 SDA -> Arduino A4 (green)

  - 16x2 SCL -> Arduino A5 (yellow)

- The SenseAir S8 needs soldering; could use two pairs of header pins

  - 4-pin side, pin 1 (G+) -> Arduino 5V (red)

  - 4-pin side, pin 2 (G0) -> Arduino GND (black)

  - 5-pin side, pin 2 -> Arduino D10 (green)

  - 5-pin side, pin 3 -> Arduino D11 (yellow)

## License

This work released under the [MIT License](LICENSE.md).
