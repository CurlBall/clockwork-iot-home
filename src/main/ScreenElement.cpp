#include "ScreenElement.h"
#include "TextSettings.h"
#include "Point.h"
#include "Logging.h"
#include "TFTInstance.h"


TFT_eSPI* ScreenElement::_tftRef = nullptr;

ScreenElement::ScreenElement(Point* referencePoint) 
  : ScreenElement(referencePoint, new TextSettings()) {}

ScreenElement::ScreenElement(Point* referencePoint, TextSettings* textSettings) {
  if(_tftRef == nullptr) {
    _tftRef = TFTInstance::getTftInstance();
  }
  
  _referencePoint = referencePoint;
  _textSettings = textSettings;
}

ScreenElement::~ScreenElement() {
  Logging::writeln("Deleting Screen Element");
  delete _referencePoint;
}

void ScreenElement::drawElement(const char* content) {
  _textSettings->apply();
  _tftRef->drawString(content, _referencePoint->x, _referencePoint->y);
  _isRedrawQueued = false;
}

void ScreenElement::queueForRedraw(bool isQueued) {
  _isRedrawQueued = isQueued;
}

bool ScreenElement::isRedrawQueued() {
  return _isRedrawQueued;
}

void ScreenElement::clear(uint8_t characters) {
  char spaces[characters + 1];
  for(uint8_t i = 0; i <= characters; i++) {
    spaces[i] = ' ';
  }

  drawElement(spaces);
}