#include "water_fsm.h"

//---------VARIABLE INITALIZATIONS----------//
bool manualOverride = false;
static int motorPinInternal;
static int water_state = WATER_OFF;
int dryThreshold = 2000;
int wetThreshold = 1500;
int water_plant = WATER_OFF;

//----------INITALIZER FUNCTION----------//
void waterFSMInit(int motorPin) {
    motorPinInternal = motorPin;
    pinMode(motorPinInternal, OUTPUT);
    digitalWrite(motorPinInternal, LOW);
}

//----------UPDATE FUNCTION----------//
void fsmWaterController(int moisture) {
    //---allowing for maual overide---//
    if (manualOverride) { //happens in the blynk file
        water_plant = WATER_ON;
        digitalWrite(motorPinInternal, HIGH);
        return;
    }
    //-----FSM SWITCH STATEMENTS-----//
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
