// Define pin numbers for the LEDs
#define RED_LED1 3
#define GREEN_LED1 5
#define BLUE_LED1 6
#define RED_LED2 9
#define GREEN_LED2 10
#define BLUE_LED2 11

#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Adafruit_HTU21DF.h>

// Define the potentiometer pin
#define POT_PIN A1

// Create an instance of the HTU21D sensor
Adafruit_HTU21DF htu = Adafruit_HTU21DF();

// Initialize the LCD
LiquidCrystal_I2C lcd(0x27, 16, 2); // Set the LCD address to 0x27 for a 16 chars and 2 line display

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

  analogWrite(RED_LED1, 1024);
  delay(500);
  analogWrite(RED_LED1, 0);
  delay(500);

  // Start serial communication for debugging
  Serial.begin(9600);

  // Initialize the sensor
  if (!htu.begin()) {
    Serial.println("Couldn't find HTU21D sensor!");
    while (1);
  }

  // Initialize the potentiometer pin as input
  pinMode(POT_PIN, INPUT);
}

void loop() {
  // Read the sensor value from the HTU21D sensor
  float temperatureC = htu.readTemperature();
  Serial.print("temp: ");
  Serial.println(temperatureC);

  // Read the potentiometer, map its value to define the temperature sensitivity range
  int potValue = analogRead(POT_PIN);
  int tempRange = map(potValue, 0, 1023, 1, 5); // Very narrow range from 1 to 5 degrees

  // Calculate lower and upper bounds based on potentiometer setting
  float lowerBound = 25 - tempRange;
  float upperBound = 25 + tempRange;

  // Map temperature to RGB values using distinct dynamic ranges for the first set of LEDs
  int redIntensity1 = map(temperatureC, lowerBound, upperBound, 0, 255);      // Red more intense at higher temp
  int greenIntensity1 = map(temperatureC, lowerBound, upperBound, 255, 0);    // Green less intense at higher temp
  int blueIntensity1 = map(temperatureC, lowerBound, upperBound, 0, 127);     // Blue with a different range

  // For the second set of LEDs, use significantly different ranges
  int redIntensity2 = map(temperatureC, lowerBound, upperBound, 127, 255);    // Different range for mood effect
  int greenIntensity2 = map(temperatureC, lowerBound, upperBound, 0, 255);    // Full range for green
  int blueIntensity2 = map(temperatureC, lowerBound, upperBound, 127, 0);     // Inverse range for blue

  Serial.print("LED1 - RED: ");
  Serial.println(redIntensity1);
  Serial.print("LED1 - GREEN: ");
  Serial.println(greenIntensity1);
  Serial.print("LED1 - BLUE: ");
  Serial.println(blueIntensity1);
  
  Serial.print("LED2 - RED: ");
  Serial.println(redIntensity2);
  Serial.print("LED2 - GREEN: ");
  Serial.println(greenIntensity2);
  Serial.print("LED2 - BLUE: ");
  Serial.println(blueIntensity2);

  Serial.print("POT VAL: ");
  Serial.println(potValue);

  // Set the RGB LED colors for both sets of LEDs
  analogWrite(RED_LED1, redIntensity1);
  analogWrite(GREEN_LED1, greenIntensity1);
  analogWrite(BLUE_LED1, blueIntensity1);
  
  analogWrite(RED_LED2, redIntensity2);
  analogWrite(GREEN_LED2, greenIntensity2);
  analogWrite(BLUE_LED2, blueIntensity2);

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
