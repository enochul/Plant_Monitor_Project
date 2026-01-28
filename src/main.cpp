#include <Arduino.h>
#include "perception.h"
#include "water_fsm.h"
#include "lcd_ui.h"
#include "blynk_ui.h"

#define MOTOR_PIN 27

void setup() {
    Serial.begin(115200);
    //----------INITALIZER FUNCTIONS----------//
    PerceptionInit(); //sensor initializing
    waterFSMInit(MOTOR_PIN); //Water FSM initalizing
    lcdInit(); //LCD Screen initalizing
    blynkInit(); // Blynk initalizing
}

void loop() {

    //----------LOOP UPDATE FUNCTIONS----------//
    PerceptionUpdate(); //updating Sensor Readings
    fsmWaterController(moisture); //Updating Water FSM
    lcdUpdate(); //Updating LCD Screen
    blynkUpdate(); //Updating Blynk I/O platform
}
