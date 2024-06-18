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
  _clockFont = &FreeMonoBold12pt7b;
  _hasChanged = true;
}

void HomeScreen::drawScreen() {
  // Format time for display
  char clockStr[9];
  sprintf(clockStr, "%.2d:%.2d:%.2d", _hour, _minute, _second);
  Logging::write("New clockStr: ");
  Logging::writeln(clockStr);

  // Almost a have to do thing is to choose the correct font/size/etc.
  // Maybe use template pattern?
  _tftRef->setTextColor(TFT_GREEN, TFT_BLACK);
  _tftRef->setFreeFont(_clockFont);
  _tftRef->setTextSize(2);

  _tftRef->drawString(clockStr, 90, TFTSCREEN_STATUSBAR_THICKNESS + 10);
}

void HomeScreen::updateContent() {
  _timeRTC->synchronize();
  uint8_t second = _timeRTC->getSeconds();
  if(second != _second) {
    updateClockDisplay();
    _hasChanged = true;
  }
}

void HomeScreen::updateClockDisplay() {
  _second = _timeRTC->getSeconds();
  _minute = _timeRTC->getMinutes();
  _hour = _timeRTC->getHours();
}