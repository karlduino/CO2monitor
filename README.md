## CO2 monitor

This is a DIY CO2 monitor based on the [SenseAir
S8](https://senseair.com/products/size-counts/s8-lp/) sensor, an
arduino, and a 16x2 LCD display.

The goal is assess air quality, particularly in classrooms and with
concern about COVID-19. The main source of my understanding was [LibreCO2](https://github.com/danielbernalb/LibreCO2).

Here are the parts I used:

- [SenseAir S8](https://senseair.com/products/size-counts/s8-lp/) from
  [Amazon](https://amzn.to/3AyzQMa)
- [Arduino Nano](https://store.arduino.cc/products/arduino-nano)
- 16x2 display with I2C chip from [Amazon](https://amzn.to/3AwG3Z7)
- plastic box from [Amazon](https://amzn.to/3R24kxb)

Also some wires, include female-female jumpers, and solder and a
soldering iron (just to get wires onto the SenseAir S8), and some
small screws, as well as some _very_ small screws.

## Libraries

- [S8_UART](https://www.arduino.cc/reference/en/libraries/s8_uart/)
- [LiquidCrystal_I2C](https://www.arduino.cc/reference/en/libraries/liquidcrystal-i2c/)

## Connections

- The 16x2 LCD with I2C has a 4-pin connector:

  - 16x2 GND -> Arduino Nano GND (black)
  - 16x2 VCC -> Arduino Nano VIN (red)
  - 16x2 SDA -> Arduino Nano A4 (green)
  - 16x2 SCL -> Arduino Nano A5 (yellow)

- The SenseAir S8 needs soldering (needs confirmation)

  - 4-pin side, pin 1 (G+) -> Arduino Nano 5V (red)
  - 4-pin side, pin 2 (G0) -> Arduino Nano GND (black)
  - 5-pin side, pin 2 -> Arduino Nano D7 (green)
  - 5-pin side, pin 3 -> Arduino Nano D6 (yellow)
