#include "perception.h"
#include <DHT.h>
#include "adc_utils.h"

#define DHTPIN 13
#define DHTTYPE DHT11
#define MOIS_PIN 14
#define LIGHT_PIN 35

const int dayThreshold = 1800;

DHT dht(DHTPIN, DHTTYPE);

float humidity;
float temperature;
int lightLevel;
int moisture;
bool isDayLight = false;

void PerceptionInit() {
    analogReadResolution(12);
    analogSetAttenuation(ADC_11db);
    dht.begin();
}

void PerceptionUpdate() {
    humidity = dht.readHumidity();
    temperature = dht.readTemperature();

    if (isnan(humidity) || isnan(temperature)) return;

    lightLevel = readAveragedADC(LIGHT_PIN, 10);
    moisture   = readAveragedADC(MOIS_PIN, 15);

    isDayLight = (lightLevel > dayThreshold);
}
