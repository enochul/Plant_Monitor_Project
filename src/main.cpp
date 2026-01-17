#include <Arduino.h>
#include <DHT.h> // Humidity & Temperature sensor
#include <Wire.h> // for the display screen
#include <LiquidCrystal_I2C.h> // for the display screen

#define DHTPIN 13     // Set the pin connected to the DHT11 data pin
#define MOIS_PIN 14 // Soil moisture module
#define LIGHT_PIN 35 // Photoresistor
#define motor1A 27 // Pump pin
#define motor2A 26 // Pump pin

#define DHTTYPE DHT11  // DHT 11
DHT dht(DHTPIN, DHTTYPE);

int page = 0;
LiquidCrystal_I2C lcd(0x27, 16, 2);

const int dayThreshold = 1800; // above this = "daylight"

void setup() {
  Serial.begin(115200);
  dht.begin();
}

void loop() {
  float humidity = dht.readHumidity();
  float temperature = dht.readTemperature();

  int lightLevel = analogRead(LIGHT_PIN);

  bool isDayLight = lightLevel > dayThreshold;

  // What to show on screen to the user
  if (isDayLight) {
    Serial.print("Daylight    ");
  } else {
    Serial.print("No daylight ");
  }

  Serial.print("Raw ADC: ");
  Serial.println(lightLevel);
  Serial.print("Humidity: ");
  Serial.println(humidity);
  Serial.print("Temperature: ");
  Serial.println(temperature);
  Serial.println("-----");
  delay(1700);
}