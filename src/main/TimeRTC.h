#ifndef TimeRTC_h
#define TimeRTC_h

#include <Arduino.h>
#include <RTC_SAMD51.h>
#include <DateTime.h>
#include <WiFiUdp.h>
#include <NTPClient.h>
#include <Timezone.h>

// Why not use the TimeZone library? https://forum.arduino.cc/t/adding-code-for-daylight-savings-time/1017146/8

class TimeRTC {
  private:
    RTC_SAMD51* _rtc;
    WiFiUDP _ntpUDP;
    NTPClient* _ntpClient;
    TimeChangeRule* _summerTime;
    TimeChangeRule* _standardTime;
    Timezone* _timezone;
    TimeRTC();
  public:
    static TimeRTC* getInstance();
    bool synchronize();
    uint8_t getSeconds();
    uint8_t getMinutes();
    uint8_t getHours();
    uint8_t getDay();
    uint8_t getMonth();
    uint16_t getYear();
};

#endif