#include "HomeScreen.h"
#include "ContentScreen.h"
#include "TimeRTC.h"
#include "TFTScreen.h"
#include "Logging.h"

#include <TFT_eSPI.h>
#include <examples/320x240/All_Free_Fonts_Demo/Free_Fonts.h>

HomeScreen::HomeScreen() {
  _timeRTC = TimeRTC::getInstance();  // NOTE: Shared instance
  updateClockDisplay();
  updateDateDisplay();
  _clockFont = &FreeMonoBold12pt7b;
  _isRedrawQueued = true;
}

HomeScreen::~HomeScreen() {
  Logging::writeln("HomeScreen deleted!");
}

void HomeScreen::drawScreen() {
  const uint16_t sidePadding = 6;
  const uint16_t clockXPos = TFTSCREEN_MAX_X - sidePadding;
  const uint16_t clockYPos = TFTSCREEN_STATUSBAR_THICKNESS + 10;
  const uint16_t dateXPos = clockXPos;
  const uint16_t dateYPos = clockYPos + 40;
  const uint16_t weekdayXPos = clockXPos;
  const uint16_t weekdayYPos = dateYPos + 20;

  // Format time
  char clockStr[9];
  sprintf(clockStr, "%.2d:%.2d:%.2d", _hour, _minute, _second);

  // Format date
  char dateStr[11];
  sprintf(dateStr, "%.2d/%.2d/%.4d", _day, _month, _year);

  // Almost a have to do thing is to choose the correct font/size/etc.
  // Maybe use template pattern?
  _tftRef->setTextDatum(TR_DATUM);
  _tftRef->setTextColor(TFT_GREEN, TFT_BLACK);
  _tftRef->setFreeFont(_clockFont);
  _tftRef->setTextSize(2);
  _tftRef->drawString(clockStr, clockXPos, clockYPos);

  _tftRef->setTextSize(1);
  _tftRef->drawString(dateStr, dateXPos, dateYPos);

  _tftRef->drawString(_weekday, weekdayXPos, weekdayYPos);
}

void HomeScreen::updateContent() {
  _timeRTC->synchronize();

  if(_timeRTC->getSeconds() != _second) {
    updateClockDisplay();
    if(_timeRTC->getDay() != _day) {
      updateDateDisplay();
    }
    _isRedrawQueued = true;
  }
}

void HomeScreen::updateClockDisplay() {
  _second = _timeRTC->getSeconds();
  _minute = _timeRTC->getMinutes();
  _hour = _timeRTC->getHours();
}

void HomeScreen::updateDateDisplay() {
  _day = _timeRTC->getDay();
  _month = _timeRTC->getMonth();
  _year = _timeRTC->getYear();
  _weekday = _timeRTC->getWeekday();
}