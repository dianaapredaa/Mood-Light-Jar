// Define pin numbers for the LEDs
#define RED_LED1 3
#define GREEN_LED1 5
#define BLUE_LED1 6
#define RED_LED2 9
#define GREEN_LED2 10
#define BLUE_LED2 11

#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// Define the temperature sensor pin and potentiometer pin
#define TEMP_SENSOR_PIN A0
#define POT_PIN A1

// Initialize the LCD
LiquidCrystal_I2C lcd(0x20, 16, 2); // Set the LCD address to 0x27 for a 16 chars and 2 line display


void setup() {
  // Initialize the LCD
  lcd.init();
  lcd.backlight();
  
  // Initialize all RGB LED pins as outputs
  pinMode(RED_LED1, OUTPUT);
  pinMode(GREEN_LED1, OUTPUT);
  pinMode(BLUE_LED1, OUTPUT);
  pinMode(RED_LED2, OUTPUT);
  pinMode(GREEN_LED2, OUTPUT);
  pinMode(BLUE_LED2, OUTPUT);

  // Start serial communication for debugging
  Serial.begin(9600);

  // Initialize the sensor and potentiometer pins as inputs
  pinMode(TEMP_SENSOR_PIN, INPUT);
  pinMode(POT_PIN, INPUT);
}

void loop() {
  // Read the sensor value from the temperature sensor
  int sensorValue = analogRead(TEMP_SENSOR_PIN);
  
  // Convert the sensor reading to voltage
  float voltage = sensorValue * (5.0 / 1023.0);

  // Convert the voltage to temperature in Celsius
  // TMP36 outputs 10mV per degree Celsius above 500mV at 0°C
  float temperatureC = (voltage - 0.5) * 100.0;

  // Read the potentiometer, map its value to define the temperature sensitivity range
  int potValue = analogRead(POT_PIN);
  int tempRange = map(potValue, 0, 1023, 1, 5); // Very narrow range from 1 to 5 degrees

  // Calculate lower and upper bounds based on potentiometer setting
  float lowerBound = 25 - tempRange / 2.0;
  float upperBound = 25 + tempRange / 2.0;

  // Map temperature to RGB values using dynamic range
  int redIntensity = map(temperatureC, lowerBound, upperBound, 0, 255); // Red more intense at higher temp
  int greenIntensity = map(abs(25 - temperatureC), 0, tempRange / 2.0, 255, 0); // Green peaks at middle of range
  int blueIntensity = map(temperatureC, lowerBound, upperBound, 255, 0); // Blue more intense at lower temp

  // Set the RGB LED colors for both sets of LEDs
  analogWrite(RED_LED1, redIntensity);
  analogWrite(GREEN_LED1, greenIntensity);
  analogWrite(BLUE_LED1, blueIntensity);
  
  analogWrite(RED_LED2, redIntensity);
  analogWrite(GREEN_LED2, greenIntensity);
  analogWrite(BLUE_LED2, blueIntensity);

  // Print the temperature and RGB values to the Serial Monitor
  Serial.print("Temperature: ");
  Serial.print(temperatureC);
  Serial.print(" C, Range: ");
  Serial.print(tempRange);
  Serial.println(" C");

  // Display temperature and range on LCD
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Temp: ");
  lcd.print(temperatureC);
  lcd.print(" C");

  lcd.setCursor(0, 1);
  lcd.print("Sensitivity: ");
  lcd.print(tempRange / 2.0);
  
  // Wait for 500 milliseconds before repeating the loop
  delay(500);
}
