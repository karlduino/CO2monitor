## CO<sub>2</sub> monitor based on an Arduino and a SenseAir S8 sensor

This is a low-cost, do-it-yourself CO<sub>2</sub> monitor based on the [SenseAir
S8](https://senseair.com/products/size-counts/s8-lp/) sensor, an
[Arduino Nano
Every](https://store.arduino.cc/products/arduino-nano-every), and a
16x2 LCD display.

The goal is assess air quality, particularly in classrooms and meeting
rooms and with concern about COVID-19. The main source of my
understanding was
[LibreCO2](https://github.com/danielbernalb/LibreCO2). Also see
[this useful
post](https://emariete.com/en/meter-co2-esp8266-nodemcu-sensor-senseair-s8/)
by [Mariete](https://emariete.com/en/).

I did a limited comparison between two of the SenseAir S8 monitors and
the more expensive [Aranet4](https://aranet.com/products/aranet4/);
[see the results](https://karlduino.org/CO2monitor/docs/Comparison/comparison.html).

[![CO2 monitor tied to a wooden post with a pink cord](https://karlduino.org/CO2monitor/docs/pics/co2monitor_sm.jpg)](https://karlduino.org/CO2monitor/docs/pics/co2monitor.jpg)

### Parts

The cost of the main components is about US$ 60. (Most of the cost is
the sensor, which is about US$ 40. If you're willing to wait a month
for shipping, you can get it much cheaper
[via AliExpress](https://s.click.aliexpress.com/e/_9GsnY9)).

- [SenseAir S8](https://senseair.com/products/size-counts/s8-lp/)
  [![shopping cart icon](docs/pics/shopping-cart.png)](https://amzn.to/3AyzQMa)

- [Arduino Nano Every](https://store.arduino.cc/products/arduino-nano-every)

- 16x2 display with I2C chip
  [![shopping cart icon](docs/pics/shopping-cart.png)](https://amzn.to/3AwG3Z7)

- clear plastic box
  [![shopping cart icon](docs/pics/shopping-cart.png)](https://amzn.to/3R24kxb)

To connect the components, you will need 8 female-to-female jumper
wires, solder, a soldering iron, 2 2-pin male headers for the SenseAir
S8 sensor, and maybe also 2 16-pin male headers for the Arduino (if
you got one without headers installed).

To attach components to the box, you'll need some
small screws (I used 1/2" 4/40 screws for the LCD display), as well as
some _very_ small screws (I used 11/32" 0/80 screws for the Arduino).


### Code

You'll find the code on [Github](https://github.com/karlduino/CO2monitor).

The first time using the Arduino Nano Every with the Arduino
IDE, you may need to use the Board Manager to install the drivers
for the megaAVR boards. Then when you select the Nano Every as your
board, select `Registers emulation: None (ATMEGA4809)`.

My code for interacting with the SenseAir S8 sensor is based on the
example code in the [S8_UART
library](https://github.com/jcomas/S8_UART).

My code for writing on the LCD (including making custom characters)
was based on the example code with the older [LiquidCrystal_I2C
library](https://github.com/johnrickman/LiquidCrystal_I2C) (which is
not compatible with the Arduino Nano Every).

### Libraries

- [S8_UART](https://www.arduino.cc/reference/en/libraries/s8_uart/)
  [![github](https://kbroman.org/icons16/github-icon.png)](https://github.com/jcomas/S8_UART)

- [LCD_I2C](https://www.arduino.cc/reference/en/libraries/lcd_i2c/)
  [![github](https://kbroman.org/icons16/github-icon.png)](https://github.com/blackhack/LCD_I2C)


### Assembly instructions

See the
[instructions document](https://karlduino.org/CO2monitor/docs/instructions.html),
which attempts to explain the full process:

- prepare the box (drilling holes to mount components and cutting
  holes for the sensor and the micro-USB cable)

- Solder headers onto the main components

- Mount the components

- Make connections (see below)

- Load the software


### Connections

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


### License

This work released under the [MIT License](LICENSE.md).
