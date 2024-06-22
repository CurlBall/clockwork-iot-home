#include "HomeScreen.h"
#include "ContentScreen.h"
#include "TimeRTC.h"
#include "Logging.h"
#include "TFTScreen.h"
#include "Point.h"
#include "TextSettings.h"
#include <TFT_eSPI.h>
#include <examples/320x240/All_Free_Fonts_Demo/Free_Fonts.h>

HomeScreen::HomeScreen() {
  _timeRTC = TimeRTC::getInstance();  // NOTE: Shared instance
  
  // Frontend "made easy"
  TextSettings* clockSettings = new TextSettings();
  clockSettings->setTextDatum(TR_DATUM);
  clockSettings->setTextSize(2);
  clockSettings->setBgColor(TFTSCREEN_DEFAULT_BG_COLOR);
  
  TextSettings* dateSettings = new TextSettings();
  dateSettings->setTextDatum(TR_DATUM);
  dateSettings->setBgColor(TFTSCREEN_DEFAULT_BG_COLOR);
  dateSettings->setTextPadding(150);

  // This doesn't exactly make things simpler.
  int sidePadding = 6;
  int topPadding = 10;
  int clockXPos = TFTSCREEN_MAX_X - sidePadding;
  int clockYPos = TFTSCREEN_STATUSBAR_THICKNESS + topPadding;
  _clockElement = new ScreenElement(
    new Point(clockXPos, clockYPos),
    clockSettings
  );

  const uint16_t dateXPos = clockXPos;
  const uint16_t dateYPos = clockYPos + 48;
  _dateElement = new ScreenElement(
    new Point(dateXPos, dateYPos),
    dateSettings
  );

  const uint16_t weekdayXPos = clockXPos;
  const uint16_t weekdayYPos = dateYPos + 20;
  _weekdayElement = new ScreenElement(
    new Point(weekdayXPos, weekdayYPos),
    dateSettings
  );

  delay(2000);

  updateClockDisplay();
  updateDateDisplay();
  drawScreenForced();
}

HomeScreen::~HomeScreen() {
  Logging::writeln("HomeScreen deleted!");
}

void HomeScreen::drawScreen() {
  // Format time
  char clockStr[9];
  sprintf(clockStr, "%.2d:%.2d:%.2d", _hour, _minute, _second);

  // Format date
  char dateStr[11];
  sprintf(dateStr, "%.2d/%.2d/%.4d", _day, _month, _year);

  // Only clock is being drawn...
  if(_clockElement->isRedrawQueued()) {
    _clockElement->drawElement(clockStr);
  }
  if(_dateElement->isRedrawQueued()) {
    _dateElement->drawElement(dateStr);
  }
  if(_weekdayElement->isRedrawQueued()) {
    _weekdayElement->drawElement(_weekday);
  }
}

void HomeScreen::drawScreenForced() {
  _clockElement->queueForRedraw();
  _dateElement->queueForRedraw();
  _weekdayElement->queueForRedraw();
  drawScreen();
}

void HomeScreen::updateContent() {
  _timeRTC->synchronize();

  if(_timeRTC->getSeconds() != _second) {
    updateClockDisplay();
    _clockElement->queueForRedraw();
    if(_timeRTC->getDay() != _day) {
      updateDateDisplay();
      _dateElement->queueForRedraw();
      _weekdayElement->queueForRedraw();
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