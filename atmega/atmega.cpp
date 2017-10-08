/*
  Test, to test reading the id of a decawave chip
 */
#include <stdint.h>
#if ARDUINO >= 100
    #include "Arduino.h"
#else
    #include "WProgram.h"
#endif

const int SOLAR_INPUT_ADC_PIN    =A0;
const int BATTERY_ADC_PIN =A1;
const int LIGHT0_ENABLE_PIN      =2;

const float SOLAR_ACTIVE_LIMIT    =20.0;
const float BATTERY_POWER_LIMIT   =3.2*5;

const float FILTER_FACTOR = 0.1;

void setup() 
{
    Serial.begin(115200);
    Serial.println(F("Solarctrl Setup"));

    analogReference(DEFAULT);    
    pinMode(SOLAR_INPUT_ADC_PIN, INPUT);
    pinMode(BATTERY_ADC_PIN, INPUT);
    
    digitalWrite(LIGHT0_ENABLE_PIN, LOW);
    pinMode(LIGHT0_ENABLE_PIN, OUTPUT);
    
    Serial.println(F(""));
    Serial.println(F("Setup done"));
}

uint8_t _n=0;
uint16_t _light0_intensity = 0;
float _solar = 0;
float _battery = 0;
void loop() 
{
    float solar = analogRead(SOLAR_INPUT_ADC_PIN)  * 50/1024.0;
    float battery = analogRead(BATTERY_ADC_PIN) * 50/1024.0;

    // Filter over time
    _solar   = _solar  *(1-FILTER_FACTOR) + solar*FILTER_FACTOR;
    _battery = _battery*(1-FILTER_FACTOR) + battery*FILTER_FACTOR;
    
    _light0_intensity += 10;
    if (_solar > SOLAR_ACTIVE_LIMIT)    _light0_intensity = 0;
    if (_battery < BATTERY_POWER_LIMIT) _light0_intensity = 0;

    if (_light0_intensity > 255) _light0_intensity=255;
    analogWrite(LIGHT0_ENABLE_PIN, _light0_intensity);

    if (((_n++)&0xF) == 0)
    {
        //Serial.print((_n++)&3);
        Serial.print(" Solar: "); Serial.print(_solar);
        Serial.print(" Battery: "); Serial.print(_battery);
        Serial.print(" Light0: "); Serial.print(_light0_intensity);
        Serial.println("");
    }
    delay(10);
}
