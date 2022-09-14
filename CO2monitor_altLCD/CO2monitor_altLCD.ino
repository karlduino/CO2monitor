// CO2 monitor with Senseair S8 and 16x2 LCD display
// this version is for an alternate LCD display using the RW1063 controller
// needs LiquidCrystalWired library + address 0x3C

#include <Arduino.h>
#include "s8_uart.h"
#include "LiquidCrystalWired.h"

#define STARTUP_DELAY_MS    8000
#define TIME_BETW_UPDATE_MS 5000
#define SAFE_LEVEL  1000
#define BAD_LEVEL   1400

// Configuration
       // need to use S8_RX = 11 and S8_TX = 10 for arduino nano every
       // also works for (old) arduino nano
#define S8_TX_PIN 11 // yellow (middle pin on 5-pin header)
#define S8_RX_PIN 10 // green  (to left of that, looking down at the label)

// The RX/TX labels are really confusing
//
// what're defined here as S8_RX and S8_TX are the pins
// where the S8 is receiving and transmitting, respectively
//
// They're connected to the opposite pins on the arduino,
// RX <-> TX, TX <-> RX
//
// and the SoftwareSerial object should get the
// arguments (arduino_RX, arduino_TX)
SoftwareSerial S8_serial(S8_TX_PIN, S8_RX_PIN);

// set up special characters for LCD display
uint8_t subscript2[8] = {0x0, 0x0, 0x0, 0x1E, 0x03, 0x06, 0x0C, 0x1F };
uint8_t heart[8] = {0x0,0xa,0x1f,0x1f,0xe,0x4,0x0};
uint8_t smile[8] = {0x0,0x0,0xa,0x0,0x0,0x11,0xe,0x0};
uint8_t frown[8] = {0x0,0x0,0xa,0x0,0x0,0xe,0x11,0x0};

S8_UART *sensor_S8;
S8_sensor sensor;

#define LCD_ADDRESS 0x3c
LiquidCrystalWired lcd = LiquidCrystalWired(2, 16, FONT_SIZE_5x8, BITMODE_8_BIT);

void setup() {

  // start up the LCD display
  lcd.begin(LCD_ADDRESS, &Wire);
  lcd.turnOn();
  lcd.setCursorPosition(0,0);
  lcd.print("Starting up...");
  lcd.setCustomSymbol(CUSTOM_SYMBOL_1, subscript2);
  lcd.setCustomSymbol(CUSTOM_SYMBOL_2, heart);
  lcd.setCustomSymbol(CUSTOM_SYMBOL_3, smile);
  lcd.setCustomSymbol(CUSTOM_SYMBOL_4, frown);

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
  lcd.setCursorPosition(0,0);
  lcd.print("SenseAir S8      ");
  lcd.setCursorPosition(1,0);
  lcd.print("Firmware:        ");
  lcd.setCursorPosition(1,10);
  if (len == 0) lcd.print("N/A");
  else lcd.print(sensor.firm_version);
  sensor.sensor_id = sensor_S8->get_sensor_ID();

  delay(2000);

  // wait a bit to try to avoid first reading of 0 ppm
  lcd.setCursorPosition(1,0);
  lcd.print("                ");
  lcd.setCursorPosition(0,0);
  lcd.print("Warming up...   ");

  // beating heart
  if(STARTUP_DELAY_MS > n_tries * 250) { // beating heart
    int n_beats = (STARTUP_DELAY_MS - n_tries*250)/1000 + 1;

    for(int beat=0; beat < n_beats; beat++) {
        lcd.setCursorPosition(1,14);
      lcd.printCustomSymbol(CUSTOM_SYMBOL_2);
      delay(800);

      lcd.setCursorPosition(1,14);
      lcd.print(" ");
      delay(200);
    }
  }

  // constant part of the display
  lcd.clear();
  lcd.setCursorPosition(0,5);
  lcd.print("ppm CO");
  lcd.setCursorPosition(0,11);
  lcd.printCustomSymbol(CUSTOM_SYMBOL_1);  // subscript 2

  lcd.setCursorPosition(1,0);
  lcd.print("max ");
  lcd.setCursorPosition(1,9);
  lcd.print("ave ");
}

int max_co2 = 0;
double ave_co2 = 0.0;
unsigned long n_measurements = 0;

void loop() {

  char buffer[17]; // to hold formated print

  // clear bits from the display
  lcd.setCursorPosition(0,0);
  lcd.print("    ");
  lcd.setCursorPosition(1,4);
  lcd.print("    ");
  lcd.setCursorPosition(0,13);
  lcd.print("   ");
  lcd.setCursorPosition(1,12);
  lcd.print("    ");

  // Get and display CO2 measure
  sensor.co2 = sensor_S8->get_co2();
  lcd.setCursorPosition(0,0);
  sprintf(buffer, "%4d", sensor.co2);
  lcd.print(buffer);

  // max since start-up
  if (sensor.co2 > max_co2) { max_co2 = sensor.co2; }
  lcd.setCursorPosition(1,4);
  sprintf(buffer, "%-4d", max_co2);
  lcd.print(buffer);

  // average
  if(n_measurements == 0) {
      ave_co2 = (double)sensor.co2;
  } else {
      ave_co2 = (ave_co2 * (double)n_measurements + (double)sensor.co2) / (double)(n_measurements+1);
  }
  n_measurements++;
  int ave_co2_int = round(ave_co2);
  lcd.setCursorPosition(1,12);
  sprintf(buffer, "%4d", ave_co2_int);
  lcd.print(buffer);

  // print warning
  lcd.setCursorPosition(0,15);
  if(sensor.co2 <= SAFE_LEVEL) {
    lcd.printCustomSymbol(CUSTOM_SYMBOL_3); // smile
  } else if(sensor.co2 < BAD_LEVEL) {
    lcd.printCustomSymbol(CUSTOM_SYMBOL_4); // frown
  } else {
      lcd.setCursorPosition(0,13);
    lcd.print("! !");
    lcd.setCursorPosition(0,14);
    lcd.printCustomSymbol(CUSTOM_SYMBOL_4); // frown
  }

  // Wait for selected time before next measure
  delay(TIME_BETW_UPDATE_MS);
}
