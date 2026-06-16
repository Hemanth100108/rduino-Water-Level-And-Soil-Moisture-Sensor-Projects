#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 32
#define OLED_RESET -1

Adafruit_SSD1306 display(
  SCREEN_WIDTH,
  SCREEN_HEIGHT,
  &Wire,
  OLED_RESET
);

// Pins
const int waterSensorPin = A0;
const int relayPin = 8;
const int buzzerPin = 7;

// Calibration values
const int sensorMin = 0;      // Empty tank
const int sensorMax = 700;    // Full tank

// Thresholds
const int lowThreshold = 30;   // Start filling
const int fullThreshold = 80;  // Stop filling

// Pump state
bool pumpState = false;
bool fullBeepPlayed = false;

// Minimum level reached
int minWaterLevel = 100;

// ---------- Moving Average Filter ----------
const int NUM_SAMPLES = 10;
int samples[NUM_SAMPLES];
int sampleIndex = 0;
long total = 0;

// Smooth display value
float displayedLevel = 0;

void setup()
{
  Serial.begin(9600);

  pinMode(relayPin, OUTPUT);
  pinMode(buzzerPin, OUTPUT);

  digitalWrite(relayPin, LOW);

  // Initialize sample array
  for (int i = 0; i < NUM_SAMPLES; i++)
  {
    samples[i] = 0;
  }

  if (!display.begin(
      SSD1306_SWITCHCAPVCC,
      0x3C))
  {
    while (1);
  }

  display.clearDisplay();
  display.display();
}

void loop()
{
  // ===== Moving Average Filter =====

  total -= samples[sampleIndex];

  samples[sampleIndex] =
      analogRead(waterSensorPin);

  total += samples[sampleIndex];

  sampleIndex++;

  if (sampleIndex >= NUM_SAMPLES)
  {
    sampleIndex = 0;
  }

  int sensorValue = total / NUM_SAMPLES;

  // Convert to %
  int waterLevel = map(
      sensorValue,
      sensorMin,
      sensorMax,
      0,
      100);

  waterLevel = constrain(
      waterLevel,
      0,
      100);

  // Smooth percentage transition
  displayedLevel =
      displayedLevel +
      (waterLevel - displayedLevel) * 0.1;

  int smoothLevel =
      (int)displayedLevel;

  // Record minimum level
  if (smoothLevel < minWaterLevel)
  {
    minWaterLevel = smoothLevel;
  }

  // ===== Automatic Filling Logic =====

  if (smoothLevel < lowThreshold)
  {
    pumpState = true;
    fullBeepPlayed = false;
  }
  else if (smoothLevel >= fullThreshold)
  {
    pumpState = false;

    if (!fullBeepPlayed)
    {
      tone(buzzerPin, 1000, 300);
      fullBeepPlayed = true;
    }
  }

  // Relay Control
  digitalWrite(relayPin, pumpState);

  // If your relay is ACTIVE LOW use:
  // digitalWrite(relayPin, !pumpState);

  // ===== OLED =====

  display.clearDisplay();

  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);

  display.setCursor(0, 0);
  display.print("Water:");
  display.print(smoothLevel);
  display.print("%");

  display.setCursor(0, 10);

  if (pumpState)
  {
    display.print("PUMP: ON");
  }
  else
  {
    display.print("PUMP: OFF");
  }

  display.setCursor(0, 20);
  display.print("Min:");
  display.print(minWaterLevel);
  display.print("%");

  display.display();

  // Serial Monitor
  Serial.print("Raw=");
  Serial.print(sensorValue);

  Serial.print("  Level=");
  Serial.print(smoothLevel);

  Serial.print("%  Pump=");
  Serial.println(
      pumpState ? "ON" : "OFF");

  delay(200);
}