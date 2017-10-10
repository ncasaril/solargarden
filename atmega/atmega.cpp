/*
  Test, to test reading the id of a decawave chip
 */
#include <stdint.h>
#if ARDUINO >= 100
    #include "Arduino.h"
#else
    #include "WProgram.h"
#endif

const int SOLAR_INPUT_ADC_PIN    = A0;
const int BATTERY_ADC_PIN        = A1;
const int LIGHT0_ENABLE_PIN      =  2;

const float SOLAR_ACTIVE_LIMIT    = 25.0;
const float SOLAR_V_CAL           = 25.0/18.13;
const float BATTERY_POWER_LIMIT   = 3.2*5;
const float BATTERY_V_CAL         = 20.6/15.70;

const float FILTER_FACTOR = 0.01;
const int  MID_LIGHT = 16;
const int  MAX_LIGHT = 64;
const int  LIGHT_INCREMENT = 1;

uint8_t _n=0;
uint16_t _light0_intensity = 0;
float _solar = 0;
float _battery = 0;

void setup() 
{
    Serial.begin(115200);
    Serial.println(F("Solarctrl Setup"));

    analogReference(DEFAULT);    
    //analogReference(EXTERNAL);    
    digitalWrite(SOLAR_INPUT_ADC_PIN, LOW);
    digitalWrite(BATTERY_ADC_PIN, LOW);
    pinMode(SOLAR_INPUT_ADC_PIN, INPUT);
    pinMode(BATTERY_ADC_PIN, INPUT);
    
    digitalWrite(LIGHT0_ENABLE_PIN, LOW);
    pinMode(LIGHT0_ENABLE_PIN, OUTPUT);
    
    Serial.println(F(""));
    Serial.println(F("Setup done"));

    _solar = analogRead(SOLAR_INPUT_ADC_PIN)/1023.0 * 50.0 * SOLAR_V_CAL;
    _battery = analogRead(BATTERY_ADC_PIN)/1023.0 * 50.0 * BATTERY_V_CAL;
}

void loop() 
{
    float solar = analogRead(SOLAR_INPUT_ADC_PIN)/1023.0 * 50.0 * SOLAR_V_CAL;
    float battery = analogRead(BATTERY_ADC_PIN)/1023.0 * 50.0 * BATTERY_V_CAL;

    // Filter over time
    _solar   = _solar  *(1-FILTER_FACTOR) + solar*FILTER_FACTOR;
    _battery = _battery*(1-FILTER_FACTOR) + battery*FILTER_FACTOR;
    
    _light0_intensity += LIGHT_INCREMENT;
    if (_solar > SOLAR_ACTIVE_LIMIT)    _light0_intensity = 0;
    if (_battery < BATTERY_POWER_LIMIT) _light0_intensity = 0;

    if (_light0_intensity > MAX_LIGHT) _light0_intensity=MAX_LIGHT;
    analogWrite(LIGHT0_ENABLE_PIN, _light0_intensity);

    if (((_n++)&0xF) == 0)
    {
        Serial.print(" Solar: "); Serial.print(_solar);
        Serial.print(" Battery: "); Serial.print(_battery);
        Serial.print(" Light0: "); Serial.print(_light0_intensity);
        Serial.println("");
    }
    
    delay(100);
}
