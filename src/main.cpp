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

        //----------THRESHOLDS----------//
const int dayThreshold = 1800; // above this = "daylight"
const int dryThreshold = 2000; // below this = too dry
const int wetThreshold = 1500; // above this = too wet

        //----------TIMER VARIABLES----------//
unsigned long last_serial_print = 0;
unsigned long last_LCD_update = 0;

const unsigned long SERIAL_INTERVAL = 1000;
const unsigned long LCD_INTERVAL = 1000;

enum { WATER_OFF, WATER_ON };
int water_plant = WATER_OFF;

int readAveragedADC(int pin, int samples = 10 , unsigned long interval = 500) {
  static unsigned long last_read_time[40] = {0};
  static int last_value[40] = {0};
  unsigned long now = millis();

  if (now - last_read_time[pin] >= interval) {
      last_read_time[pin] = now;

      long sum = 0;
      for (int i = 0; i < samples; i++){
          sum += analogRead(pin);
      }
      last_value[pin] = sum / samples;
    }
  retrun last_value[pin]
  }

void fsmWaterController (int moisture){
    static int water_state = 0;

    switch (water_state){
    case 0:
        water_plant = WATER_OFF;
        if (moisture > dryThreshold){
            water_state = 1;
        }
        break;
    case 1:
        water_plant = WATER_ON;
        if (moisture < wetThreshold){
            water_state = 0;
        }
        break;
    default:
        water_state = 0;
        break;
    }

    digitalWrite(motor1A , water_plant);

}

void setup() {
  Serial.begin(115200);
  dht.begin();

  lcd.init(); //Turn on LCD screen brain
  lcd.backlight(); //Turn on LCD backlight
  pinMode(motor1A , OUTPUT);
  pinMode(motor2A , OUTPUT);

}

void loop() {
	//Humidity, Temperature, and Light readings
  float humidity = dht.readHumidity();
  float temperature = dht.readTemperature();
  int lightLevel = readAveragedADC(LIGHT_PIN, 10);
  int moisture   = readAveragedADC(MOIS_PIN, 15);
  if (isnan(humidity) || isnan(temperature)) return;

  bool isDayLight = lightLevel > dayThreshold;

  // What to show on screen to the user
  if (millis() - last_serial_print >= SERIAL_INTERVAL) {
      last_serial_print = millis();

    if (isDayLight) {
        Serial.print("Daylight    ");
    } else {
        Serial.print("No daylight ");
    }
    Serial.print("Light: ");
    Serial.print(lightLevel);
    Serial.print("Moisture: ");
    Serial.print(moisture);
    Serial.print("Temp: ");
    Serial.print((temperature*(9/5)+32), 1);
    Serial.print("Humidity: ");
    Serial.print(humidity, 1);
    Serial.print("Water: ");
    Serial.println(water_plant == WATER_ON ? "ON" : "OFF");
    Serial.println("-----");
  }
  fsmWaterController (moisture);
}

