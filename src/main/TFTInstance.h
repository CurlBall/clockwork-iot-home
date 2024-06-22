#ifndef TFTSingleton_h
#define TFTSingleton_h

#include <TFT_eSPI.h>

class TFTInstance {
  private:
    static TFT_eSPI* _tft;
    TFTInstance();
  public:
    static TFT_eSPI* getTftInstance();
};

#endif