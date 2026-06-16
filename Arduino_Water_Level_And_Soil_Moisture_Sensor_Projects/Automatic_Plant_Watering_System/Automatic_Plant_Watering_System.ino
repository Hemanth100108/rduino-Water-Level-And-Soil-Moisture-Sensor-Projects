#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1

Adafruit_SSD1306 display(
  SCREEN_WIDTH,
  SCREEN_HEIGHT,
  &Wire,
  OLED_RESET
);

// Pins
const int waterSensorPin = A0;
const int soilSensorPin  = A1;
const int relayPin       = 8;
const int buzzerPin      = 7;

// Calibration Values
const int waterMin = 0;
const int waterMax = 700;

const int soilWet = 300;
const int soilDry = 800;

// Thresholds
const int tankThreshold = 20;   // Minimum water level
const int soilThreshold = 40;   // Soil considered dry below this

bool pumpState = false;
bool tankEmptyAlarm = false;

// ---------- Moving Average ----------
const int NUM_SAMPLES = 10;

int waterSamples[NUM_SAMPLES];
int soilSamples[NUM_SAMPLES];

int sampleIndex = 0;

long waterTotal = 0;
long soilTotal = 0;

// ---------- Smooth Display ----------
float displayedWaterLevel = 0;
float displayedSoilLevel = 0;

void setup()
{
  Serial.begin(9600);

  pinMode(relayPin, OUTPUT);
  pinMode(buzzerPin, OUTPUT);

  digitalWrite(relayPin, LOW);

  // Initialize buffers
  for (int i = 0; i < NUM_SAMPLES; i++)
  {
    waterSamples[i] = 0;
    soilSamples[i] = 0;
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

  waterTotal -= waterSamples[sampleIndex];
  soilTotal  -= soilSamples[sampleIndex];

  waterSamples[sampleIndex] =
      analogRead(waterSensorPin);

  soilSamples[sampleIndex] =
      analogRead(soilSensorPin);

  waterTotal += waterSamples[sampleIndex];
  soilTotal  += soilSamples[sampleIndex];

  sampleIndex++;

  if (sampleIndex >= NUM_SAMPLES)
  {
    sampleIndex = 0;
  }

  int waterRaw = waterTotal / NUM_SAMPLES;
  int soilRaw  = soilTotal / NUM_SAMPLES;

  // ===== Convert to Percentages =====

  int waterLevel =
      map(waterRaw,
          waterMin,
          waterMax,
          0,
          100);

  waterLevel =
      constrain(waterLevel,
                0,
                100);

  int soilMoisture =
      map(soilRaw,
          soilDry,
          soilWet,
          0,
          100);

  soilMoisture =
      constrain(soilMoisture,
                0,
                100);

  // ===== Smooth Percentage Changes =====

  displayedWaterLevel =
      displayedWaterLevel +
      (waterLevel - displayedWaterLevel) * 0.05;

  displayedSoilLevel =
      displayedSoilLevel +
      (soilMoisture - displayedSoilLevel) * 0.05;

  int smoothWater =
      (int)displayedWaterLevel;

  int smoothSoil =
      (int)displayedSoilLevel;

  // ===== Pump Logic =====

  bool soilDryCondition =
      (smoothSoil < soilThreshold);

  bool enoughWater =
      (smoothWater > tankThreshold);

  if (soilDryCondition &&
      enoughWater)
  {
    pumpState = true;
  }
  else
  {
    pumpState = false;
  }

  // Relay Control
  digitalWrite(relayPin, pumpState);

  // If relay is ACTIVE LOW use:
  // digitalWrite(relayPin, !pumpState);

  // ===== Tank Empty Alarm =====

  if (smoothWater <= tankThreshold)
  {
    if (!tankEmptyAlarm)
    {
      tone(buzzerPin, 1000, 300);
      tankEmptyAlarm = true;
    }
  }
  else
  {
    tankEmptyAlarm = false;
  }

  // ===== OLED Display =====

  display.clearDisplay();

  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);

  display.setCursor(0, 0);
  display.print("Soil:");
  display.print(smoothSoil);
  display.print("%");

  display.setCursor(0, 15);
  display.print("Tank:");
  display.print(smoothWater);
  display.print("%");

  display.setCursor(0, 30);

  if (pumpState)
    display.print("Pump: ON");
  else
    display.print("Pump: OFF");

  display.setCursor(0, 50);

  if (smoothWater <= tankThreshold)
  {
    display.print("TANK EMPTY!");
  }
  else if (pumpState)
  {
    display.print("Watering Plant...");
  }
  else
  {
    display.print("Soil Moisture Good");
  }

  display.display();

  // ===== Serial Monitor =====

  Serial.print("Soil=");
  Serial.print(smoothSoil);
  Serial.print("%  ");

  Serial.print("Tank=");
  Serial.print(smoothWater);
  Serial.print("%  ");

  Serial.print("Pump=");
  Serial.println(
      pumpState ? "ON" : "OFF");

  delay(200);
}