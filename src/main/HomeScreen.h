#ifndef HomeScreen_h
#define HomeScreen_h

#include <Arduino.h>
#include <stdint.h>
#include <TFT_eSPI.h>
#include <examples/320x240/All_Free_Fonts_Demo/Free_Fonts.h>
#include "TimeRTC.h"
#include "ContentScreen.h"
#include "ScreenElement.h"
#include "Grove_Temperature_And_Humidity_Sensor.h"

#define DHTPIN D0 // or 15. Right side of serial port
#define DHTTYPE DHT11

class HomeScreen : public ContentScreen {
  private:
    // Holy shit these are classes.
    ScreenElement* _clockElement;
    TimeRTC* _timeRTC;
    uint8_t _hour;
    uint8_t _minute;
    uint8_t _second;

    ScreenElement* _dateElement;
    uint8_t _day;
    uint8_t _month;
    uint16_t _year;

    ScreenElement* _weekdayElement;
    const char* _weekday;

    // Temp / Humidity
    DHT* _dht;
    unsigned long _dhtMillisTimestamp;
    unsigned long _dhtReadingDelay = 5000;

    ScreenElement* _temperatureElement;
    float _temperature;

    ScreenElement* _humidityElement;
    float _humidity;
    
    void updateClockDisplay();
    void updateDateDisplay();
    void updateDHTDisplay();
  public:
    HomeScreen();
    virtual ~HomeScreen() override;
    virtual void drawScreen() override;
    virtual void drawScreenForced() override;
    virtual void updateContent() override;
};

#endif