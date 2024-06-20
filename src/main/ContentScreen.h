#ifndef ContentScreen_h
#define ContentScreen_h

// Definitions can be found in TFT_eSPI.h, Free_Fonts.h and the like
#define TFTSCREEN_DEFAULT_BG_COLOR TFT_BLACK
#define TFTSCREEN_DEFAULT_TEXT_COLOR TFT_GREEN
#define TFTSCREEN_DEFAULT_TEXT_SIZE 1
#define TFTSCREEN_DEFAULT_FONT FF6
#define TFTSCREEN_DEFAULT_PADDING 0   // Kinda temp
#define TFTSCREEN_DEFAULT_TEXT_DATUM MC_DATUM

#include <TFT_eSPI.h>

// For polymorphism, one may need to use a pointer to the base class: https://www.ibm.com/docs/en/zos/2.4.0?topic=only-abstract-classes-c
class ContentScreen {
  protected:
    TFT_eSPI* _tftRef;
    bool _isRedrawQueued;
  public:
    virtual ~ContentScreen();
    virtual void drawScreen() = 0;
    virtual void updateContent() = 0;
    bool hasChanged();
    void setTftReference(TFT_eSPI* tft);
};

#endif