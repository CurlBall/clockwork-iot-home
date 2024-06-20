#include "ScreenElement.h"
#include "TextSettings.h"
#include "Point.h"
#include "Logging.h"


TFT_eSPI* ScreenElement::_tftRef = nullptr;

void ScreenElement::setTftReference(TFT_eSPI *tftRef) {
  _tftRef = tftRef;
}

ScreenElement::ScreenElement(Point* referencePoint) {
  _referencePoint = referencePoint;
}

ScreenElement::ScreenElement(Point* referencePoint, TextSettings* textSettings) 
  : ScreenElement(referencePoint) {   // Idk if this works
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