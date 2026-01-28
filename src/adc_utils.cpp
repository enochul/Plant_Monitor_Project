#include "adc_utils.h"


//----------ADC PIN CLEANUP FUNCTION----------//
int readAveragedADC(int pin, int samples, unsigned long interval) {
    //---PREVENTS ADDRESSING OUT OF MEMORY---//
    if (pin < 0 || pin >= 40) {
        return 0;
    }
    //---------TIME/READING VARIABLES--------//
    static unsigned long last_read_time[40] = {0};
    static int last_value[40] = {0};
    unsigned long now = millis();

    //---------CREATES AVERAGE VALUE--------//
    if (now - last_read_time[pin] >= interval) {
        last_read_time[pin] = now;

        long sum = 0;
        for (int i = 0; i < samples; i++) {
            sum += analogRead(pin);
        }
        last_value[pin] = sum / samples;
    }
    return last_value[pin];
}
