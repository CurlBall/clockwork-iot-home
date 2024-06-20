#ifndef HomeScreen_h
#define HomeScreen_h

#include <Arduino.h>
#include <stdint.h>
#include <TFT_eSPI.h>
#include <examples/320x240/All_Free_Fonts_Demo/Free_Fonts.h>
#include "TimeRTC.h"
#include "ContentScreen.h"
#include "ScreenElement.h"

class HomeScreen : public ContentScreen {
  private:
    const GFXfont* _clockFont;

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
    
    void updateClockDisplay();
    void updateDateDisplay();
  public:
    HomeScreen();
    virtual ~HomeScreen() override;
    virtual void drawScreen() override;
    virtual void drawScreenForced() override;
    virtual void updateContent() override;
};

#endif