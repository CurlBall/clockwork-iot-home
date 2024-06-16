#ifndef TFTScreen_h
#define TFTScreen_h

#include "ContentScreen.h"
#include <TFT_eSPI.h>
#define MAX_NUM_OF_SCREENS 8

// Driver IC: ILI9341 | 2 different variations can be used in User_Setup.h
// So I have the newest TFT lib being used, but it might require some further config to have it not start with a black screen.
class TFTScreen {
  private:
    TFT_eSPI _tft;
    ContentScreen* _activeScreen;
    ContentScreen* _allScreens[MAX_NUM_OF_SCREENS];
    uint8_t _numOfScreens;
    uint8_t _currentScreenIndex;
    TFTScreen();
  public:
    void update();
    void nextScreen();
    bool addScreen(ContentScreen* newScreen);
    static TFTScreen* getInstance();
    // bool removeScreen(???);
};

#endif