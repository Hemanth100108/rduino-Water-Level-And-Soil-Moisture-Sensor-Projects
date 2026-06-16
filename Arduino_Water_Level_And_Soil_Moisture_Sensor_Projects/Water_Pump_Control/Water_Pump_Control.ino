#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 32
#define OLED_RESET -1

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// Pins
const int buttonPin = 12;
const int relayPin = 8;
const int buzzerPin = 7;

// Variables
bool pumpState = false;
bool lastButtonState = HIGH;
unsigned long lastDebounceTime = 0;
unsigned long debounceDelay = 50;

unsigned long pumpStartTime = 0;

void setup() {
  Serial.begin(9600);

  pinMode(buttonPin, INPUT_PULLUP);
  pinMode(relayPin, OUTPUT);
  pinMode(buzzerPin, OUTPUT);

  digitalWrite(relayPin, LOW);

  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    while (1);
  }

  display.clearDisplay();
  display.display();
}

void loop() {

  bool reading = digitalRead(buttonPin);

  if (reading != lastButtonState) {
    lastDebounceTime = millis();
  }

  if ((millis() - lastDebounceTime) > debounceDelay) {

    static bool buttonState = HIGH;

    if (reading != buttonState) {
      buttonState = reading;

      // Button pressed
      if (buttonState == LOW) {

        pumpState = !pumpState;

        digitalWrite(relayPin, pumpState);

        // Start timer when pump turns ON
        if (pumpState) {
          pumpStartTime = millis();
        }

        // Short beep
        tone(buzzerPin, 1000, 150);
      }
    }
  }

  lastButtonState = reading;

  // OLED Display
  display.clearDisplay();

  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);

  display.setCursor(0, 0);
  display.print("Water Pump");

  display.setCursor(0, 12);

  if (pumpState) {
    display.print("PUMP ON");
  } else {
    display.print("PUMP OFF");
  }

  // Bonus: Runtime
  display.setCursor(0, 24);

  if (pumpState) {
    unsigned long elapsed = (millis() - pumpStartTime) / 1000;

    display.print("Run:");
    display.print(elapsed);
    display.print("s");
  } else {
    display.print("Run: 0s");
  }

  display.display();

  delay(100);
}