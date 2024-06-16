#include "ContentScreen.h"
#include "Logging.h"

bool ContentScreen::hasChanged() {
  return _hasChanged;
}

void ContentScreen::setTftReference(TFT_eSPI* tft) {
  if(_tftRef != nullptr) {
    _tftRef = tft;
  }
  else {
    Logging::writeln("ContentScreen subclass already has reference to TFT_eSPI", LoggingLevel::Warning);
  }
}