#include "water_fsm.h"

//---------VARIABLE INITALIZATIONS----------//
bool manualOverride = false;
static int motorPinInternal;
static int water_state = WATER_OFF;
int dryThreshold = 2000;
int wetThreshold = 1500;
bool isWatering = false;
unsigned long lastWaterTime = 0;
const long waterDuration = 2000; // sets pump timer for two seconds
const long wait_period = 60000; // sets the time we wait to check moisture after watering
const long bootBuffer = 15000; // buffer for a hard limit on the soonest water will turn on

//----------INITALIZER FUNCTION----------//
void waterFSMInit(int motorPin) {
    motorPinInternal = motorPin;
    pinMode(motorPinInternal, OUTPUT);
    digitalWrite(motorPinInternal, LOW);
}

//----------WATERING ACTION LOGIC FUNCTION----------//
void perform_watering() {
    //update the current time every call
    unsigned long currentMillis = millis();
    // if we haven't reached the boot buffer yet just exit
    if (currentMillis < bootBuffer) return;
    /* START LOGIC:   If we are NOT currently watering AND:
    (It's been 60s) OR (It's the first time) OR (User pressed the button) */
    if (!isWatering) {
        if (currentMillis - lastWaterTime >= wait_period || lastWaterTime == 0 || manualOverride) {
            digitalWrite(motorPinInternal, HIGH);
            lastWaterTime = currentMillis; // record when the watering starts
            isWatering = true;
            //reset the manual flag to prevent infinite loops and overwatering
            manualOverride = false;
        }
    }
    // STOP LOGIC: if we ARE currently watering and it has been two seconds 
    if (isWatering && (currentMillis - lastWaterTime >= waterDuration)) {
        digitalWrite(motorPinInternal, LOW);
        isWatering = false;
    }
}

//----------UPDATE FUNCTION----------//
void fsmWaterController(int moisture) {
    //---allowing for manual overide---//
    if (manualOverride) { //happens in the blynk file
        perform_watering();
    }
    //-----FSM SWITCH STATEMENTS-----//
    switch (water_state) {
        case WATER_OFF:
            if (moisture > dryThreshold) {
                water_state = WATER_ON;
            }
            break;

        case WATER_ON:
            perform_watering();
            // only exit this state if we aren't mid-pulse AND the soil is wet enough
            if (!isWatering && moisture < wetThreshold) {
                water_state = WATER_OFF;
            }
            break;
    }
}
