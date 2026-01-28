#pragma once
#include <Arduino.h>

//allows these variables to be visable to other files
extern float humidity;
extern float temperature;
extern int lightLevel;
extern int moisture;
extern bool isDayLight;

void PerceptionInit();
void PerceptionUpdate();
