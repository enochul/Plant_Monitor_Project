#pragma once
#include <Arduino.h>

extern bool manualOverride; //allowing for overide from blynk app
enum WaterState { WATER_OFF, WATER_ON };

extern int water_plant;
extern int dryThreshold;
extern int wetThreshold;

void waterFSMInit(int motorPin);
void fsmWaterController(int moisture);
