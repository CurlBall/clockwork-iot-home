#include "TimeRTC.h"
#include "Logging.h"
#include "config.h"
#include <stdint.h>
#include <RTC_SAMD51.h>
#include <DateTime.h>
#include <rpcWiFi.h>
#include <NTPClient.h>
#include <WiFiUdp.h>
#include <Timezone.h>

constexpr const char TimeRTC::_weekDays[7][10];   // I don't understand C++

TimeRTC::TimeRTC() {
  _rtc = new RTC_SAMD51();
  _rtc->begin();

  _summerTime = new TimeChangeRule(config::summerTime);
  _standardTime = new TimeChangeRule(config::standardTime);
  _timezone = new Timezone(*_summerTime, *_standardTime);

  _ntpClient = new NTPClient(_ntpUDP, "pool.ntp.org");
  _ntpClient->begin();

  // Paranoia
  delay(1000);

  // Set initial time. Will go badly if there's no connection with the internet.
  bool synchronizationSuccess = synchronize();
  if(!synchronizationSuccess) {
    // Log sync failure and do nothing to remedy it
    Logging::writeln("TimeRTC constructor couldn't use NTP", LoggingLevel::Error);
  }
  else {
    Logging::writeln("TimeRTC successfully synchronized");
  }
  
}

TimeRTC* TimeRTC::getInstance() {
  static TimeRTC* rtcInstance = new TimeRTC();
  return rtcInstance;
}

bool TimeRTC::synchronize() {
  if(WiFi.status() != WL_CONNECTED) {
    Logging::writeln("TimeRTC couldn't synchronize. Bad connection.", LoggingLevel::Warning);
    return false;
  }
  else if(_ntpClient->update()) {
    // Get unix timestamp and convert to local time
    unsigned long epochTime = _ntpClient->getEpochTime();
    epochTime = _timezone->toLocal(epochTime);

    // Set RTC
    DateTime now(epochTime);
    _rtc->adjust(now);

    Logging::writeln("RTC adjusted.");
    Logging::write("New _ntpClient epoch time: ");
    Logging::writeln(_ntpClient->getEpochTime());
    Logging::write("New RTC epoch time: ");
    Logging::writeln(now.unixtime());
    return true;
  }
  else {
    return false;
  }
}

uint8_t TimeRTC::getSeconds() {
  // Do I give a shit about seconds?
  return _rtc->now().second();
}

uint8_t TimeRTC::getMinutes() {
  return _rtc->now().minute();
}

uint8_t TimeRTC::getHours() {
  return _rtc->now().hour();
}

uint8_t TimeRTC::getDay() {
  return _rtc->now().day();
}

uint8_t TimeRTC::getMonth() {
  return _rtc->now().month();
}

uint16_t TimeRTC::getYear() {
  // Lesson learned: Always double check the return value type.
  return _rtc->now().year();
}

const char* TimeRTC::getWeekday() {
  return _weekDays[_rtc->now().dayOfTheWeek()];
}