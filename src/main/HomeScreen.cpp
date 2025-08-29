#include <Arduino.h>
#include "HomeScreen.h"
#include "ContentScreen.h"
#include "TimeRTC.h"
#include "Logging.h"
#include "TFTScreen.h"
#include "Point.h"
#include "TextSettings.h"
#include <TFT_eSPI.h>
#include <examples/320x240/All_Free_Fonts_Demo/Free_Fonts.h>
#include "Grove_Temperature_And_Humidity_Sensor.h"

HomeScreen::HomeScreen() : ContentScreen() {
  // Get components
  _timeRTC = TimeRTC::getInstance();  // NOTE: Shared instance
  
  Logging::writeln("Initializing DHT");
  _dht = new DHT(DHTPIN, DHTTYPE);
  _dht->begin();
  Logging::writeln("DHT initialized");
  
  // Frontend "made easy"
  TextSettings* clockSettings = new TextSettings();
  clockSettings->setTextDatum(TR_DATUM);
  clockSettings->setTextSize(2);
  clockSettings->setBgColor(TFTSCREEN_DEFAULT_BG_COLOR);
  
  TextSettings* dateSettings = new TextSettings();
  dateSettings->setTextDatum(TR_DATUM);
  dateSettings->setBgColor(TFTSCREEN_DEFAULT_BG_COLOR);
  dateSettings->setTextPadding(150);

  TextSettings* dhtSettings = new TextSettings();
  dhtSettings->setTextDatum(BL_DATUM);  // Let's put iiiiiiit on the left
  dhtSettings->setBgColor(TFTSCREEN_DEFAULT_BG_COLOR);
  dhtSettings->setTextSize(1);

  // This doesn't exactly make things simpler.
  // Clock position
  int sidePadding = 6;
  int topPadding = 10;
  int clockXPos = TFTSCREEN_MAX_X - sidePadding;
  int clockYPos = TFTSCREEN_STATUSBAR_THICKNESS + topPadding;
  _clockElement = new ScreenElement(
    new Point(clockXPos, clockYPos),
    clockSettings
  );

  // Date position
  const uint16_t dateXPos = clockXPos;
  const uint16_t dateYPos = clockYPos + 48;
  _dateElement = new ScreenElement(
    new Point(dateXPos, dateYPos),
    dateSettings
  );

  // Weekday position
  const uint16_t weekdayXPos = clockXPos;
  const uint16_t weekdayYPos = dateYPos + 20;
  _weekdayElement = new ScreenElement(
    new Point(weekdayXPos, weekdayYPos),
    dateSettings
  );
  
  // Humidity position
  const uint16_t humidityXPos = 3;
  const uint16_t humidityYPos = TFTSCREEN_MAX_Y - 10;
  _humidityElement= new ScreenElement(
    new Point(humidityXPos, humidityYPos),
    dhtSettings
  );

  // Temperature position
  const uint16_t tempXPos = 3;
  const uint16_t tempYPos = humidityYPos - 30;
  _temperatureElement = new ScreenElement(
    new Point(tempXPos, tempYPos),
    dhtSettings
  );
  

  updateClockDisplay();
  updateDateDisplay();
  updateDHTDisplay();
}

HomeScreen::~HomeScreen() {
  Logging::writeln("HomeScreen deleted!");
}

void HomeScreen::drawScreen() {
  // Format time
  char clockStr[9];
  sprintf(clockStr, "%.2d:%.2d:%.2d", _hour, _minute, _second);

  // Format date
  char dateStr[11];
  sprintf(dateStr, "%.2d/%.2d/%.4d", _day, _month, _year);

  char temperatureStr[7];
  sprintf(temperatureStr, "%.1f C", _temperature);

  char humidityStr[7];
  sprintf(humidityStr, "%.1f%%", _humidity);

  // Only clock is being drawn...
  if(_clockElement->isRedrawQueued()) {
    _clockElement->drawElement(clockStr);
  }
  if(_dateElement->isRedrawQueued()) {
    _dateElement->drawElement(dateStr);
  }
  if(_weekdayElement->isRedrawQueued()) {
    _weekdayElement->drawElement(_weekday);
  }
  if(_temperatureElement->isRedrawQueued()) {
    _temperatureElement->drawElement(temperatureStr);
  }
  if(_humidityElement->isRedrawQueued()) {
    _humidityElement->drawElement(humidityStr);
  }
}

void HomeScreen::drawScreenForced() {
  _clockElement->queueForRedraw();
  _dateElement->queueForRedraw();
  _weekdayElement->queueForRedraw();
  _temperatureElement->queueForRedraw();
  _humidityElement->queueForRedraw();
  drawScreen();
}

// Here we set the queueForRedraw variables
void HomeScreen::updateContent() {
  _timeRTC->synchronize();

  // Queue redraws for time related stuff
  if(_timeRTC->getSeconds() != _second) {
    updateClockDisplay();
    _clockElement->queueForRedraw();
    if(_timeRTC->getDay() != _day) {
      updateDateDisplay();
      _dateElement->queueForRedraw();
      _weekdayElement->queueForRedraw();
    }
    _isRedrawQueued = true;
  }

  // Queue redraws for DHT
  unsigned long currentMillis = millis();
  if(currentMillis >= _dhtMillisTimestamp + _dhtReadingDelay) {
    updateDHTDisplay();

    _dhtMillisTimestamp = millis();
  }
}

void HomeScreen::updateClockDisplay() {
  _second = _timeRTC->getSeconds();
  _minute = _timeRTC->getMinutes();
  _hour = _timeRTC->getHours();
}

void HomeScreen::updateDateDisplay() {
  _day = _timeRTC->getDay();
  _month = _timeRTC->getMonth();
  _year = _timeRTC->getYear();
  _weekday = _timeRTC->getWeekday();
}

void HomeScreen::updateDHTDisplay() {
  float readings[2] = {0};
  bool readingSuccess = _dht->readTempAndHumidity(readings) == 0;
  
  if(readingSuccess) {
    Logging::writeln("DHT reading success");
    float temperature = readings[1];
    float humidity = readings[0];
    Logging::writelnf("Temp: %.1f\nHumidity: %.1f", LoggingLevel::Normal, temperature, humidity);

    // Update only if changed (because we can)
    if(_temperature != temperature) {
      _temperatureElement->queueForRedraw();
      _temperature = temperature;
    }
    if(_humidity != humidity) {
      _humidityElement->queueForRedraw();
      _humidity = humidity;
    }
  }
  else {
    Logging::writeln("DHT sensor readings failed", LoggingLevel::Warning);
  }
}
