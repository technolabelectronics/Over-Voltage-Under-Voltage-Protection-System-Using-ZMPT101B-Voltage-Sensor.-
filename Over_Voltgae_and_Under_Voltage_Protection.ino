#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include <ZMPT101B.h>

// Set the LCD address to 0x27 for a 16 chars and 2 line display
LiquidCrystal_I2C lcd(0x27, 16, 2);
 
#define SENSITIVITY 500.0f
#define RELAY_PIN 2 // Define the relay control pin
 
// ZMPT101B sensor output connected to ADC pin 34
// and the voltage source frequency is 50 Hz.
ZMPT101B voltageSensor(34, 50.0);
void setup() {
  Serial.begin(115200);
  // Change the sensitivity value based on value you got from the calibrate
  // example.
  voltageSensor.setSensitivity(SENSITIVITY);
  
  lcd.begin();   // initialize the LCD
  lcd.backlight();  // Turn on the blacklight and print a message.

  // Set up the relay pin as output
  pinMode(RELAY_PIN, OUTPUT);
  digitalWrite(RELAY_PIN, LOW); // Turn relay off initially
   // Display initial message on LCD
  lcd.setCursor(0, 0);
  lcd.print("Voltage Monitor");
  delay(2000);
  lcd.clear();
}
 
void loop() {
  // read the voltage and then print via Serial
  float voltage = voltageSensor.getRmsVoltage();
  Serial.println(voltage);
  
  // Display voltage on the LCD
  delay(500);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Voltage: ");
  lcd.print(voltage);
  lcd.print("V "); // Clear any trailing characters
    // Check for under-voltage or over-voltage conditions
  if (voltage < 180.0) {
    lcd.setCursor(0, 1);
    lcd.print("Under Voltage ");
    digitalWrite(RELAY_PIN, LOW); // Turn relay off
  } else if (voltage > 230.0) {
    lcd.setCursor(0, 1);
    lcd.print("Over Voltage  ");
    digitalWrite(RELAY_PIN, LOW); // Turn relay off
  } else {
    lcd.setCursor(0, 1);
    lcd.print("Normal         ");
    digitalWrite(RELAY_PIN, HIGH); // Turn relay on
  }
}
