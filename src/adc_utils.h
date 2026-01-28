#pragma once
#include <Arduino.h>

int readAveragedADC(int pin, int samples = 10, unsigned long interval = 100);
