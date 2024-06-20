#include "ScreenElement.h"
#include "TextSettings.h"
#include "Point.h"
#include "Logging.h"


TFT_eSPI* ScreenElement::_tftRef = nullptr;

void ScreenElement::setTftReference(TFT_eSPI *tftRef) {
  _tftRef = tftRef;
}

ScreenElement::ScreenElement(Point* topLeftCorner, Point* bottomRightCorner) {
  _topLeft = topLeftCorner;
  _bottomRight = bottomRightCorner;
  _middle = Point::getMiddlePoint(_topLeft, _bottomRight);
}

ScreenElement::ScreenElement(Point* topLeftCorner, Point* bottomRightCorner, TextSettings* textSettings) 
  : ScreenElement(topLeftCorner, bottomRightCorner) {   // Idk if this works
  _textSettings = textSettings;
}

ScreenElement::~ScreenElement() {
  // Should the point objects be deleted? 
  // I'm thinking none of the references should be deleted,
  // since they may be passed amongs eachother, possibly.
  // _middle can be removed though.
  Logging::writeln("Deleting Screen Element");
  delete _middle;
}

void ScreenElement::drawElement(const char* content) {
  _textSettings->apply();
  _tftRef->drawString(content, _middle->x, _middle->y);
  _isRedrawQueued = false;
}

void ScreenElement::queueForRedraw(bool isQueued) {
  _isRedrawQueued = isQueued;
}

bool ScreenElement::isRedrawQueued() {
  return _isRedrawQueued;
}