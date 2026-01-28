#pragma once
#include <Arduino.h>

extern float humidity;
extern float temperature;
extern int lightLevel;
extern int moisture;
extern bool isDayLight;

void PerceptionInit();
void PerceptionUpdate();
