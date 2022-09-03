// CO2 monitor with Senseair S8 and 16x2 LCD display

#include <Arduino.h>
#include "s8_uart.h"
#include <Wire.h>
#include <LCD_I2C.h>

// Configuration
#define S8_RX_PIN 6
#define S8_TX_PIN 7

SoftwareSerial S8_serial(S8_RX_PIN, S8_TX_PIN);


// set up special character (subscript 2) for LCD display
#if defined(ARDUINO) && ARDUINO >= 100
#define printByte(args)  write(args);
#else
#define printByte(args)  print(args,BYTE);
#endif

uint8_t subscript2[8] = {0x0, 0x0, 0x0, 0x1E, 0x03, 0x06, 0x0C, 0x1F };

S8_UART *sensor_S8;
S8_sensor sensor;

LCD_I2C lcd(0x27,16,2);  // set the LCD address to 0x27 for a 16 chars and 2 line display

void setup() {

  // start up the LCD display
  lcd.begin();
  lcd.backlight();
  lcd.setCursor(0,0);
  lcd.print("Starting up...");
  lcd.createChar(1, subscript2);

  // Initialize S8 sensor
  S8_serial.begin(S8_BAUDRATE);
  sensor_S8 = new S8_UART(S8_serial);
  delay(2000);

  // Check if S8 is available
  sensor_S8->get_firmware_version(sensor.firm_version);
  int len = strlen(sensor.firm_version);
  if (len == 0) {
      lcd.setCursor(0,0);
      lcd.print("SenseAir S8 CO2");
      lcd.setCursor(0,1);
      lcd.print("not found!");
      while (1) { delay(1); };
  }

  // Show basic S8 sensor info
  lcd.setCursor(0,0);
  lcd.print("Yay! SenseAir S8");
  lcd.setCursor(0,1);
  lcd.print("Firmware:");
  lcd.setCursor(9,1);
  lcd.print(sensor.firm_version);
  sensor.sensor_id = sensor_S8->get_sensor_ID();

  delay(2000);


  // Show basic S8 sensor info
  lcd.setCursor(0,0);
  lcd.print("Warming up...   ");
  lcd.setCursor(0,1);
  lcd.print("                ");

  delay(4000);

}

int max_co2 = 0;

void loop() {

  char buffer[17]; // to hold formated print

  // clear display
  lcd.clear();

  // Get and display CO2 measure
  sensor.co2 = sensor_S8->get_co2();
  lcd.setCursor(0,0);
  sprintf(buffer, "%4d ppm CO", sensor.co2);
  lcd.print(buffer);
  lcd.setCursor(11,0);
  lcd.printByte(1);  // subscript 2

  if (sensor.co2 > max_co2) { max_co2 = sensor.co2; }
  lcd.setCursor(0,1);
  sprintf(buffer, "max CO  = %4d", max_co2);
  lcd.print(buffer);
  lcd.setCursor(6,1);
  lcd.printByte(1);  // subscript 2


  // Wait 5 second for next measure
  delay(5000);
}
