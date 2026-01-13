#include <Arduino.h>

#define LDR_PIN 35 // LDR

// Tune these by experiment
const int dayThreshold = 1800; // above this = "daylight"

void setup()
{
  Serial.begin(9600);
}

void loop()
{
  int lightLevel = analogRead(LDR_PIN);

  bool isDayLight = lightLevel > dayThreshold;

  // What to show on screen to the user
  if (isDayLight) {
    Serial.println("Daylight");
  } else {
    Serial.println("No daylight");
  }

  Serial.print("Raw ADC: ");
  Serial.println(lightLevel);

  // Optional debugging info while tuning brightness settings
  Serial.print("Raw ADC: ");
  Serial.println(lightLevel);

  Serial.println("-----");
  delay(700);
}
