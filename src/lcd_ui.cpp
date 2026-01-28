#include "lcd_ui.h"
#include <LiquidCrystal_I2C.h>
#include "perception.h"
#include "water_fsm.h"

// LCD instance (owned here)
LiquidCrystal_I2C lcd(0x27, 16, 2);

// Timing
static unsigned long lastUpdate = 0;
const unsigned long LCD_INTERVAL = 1000;

void lcdInit() {
    lcd.init();
    lcd.backlight();
    lcd.clear();
}

void lcdUpdate() {
    unsigned long now = millis();
    if (now - lastUpdate < LCD_INTERVAL) return;
    lastUpdate = now;

    lcd.clear();

    // -------- ROW 0 --------
    lcd.setCursor(0, 0);
    lcd.print("L:");
    lcd.print(lightLevel);
    lcd.print(" M:");
    lcd.print(moisture);

    // -------- ROW 1 --------
    lcd.setCursor(0, 1);
    lcd.print(isDayLight ? "DAY " : "NIGHT ");
    lcd.print("W:");
    lcd.print(water_plant == WATER_ON ? "ON " : "OFF ");
    lcd.print((int)(temperature * 9 / 5 + 32));
    lcd.print("F");
}
