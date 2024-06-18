#include <Arduino.h>
#include <TFT_eSPI.h>
#include "TFTScreen.h"
#include "Logging.h"
#include "ContentScreen.h"

TFTScreen::TFTScreen() {
  _numOfScreens = 0;
  _currentScreenIndex = -1;
  _tft.begin();
  _tft.setRotation(3);
  _tft.fillScreen(TFT_BLACK);

  // Screen test
  if(DEBUG_ON) {
    _tft.drawPixel(0, 0, TFT_MAGENTA);     // Top left
    _tft.drawPixel(0, 239, TFT_MAGENTA);   // Bottom Left
    _tft.drawPixel(319, 239, TFT_MAGENTA); // Bottom Right
    _tft.drawPixel(319, 0, TFT_MAGENTA);   // Top Right
  }

  Logging::writeln("Setting text color");
  _tft.setTextColor(TFT_GREENYELLOW);
  Logging::writeln("Setting text size");
  _tft.setTextSize(5);
  _tft.setTextFont(1);
  Logging::writeln("Writing text");
  _tft.drawString("KLOCKWORK", 20, 20);
  Logging::writeln("Constructor done");
}

TFTScreen* TFTScreen::getInstance() {
  // In-function static variables like the one below is only defined once.
  // All but the first call to getInstance() will only run the return statement.
  static TFTScreen* instanceRef = new TFTScreen();
  return instanceRef;
}

void TFTScreen::update() {
  if(_numOfScreens == 0) {
    return;
  }

  // If possible, update screen content, 
  // then redraw the screens if a change has been made.
  // Relies on NOT filling the entire screen before redrawing.
  _activeScreen->updateContent();
  if(_activeScreen->hasChanged()) {
    Logging::writeln("TFTScreen: Drawing screens");
    _activeScreen->drawScreen();
  }
}

void TFTScreen::nextScreen() {
  // Clear screen (Should probably use an attribute for this, BG colour or something)
  _tft.fillScreen(TFT_BLACK);

  // Redraw StatusBar [TEMP]
  _tft.fillRect(0, 0, TFTSCREEN_MAX_X, TFTSCREEN_STATUSBAR_THICKNESS, TFT_DARKCYAN);
  _tft.drawLine(0, TFTSCREEN_STATUSBAR_THICKNESS, TFTSCREEN_MAX_X, TFTSCREEN_STATUSBAR_THICKNESS, TFT_WHITE);

  // Choose next screen and assign it as active.
  _currentScreenIndex++;
  if(_currentScreenIndex == _numOfScreens) {
    _currentScreenIndex = 0;
  }

  _activeScreen = _allScreens[_currentScreenIndex];
}

bool TFTScreen::addScreen(ContentScreen* newScreen) {
  if(_numOfScreens == MAX_NUM_OF_SCREENS) {
    Logging::writeln("Max number of screens exceeded!", LoggingLevel::Error);
    return false;
  }

  newScreen->setTftReference(&_tft);
  _allScreens[_numOfScreens] = newScreen;
  _numOfScreens++;
  if(_numOfScreens == 1) {
    nextScreen();
  }

  return true;
}