#include "ContentScreen.h"
#include "Logging.h"

bool ContentScreen::hasChanged() {
  if(_hasChanged == true) {
    _hasChanged = false;
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