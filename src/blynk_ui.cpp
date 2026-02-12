#define BLYNK_PRINT Serial

#include "blynk_ui.h"
#include <WiFi.h>
#include "perception.h"
#include "water_fsm.h"

//----------BLYNK CREDENTIALS----------//
#define BLYNK_TEMPLATE_ID "TMPL2NthM_I1x"
#define BLYNK_TEMPLATE_NAME "Plant Monitor"
#define BLYNK_AUTH_TOKEN    "YOUR_DEVICE_AUTH_TOKEN"

#include <BlynkSimpleEsp32.h>

//-------------WIFI INFO-------------//
const char* ssid = "YOUR_WIFI";
const char* pass = "YOUR_PASSWORD";

//---Thresholds (shared with FSM)---//
extern int dryThreshold;
extern int wetThreshold;

//---------Manual override---------//
static bool manualWater = false;

void blynkInit() {
    Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);
}

//-----Push sensor data → app-----//
void blynkUpdate() {
    Blynk.run();

    static unsigned long lastPush = 0;
    if (millis() - lastPush >= 1000) {
        lastPush = millis();
        Blynk.virtualWrite(V0, moisture);
        Blynk.virtualWrite(V1, lightLevel);
        Blynk.virtualWrite(V2, temperature * 9 / 5 + 32);
        Blynk.virtualWrite(V3, humidity);
        Blynk.virtualWrite(V4, isWatering);
    }
}

//---------INBOUND CONTROLS---------//

// Dry threshold slider
BLYNK_WRITE(V5) {
    dryThreshold = param.asInt();
}
// Wet threshold slider
BLYNK_WRITE(V6) {
    wetThreshold = param.asInt();
}
// Manual water button
extern bool manualOveride;
BLYNK_WRITE(V7) {
    if (param.asInt() == 1) {
        manualOveride = true;
    }
}