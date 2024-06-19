#include <Arduino.h>
#include <TFT_eSPI.h>
#include <examples/320x240/All_Free_Fonts_Demo/Free_Fonts.h>
#include "TFTScreen.h"
#include "Logging.h"
#include "ContentScreen.h"

TFTScreen::TFTScreen() {
  _numOfScreens = 0;
  _currentScreenIndex = -1;

  //_defaultBGcolor = TFT_BLACK;
  //_defaultTextColor = TFT_GREEN;
  //_defaultFont = &FreeMonoBold12pt7b;


  _tft.begin();
  _tft.setRotation(3);
  _tft.fillScreen(TFTSCREEN_DEFAULT_BG_COLOR);
  _tft.setTextColor(TFTSCREEN_DEFAULT_TEXT_COLOR);
  _tft.setFreeFont(TFTSCREEN_DEFAULT_FONT);

  // Screen test
  if(DEBUG_ON) {
    _tft.drawPixel(0, 0, TFT_MAGENTA);     // Top left
    _tft.drawPixel(0, 239, TFT_MAGENTA);   // Bottom Left
    _tft.drawPixel(319, 239, TFT_MAGENTA); // Bottom Right
    _tft.drawPixel(319, 0, TFT_MAGENTA);   // Top Right
  }

  _tft.setTextSize(2);
  _tft.setTextDatum(MC_DATUM);
  _tft.drawString("KLOCKWORK", TFTSCREEN_MAX_X / 2, TFTSCREEN_MAX_Y / 2);
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
  _tft.fillScreen(TFTSCREEN_DEFAULT_BG_COLOR);

  // Redraw StatusBar [TEMP] (Should do with the colours as I did with TFTSCREEN_DEFAULT_BG_COLOR and the like)
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
  if(_numOfScreens == TFTSCREEN_MAX_CSCREENS) {
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