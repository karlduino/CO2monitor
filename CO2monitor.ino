// CO2 monitor with Senseair S8 and 16x2 LCD display

#include <Arduino.h>
#include "s8_uart.h"
#include <Wire.h>
#include <LCD_I2C.h>

#define STARTUP_DELAY_MS    8000
#define TIME_BETW_UPDATE_MS 5000
#define SAFE_LEVEL  1000
#define BAD_LEVEL   1400

// Configuration
       // need to use S8_RX = 11 and S8_TX = 10 for arduino nano every
       // also works for (old) arduino nano
#define S8_RX_PIN 11 // yellow (middle pin on 5-pin header)
#define S8_TX_PIN 10 // green  (to left of that, looking down at the label)

SoftwareSerial S8_serial(S8_RX_PIN, S8_TX_PIN);

// set up special characters for LCD display
#if defined(ARDUINO) && ARDUINO >= 100
#define printByte(args)  write(args);
#else
#define printByte(args)  print(args,BYTE);
#endif

uint8_t subscript2[8] = {0x0, 0x0, 0x0, 0x1E, 0x03, 0x06, 0x0C, 0x1F };
uint8_t heart[8] = {0x0,0xa,0x1f,0x1f,0xe,0x4,0x0};
uint8_t smile[8] = {0x0,0x0,0xa,0x0,0x0,0x11,0xe,0x0};
uint8_t frown[8] = {0x0,0x0,0xa,0x0,0x0,0x0,0xe,0x11};

S8_UART *sensor_S8;
S8_sensor sensor;

LCD_I2C lcd(0x27,16,2);  // set the LCD address to 0x27 for a 16 chars and 2 line display

void setup() {

  // start up the LCD display
  lcd.begin();
  lcd.backlight();
  lcd.setCursor(0,0);
  lcd.print("Starting up...");
  lcd.createChar(0, subscript2);
  lcd.createChar(1, heart);
  lcd.createChar(2, smile);
  lcd.createChar(3, frown);

  // Initialize S8 sensor
  S8_serial.begin(S8_BAUDRATE);
  sensor_S8 = new S8_UART(S8_serial);

  // Check if S8 is available
  sensor_S8->get_firmware_version(sensor.firm_version);
  int len = strlen(sensor.firm_version);
  int n_tries = 1;
  while (len == 0 && n_tries < 120) {
      delay(250);
      sensor_S8->get_firmware_version(sensor.firm_version);
      len = strlen(sensor.firm_version);
      n_tries++; // give up after 120 tries
  }

  // Show basic S8 sensor info
  lcd.setCursor(0,0);
  lcd.print("SenseAir S8      ");
  lcd.setCursor(0,1);
  lcd.print("Firmware:        ");
  lcd.setCursor(10,1);
  if (len == 0) lcd.print("N/A");
  else lcd.print(sensor.firm_version);
  sensor.sensor_id = sensor_S8->get_sensor_ID();

  delay(2000);

  // wait a bit to try to avoid first reading of 0 ppm
  lcd.setCursor(0,1);
  lcd.print("                ");
  lcd.setCursor(0,0);
  lcd.print("Warming up...   ");

  // beating heart
  if(STARTUP_DELAY_MS > n_tries * 250) { // beating heart
    int n_beats = (STARTUP_DELAY_MS - n_tries*250)/1000 + 1;

    for(int beat=0; beat < n_beats; beat++) {
      lcd.setCursor(14,1);
      lcd.printByte(1);
      delay(800);

      lcd.setCursor(14,1);
      lcd.print(" ");
      delay(200);
    }
  }

  // constant part of the display
  lcd.clear();
  lcd.setCursor(5,0);
  lcd.print("ppm CO");
  lcd.setCursor(11,0);
  lcd.printByte(0);  // subscript 2

  lcd.setCursor(0,1);
  lcd.print("max CO  =");
  lcd.setCursor(6,1);
  lcd.printByte(0);  // subscript 2
}

int max_co2 = 0;

void loop() {

  char buffer[17]; // to hold formated print

  // clear bits from the display
  lcd.setCursor(0,0);
  lcd.print("    ");
  lcd.setCursor(10,1);
  lcd.print("    ");
  lcd.setCursor(13, 0);
  lcd.print("   ");
  lcd.setCursor(15, 1);
  lcd.print(" ");

  // Get and display CO2 measure
  sensor.co2 = sensor_S8->get_co2();
  lcd.setCursor(0,0);
  sprintf(buffer, "%4d", sensor.co2);
  lcd.print(buffer);

  // max since start-up
  if (sensor.co2 > max_co2) { max_co2 = sensor.co2; }
  lcd.setCursor(10,1);
  sprintf(buffer, "%4d", max_co2);
  lcd.print(buffer);

  // print warning
  lcd.setCursor(15,0);
  if(sensor.co2 <= SAFE_LEVEL) {
    lcd.printByte(2); // smile
  } else if(sensor.co2 < BAD_LEVEL) {
    lcd.printByte(3); // frown
  } else {
    lcd.setCursor(13,0);
    lcd.print("!!!");
    lcd.setCursor(15,1);
    lcd.printByte(3); // frown
  }

  // Wait for selected time before next measure
  delay(TIME_BETW_UPDATE_MS);
}
