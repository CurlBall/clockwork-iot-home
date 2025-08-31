#include "TFTInstance.h"
#include "Logging.h"
#include <TFT_eSPI.h>

TFT_eSPI* TFTInstance::_tft = nullptr;

TFTInstance::TFTInstance() {
  // Frick all to see here
}

TFT_eSPI* TFTInstance::getTftInstance() {
  if(_tft == nullptr) {
    Logging::writeln("Creating TFT_eSPI object");
    _tft = new TFT_eSPI();
    Logging::writelnf("TFT_eSPI initialized. Version: %s", LoggingLevel::Normal, TFT_ESPI_VERSION);
    _tft->begin();
    _tft->setRotation(3);
  }

  return _tft;
}