#ifndef ContentScreen_h
#define ContentScreen_h

#include <TFT_eSPI.h>

// For polymorphism, one may need to use a pointer to the base class: https://www.ibm.com/docs/en/zos/2.4.0?topic=only-abstract-classes-c
class ContentScreen {
  private:
    TFT_eSPI* _tftRef;
    bool _hasChanged;
  public:
    virtual void drawScreen() = 0;
    virtual void updateContent() = 0;
    bool hasChanged();
    void setTftReference(TFT_eSPI* tft);
};

#endif