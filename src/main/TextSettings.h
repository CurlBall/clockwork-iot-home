#ifndef TextSettings_h
#define TextSettings_h

#include <TFT_eSPI.h>
#include <examples/320x240/All_Free_Fonts_Demo/Free_Fonts.h>

class TextSettings {
  private:
    static TFT_eSPI* _tftRef;
    const GFXfont* _font;
    uint32_t _bgColor;
    uint16_t _textPadding;
    uint32_t _textColor;
    uint8_t _textSize;
    uint8_t _textDatum;
  public:
    static void setTftReference(TFT_eSPI* tftRef);
    TextSettings();
    void apply();
    void setFont(const GFXfont* font);
    void setBgColor(uint32_t bgColor);
    void setTextPadding(uint16_t padding);
    void setTextColor(uint32_t color);
    void setTextSize(uint8_t size);
    void setTextDatum(uint8_t datum);
};

#endif