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
const int buttonPin      = 13;

// Calibration Values
const int waterMin = 0;
const int waterMax = 700;

const int soilWet = 300;
const int soilDry = 800;

// Page Control
int currentPage = 0;

// Button Debounce
bool lastButtonState = HIGH;
unsigned long lastDebounceTime = 0;
const int debounceDelay = 50;

// Moving Average
const int NUM_SAMPLES = 10;

int waterSamples[NUM_SAMPLES];
int soilSamples[NUM_SAMPLES];

long waterTotal = 0;
long soilTotal = 0;

int sampleIndex = 0;

// Smooth Display
float displayedWater = 0;
float displayedSoil = 0;

void setup()
{
  Serial.begin(9600);

  pinMode(buttonPin, INPUT_PULLUP);

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
  // =====================
  // PAGE SWITCHING
  // =====================

  bool reading = digitalRead(buttonPin);

  if (reading != lastButtonState)
  {
    lastDebounceTime = millis();
  }

  if ((millis() - lastDebounceTime) > debounceDelay)
  {
    static bool buttonState = HIGH;

    if (reading != buttonState)
    {
      buttonState = reading;

      if (buttonState == LOW)
      {
        currentPage++;

        if (currentPage > 2)
        {
          currentPage = 0;
        }
      }
    }
  }

  lastButtonState = reading;

  // =====================
  // MOVING AVERAGE FILTER
  // =====================

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

  int waterRaw =
      waterTotal / NUM_SAMPLES;

  int soilRaw =
      soilTotal / NUM_SAMPLES;

  // =====================
  // CONVERT TO %
  // =====================

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

  // =====================
  // SMOOTH DISPLAY
  // =====================

  displayedWater =
      displayedWater +
      (waterLevel - displayedWater) * 0.03;

  displayedSoil =
      displayedSoil +
      (soilMoisture - displayedSoil) * 0.03;

  int smoothWater =
      (int)displayedWater;

  int smoothSoil =
      (int)displayedSoil;

  // =====================
  // OLED DISPLAY
  // =====================

  display.clearDisplay();

  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);

  // PAGE 1
  if (currentPage == 0)
  {
    display.setCursor(0,0);
    display.print("PAGE 1");

    display.setCursor(0,15);
    display.print("Water Tank");

    display.setCursor(0,30);
    display.print("Level: ");
    display.print(smoothWater);
    display.print("%");

    display.setCursor(0,50);

    if (smoothWater > 60)
      display.print("Status: GOOD");
    else if (smoothWater > 20)
      display.print("Status: LOW");
    else
      display.print("TANK EMPTY");
  }

  // PAGE 2
  else if (currentPage == 1)
  {
    display.setCursor(0,0);
    display.print("PAGE 2");

    display.setCursor(0,15);
    display.print("Soil Moisture");

    display.setCursor(0,30);
    display.print("Level: ");
    display.print(smoothSoil);
    display.print("%");

    display.setCursor(0,50);

    if (smoothSoil < 40)
      display.print("SOIL DRY");
    else
      display.print("SOIL GOOD");
  }

  // PAGE 3
  else
  {
    display.setCursor(0,0);
    display.print("IRRIGATION DASH");

    display.setCursor(0,18);
    display.print("Tank: ");
    display.print(smoothWater);
    display.print("%");

    display.setCursor(0,34);
    display.print("Soil: ");
    display.print(smoothSoil);
    display.print("%");

    display.setCursor(0,52);

    if (smoothWater <= 20)
      display.print("Tank Empty!");
    else if (smoothSoil < 40)
      display.print("Water Needed");
    else
      display.print("System Normal");
  }

  display.display();

  delay(100);
}