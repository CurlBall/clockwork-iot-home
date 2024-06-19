#ifndef TFTScreen_h
#define TFTScreen_h

#include "ContentScreen.h"
#include <TFT_eSPI.h>
#include <examples/320x240/All_Free_Fonts_Demo/Free_Fonts.h>

// Screen constraints
// Should be kept customizable
#define TFTSCREEN_MAX_CSCREENS 8
#define TFTSCREEN_MAX_Y 239
#define TFTSCREEN_MAX_X 319
#define TFTSCREEN_STATUSBAR_THICKNESS 36        // 'Thickness' to semantically make sense if going for either vertical/horizontal statusbar
#define TFTSCREEN_CONTENTSCREEN_THICKNESS 203   // 'Thickness' to semantically make sense if going for either vertical/horizontal statusbar

// Driver IC: ILI9341 | 2 different variations can be used in User_Setup.h
// So I have the newest TFT lib being used, but it might require some further config to have it not start with a black screen.
class TFTScreen {
  private:
    TFT_eSPI _tft;
    ContentScreen* _activeScreen;
    ContentScreen* _allScreens[TFTSCREEN_MAX_CSCREENS];
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