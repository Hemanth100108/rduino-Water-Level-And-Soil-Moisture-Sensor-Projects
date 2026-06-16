#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// OLED Configuration
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 32
#define OLED_RESET -1

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// Pins
const int waterSensorPin = A0;
const int redLED = 8;
const int yellowLED = 9;
const int greenLED = 10;
const int buzzer = 7;

// Calibration values
const int sensorMin = 0;      // Empty tank
const int sensorMax = 700;    // Full tank

void setup() {
  Serial.begin(9600);

  pinMode(redLED, OUTPUT);
  pinMode(yellowLED, OUTPUT);
  pinMode(greenLED, OUTPUT);
  pinMode(buzzer, OUTPUT);

  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println("OLED failed");
    while (1);
  }

  display.clearDisplay();
  display.display();
}

void loop() {

  // Read water sensor
  int sensorValue = analogRead(waterSensorPin);

  // Convert to %
  int waterLevel = map(sensorValue,
                       sensorMin,
                       sensorMax,
                       0,
                       100);

  waterLevel = constrain(waterLevel, 0, 100);

  // Turn everything OFF first
  digitalWrite(redLED, LOW);
  digitalWrite(yellowLED, LOW);
  digitalWrite(greenLED, LOW);
  noTone(buzzer);

  String status;

  // Status logic
  if (waterLevel >= 80) {
    status = "FULL";

    digitalWrite(greenLED, HIGH);

    // Buzzer when full
    tone(buzzer, 1000);

  } 
  else if (waterLevel >= 40) {
    status = "MEDIUM";

    digitalWrite(yellowLED, HIGH);
  } 
  else {
    status = "LOW";

    digitalWrite(redLED, HIGH);
  }

  // OLED Display
  display.clearDisplay();

  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);

  display.setCursor(0, 0);
  display.print("Water:");
  display.print(waterLevel);
  display.print("%");

  display.setCursor(0, 12);
  display.print("Status:");
  display.print(status);

  // Graphical Bar
  display.drawRect(0, 24, 120, 8, SSD1306_WHITE);

  int barWidth = map(waterLevel, 0, 100, 0, 118);

  display.fillRect(
    1,
    25,
    barWidth,
    6,
    SSD1306_WHITE
  );

  display.display();

  // Serial Monitor
  Serial.print("Sensor = ");
  Serial.print(sensorValue);
  Serial.print("  Water = ");
  Serial.print(waterLevel);
  Serial.print("%  ");
  Serial.println(status);

  delay(1000);
}