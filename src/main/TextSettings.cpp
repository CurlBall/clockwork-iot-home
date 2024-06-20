#include "TextSettings.h"
#include "TFTScreen.h"
#include "ContentScreen.h"
#include "Logging.h"
#include <stdint.h>
#include <TFT_eSPI.h>
#include <examples/320x240/All_Free_Fonts_Demo/Free_Fonts.h>

TFT_eSPI* TextSettings::_tftRef = nullptr;

// 
void TextSettings::setTftReference(TFT_eSPI *tftRef) {
  if(_tftRef != nullptr) {
    _tftRef = tftRef;
  }
  else {
    Logging::writeln("TextSettings::_tftRef already set!", LoggingLevel::Warning);
  }
}

TextSettings::TextSettings() {
  if(_tftRef != nullptr) {
    Logging::writeln("TextSettings::_tftRef wasn't set", LoggingLevel::Cataclysmic);
    delay(10000);
  }

  _font = TFTSCREEN_DEFAULT_FONT;
  _bgColor = TFTSCREEN_DEFAULT_BG_COLOR;
  _textPadding = TFTSCREEN_DEFAULT_PADDING;
  _textColor = TFTSCREEN_DEFAULT_TEXT_COLOR;
  _textSize = TFTSCREEN_DEFAULT_TEXT_SIZE;
  _textDatum = TFTSCREEN_DEFAULT_TEXT_DATUM;
}

void TextSettings::apply() {
  _tftRef->setFreeFont(_font);
  _tftRef->setTextColor(_textColor, _bgColor);
  _tftRef->setTextPadding(_textPadding);
  _tftRef->setTextSize(_textSize);
  _tftRef->setTextDatum(_textDatum);
}

void TextSettings::setFont(const GFXfont* font) {
  _font = font;
}

void TextSettings::setBgColor(uint32_t bgColor) {
  _bgColor = bgColor;
}

void TextSettings::setTextPadding(uint16_t padding) {
  _textPadding = padding;
}

void TextSettings::setTextColor(uint32_t color) {
  _textColor = color;
}

void TextSettings::setTextSize(uint8_t size) {
  _textSize = size;
}

void TextSettings::setTextDatum(uint8_t datum) {
  _textDatum = datum;
}
