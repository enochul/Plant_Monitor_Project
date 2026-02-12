#include "water_fsm.h"

//---------VARIABLE INITALIZATIONS----------//
bool manualOverride = false;
static int motorPinInternal;
static int water_state = WATER_OFF;
int dryThreshold = 2000;
int wetThreshold = 1500;
bool isWatering = false;
unsigned long currentMillis = millis();
unsigned long lastWaterTime = 0;
const long waterDuration = 2000; // sets pump timer for two seconds
const long wait_period = 60000; // sets the time we wait to check moisture after watering
const long bootBuffer = 15000; // buffer for a hard limit on the soonest water will turn on

// Helper functions to handle inverted logic in one place
void pumpOn() {
    digitalWrite(motorPinInternal, LOW); // Change to HIGH if logic is normal
    isWatering = true;
    Serial.println(">>> PUMP ACTIVATED");
}

void pumpOff() {
    digitalWrite(motorPinInternal, HIGH); // Change to LOW if logic is normal
    isWatering = false;
    Serial.println(">>> PUMP DEACTIVATED");
}

//----------INITALIZER FUNCTION----------//
void waterFSMInit(int motorPin) {
    motorPinInternal = motorPin;
    pinMode(motorPinInternal, OUTPUT);
    digitalWrite(motorPinInternal, HIGH);
}

//----------WATERING ACTION LOGIC FUNCTION----------//
void perform_watering() {
    //update the current time every call
    currentMillis = millis();
    // if we haven't reached the boot buffer yet just exit
    if (currentMillis < bootBuffer) {
        pumpOff();
        return;
    }
    /* START LOGIC:   If we are NOT currently watering AND:
    (It's been 60s) OR (It's the first time) OR (User pressed the button) */
    if (!isWatering) {
        if (currentMillis - lastWaterTime >= wait_period || lastWaterTime == 0 || manualOverride) {
            pumpOn();
            lastWaterTime = currentMillis; // record when the watering starts
            //reset the manual flag to prevent infinite loops and overwatering
            manualOverride = false;
        }
    }
    // STOP LOGIC: if we ARE currently watering and it has been two seconds 
    if (isWatering && (currentMillis - lastWaterTime >= waterDuration)) {
        pumpOff();
    }
}

//----------UPDATE FUNCTION----------//
void fsmWaterController(int moisture) {
    //---allowing for manual overide---//
    if (manualOverride) { //happens in the blynk file
        water_state = WATER_ON;
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