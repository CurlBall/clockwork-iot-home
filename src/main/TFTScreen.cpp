#include "TFT_eSPI.h"
#include "TFTScreen.h"
#include "Logging.h"

TFTScreen::TFTScreen() {
  _numOfScreens = 0;
  _currentScreenIndex = -1;
  _tft.begin();
  _tft.setRotation(3);
  _tft.fillScreen(TFT_BLACK);

  // Screen test
  _tft.drawPixel(0, 0, TFT_MAGENTA);     // Top left
  _tft.drawPixel(0, 239, TFT_MAGENTA);   // Bottom Left
  _tft.drawPixel(319, 239, TFT_MAGENTA); // Bottom Right
  _tft.drawPixel(319, 0, TFT_MAGENTA);   // Top Right

  Logging::writeln("Setting text color");
  _tft.setTextColor(TFT_GREENYELLOW);
  Logging::writeln("Setting text size");
  _tft.setTextSize(5);
  Logging::writeln("Writing text");
  _tft.drawString("Starting...", 20, 20, 1);
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
  _activeScreen->updateContent();
  if(_activeScreen->hasChanged()) {
    _activeScreen->drawScreen();
  }
}

void TFTScreen::nextScreen() {
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
  if(_currentScreenIndex == -1) {
    nextScreen();
  }
}