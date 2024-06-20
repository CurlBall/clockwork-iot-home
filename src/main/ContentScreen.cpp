#include "ContentScreen.h"
#include "Logging.h"

ContentScreen::~ContentScreen() {
  Logging::writeln("ContentScreen child deleted!");
}

bool ContentScreen::hasChanged() {
  if(_isRedrawQueued == true) {
    _isRedrawQueued = false;
    return true;
  }
  else {
    return false;
  }
}

void ContentScreen::setTftReference(TFT_eSPI* tft) {
  if(_tftRef != nullptr) {
    _tftRef = tft;
  }
  else {
    Logging::writeln("ContentScreen subclass already has reference to TFT_eSPI", LoggingLevel::Warning);
  }
}