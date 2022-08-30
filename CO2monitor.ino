/*****************
   Get CO2 value
 *****************/

#include <Arduino.h>
#include "s8_uart.h"
#include <Wire.h>
#include <LiquidCrystal_I2C.h>


/* BEGIN CONFIGURATION */
#define DEBUG_BAUDRATE 115200

#if (defined USE_SOFTWARE_SERIAL || defined ARDUINO_ARCH_RP2040)
  #define S8_RX_PIN 6         // Rx pin which the S8 Tx pin is attached to (change if it is needed)
  #define S8_TX_PIN 7         // Tx pin which the S8 Rx pin is attached to (change if it is needed)
#else
  #define S8_UART_PORT  1     // Change UART port if it is needed
#endif
/* END CONFIGURATION */


#ifdef USE_SOFTWARE_SERIAL
  SoftwareSerial S8_serial(S8_RX_PIN, S8_TX_PIN);
#else
  #if defined(ARDUINO_ARCH_RP2040)
    REDIRECT_STDOUT_TO(Serial)    // to use printf (Serial.printf not supported)
    UART S8_serial(S8_TX_PIN, S8_RX_PIN, NC, NC);
  #else
    HardwareSerial S8_serial(S8_UART_PORT);
  #endif
#endif


#if defined(ARDUINO) && ARDUINO >= 100
#define printByte(args)  write(args);
#else
#define printByte(args)  print(args,BYTE);
#endif

uint8_t subscript[8] = {0x0, 0x0, 0x0, 0x1E, 0x03, 0x06, 0x0C, 0x1F };



S8_UART *sensor_S8;
S8_sensor sensor;

LiquidCrystal_I2C lcd(0x27,16,2);  // set the LCD address to 0x27 for a 16 chars and 2 line display

void setup() {

  lcd.init();
  lcd.backlight();
  lcd.setCursor(0,0);
  lcd.print("Starting up...");
  lcd.createChar(1, subscript);

  // Configure serial port, we need it for debug
  Serial.begin(DEBUG_BAUDRATE);

  // Wait port is open or timeout
  int i = 0;
  while (!Serial && i < 50) {
    delay(10);
    i++;
  }

  // First message, we are alive
  Serial.println("");
  Serial.println("Init");

  // Initialize S8 sensor
  S8_serial.begin(S8_BAUDRATE);
  sensor_S8 = new S8_UART(S8_serial);

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

  delay(1000);
  
  // Show basic S8 sensor info
  lcd.setCursor(0,0);
  lcd.print("Yay! SenseAir S8");
  lcd.setCursor(0,1);
  lcd.print("Firmware:");
  lcd.setCursor(9,1);
  lcd.print(sensor.firm_version);
  sensor.sensor_id = sensor_S8->get_sensor_ID();

  delay(1000);
}


void loop() {

  char buffer[17];

  // clear display
  lcd.clear();

  // Get CO2 measure
  sensor.co2 = sensor_S8->get_co2();
  lcd.setCursor(0,0);
  sprintf(buffer, "%4d ppm CO", sensor.co2);
  lcd.print(buffer);
  lcd.setCursor(11,0);
  lcd.printByte(1);  // subscript 2

  // Compare with PWM output
  //sensor.pwm_output = sensor_S8->get_PWM_output();
  //printf("PWM output = %0.0f ppm\n", (sensor.pwm_output / 16383.0) * 2000.0);

  // Wait 5 second for next measure
  delay(5000);
}
