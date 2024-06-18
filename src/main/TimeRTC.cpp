#include <stdint.h>
#include "TimeRTC.h"
#include <RTC_SAMD51.h>
#include <DateTime.h>
#include <rpcWiFi.h>
#include <NTPClient.h>
#include <WiFiUdp.h>

#include "Logging.h"

TimeRTC::TimeRTC() {
  _rtc = new RTC_SAMD51();
  _rtc->begin();

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
    // NTP stuff
    // Not sure these 3 loc will work.
    unsigned long epochTime = _ntpClient->getEpochTime();
    DateTime now(epochTime);
    Logging::write("DateTime year: ");
    Logging::writeln(now.year());
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

