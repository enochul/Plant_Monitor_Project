#include "water_fsm.h"

bool manualOverride = false;
static int motorPinInternal;
static int water_state = WATER_OFF;

int dryThreshold = 2000;
int wetThreshold = 1500;

int water_plant = WATER_OFF;

void waterFSMInit(int motorPin) {
    motorPinInternal = motorPin;
    pinMode(motorPinInternal, OUTPUT);
    digitalWrite(motorPinInternal, LOW);
}

void fsmWaterController(int moisture) {
    if (manualOverride) {
        water_plant = WATER_ON;
        digitalWrite(motorPinInternal, HIGH);
        return;
    }
    switch (water_state) {
        case WATER_OFF:
            water_plant = WATER_OFF;
            if (moisture > dryThreshold) {
                water_state = WATER_ON;
            }
            break;

        case WATER_ON:
            water_plant = WATER_ON;
            if (moisture < wetThreshold) {
                water_state = WATER_OFF;
            }
            break;
    }

    digitalWrite(motorPinInternal, water_plant);
}
