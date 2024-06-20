#ifndef ScreenElement_h
#define ScreenElement_h

#include "Point.h"
#include "TextSettings.h"
#include <TFT_eSPI.h>

class ScreenElement {
  protected:
    static TFT_eSPI* _tftRef;
    bool _isRedrawQueued;
    Point* _referencePoint;   // Text will be drawn from here, works in conjunction with TextSettings::_textDatum
    TextSettings* _textSettings;
  public:
    static void setTftReference(TFT_eSPI* tftRef);
    ScreenElement(Point* referencePoint);
    ScreenElement(Point* referencePoint, TextSettings* textSettings);
    virtual ~ScreenElement();
    void drawElement(const char* content);
    void queueForRedraw(bool isChanged = true);
    bool isRedrawQueued();
};

#endif