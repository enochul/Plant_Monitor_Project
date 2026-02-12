#include "perception.h"
#include <DHT.h>
#include "adc_utils.h"

//----------PIN DECLARATIONS----------//
#define DHTPIN 13
#define DHTTYPE DHT11
#define MOIS_PIN 14
#define LIGHT_PIN 35

const int dayThreshold = 1800; //used to make daylight binary

DHT dht(DHTPIN, DHTTYPE);
//----------DATA VARIABLES----------//
float humidity;
float temperature;
int lightLevel;
int moisture;
bool isDayLight = false;

//----------INITALIZER FUNCTION----------//
void PerceptionInit() {
    analogReadResolution(12); //adjusts how precise the reading will be: this is pretty precise
    analogSetAttenuation(ADC_11db); //expands the reading range from 0V to appros 3.3V
    dht.begin();
}

//----------UPDATE FUNCTION----------//
void PerceptionUpdate() {
    humidity = dht.readHumidity();
    temperature = dht.readTemperature();

    if (isnan(humidity) || isnan(temperature)) return; //used if sensors are not reading

    lightLevel = readAveragedADC(LIGHT_PIN, 10, 100);
    moisture   = readAveragedADC(MOIS_PIN, 20, 100);

    isDayLight = (lightLevel > dayThreshold);
}