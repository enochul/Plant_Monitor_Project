:echo globpath(&runtimepath, 'colors/tokyonight.vim')
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
const int dryThreshold = 2200; // below this = too dry
const int wetThreshold = 3300; // above this p= too dry

void setup() {
  Serial.begin(115200);
  dht.begin();

  lcd.init(); //Turn on LCD screen brain
  lcd.backlight(); //Turn on LCD backlight
  pinMode(motor1A , OUTPUT);
  pinMode(motor2A , OUTOPUT);

}

void loop() {
	//Humidity, Temperature, and Light readings
  float humidity = dht.readHumidity();
  float temperature = dht.readTemperature();
  int lightLevel = analogRead(LIGHT_PIN);
  int moisture = analogRead(MOIS_PIN);
  if (isnan(humidity) || isnan(temperature)) return;

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

void fmsWaterController (){
    static int water_state = 0;

    switch (water_state)
    case 0:
        //action turn off water
        if (moisture < wetthreshold){
            water_state = 1;
        }
        break;
    case 1:
        //action turn on water
        if (moisture > wetthreshold){
            water_stae = 0;
        }
        break;
    default:
        water_state = 0;
        break;
}

