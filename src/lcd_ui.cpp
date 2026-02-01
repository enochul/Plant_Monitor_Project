#include "lcd_ui.h"
#include <LiquidCrystal_I2C.h>
#include "perception.h"
#include "water_fsm.h"

//---LCD instance (owned here)---//
LiquidCrystal_I2C lcd(0x27, 16, 2);

//------------Timing------------//
static unsigned long lastUpdate = 0;
const unsigned long LCD_INTERVAL = 1000;

//-----INITALIZER FUNCTION------//
void lcdInit() {
    lcd.init();
    lcd.backlight();
    lcd.clear();
}

//-------UPDATE FUNCTION--------//
void lcdUpdate() {
    unsigned long now = millis();
    if (now - lastUpdate < LCD_INTERVAL) return;
    lastUpdate = now;

    char line0[17]; // 16 chars + null terminator
    char line1[17];

    // Build Row 0: L:4095 M:1500
    // %4d means "an integer exactly 4 spaces wide"
    snprintf(line0, sizeof(line0), "L:%4d M:%4d", lightLevel, moisture);

    // Build Row 1: DAY  W:OFF  72F
    // %-5s means "string left-aligned in 5 spaces"
    int tempF = (int)(temperature * 9 / 5 + 32);
    const char* dayStr = isDayLight ? "DAY  " : "NIGHT";
    const char* waterStr = isWatering ? "ON " : "OFF";
    snprintf(line1, sizeof(line1), "%s W:%s %3dF", dayStr, waterStr, tempF);

    // Send to LCD
    lcd.setCursor(0, 0);
    lcd.print(line0);
    lcd.setCursor(0, 1);
    lcd.print(line1);
}