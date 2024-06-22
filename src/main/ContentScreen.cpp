#include "ContentScreen.h"
#include "Logging.h"
#include "TFTInstance.h"

ContentScreen::ContentScreen() {
  Logging::writeln("[ContentScreen] Getting TFTref");
  _tftRef = TFTInstance::getTftInstance();
}

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
