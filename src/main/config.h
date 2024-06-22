#ifndef config_h
#define config_h

#include <Arduino.h>
#include <Timezone.h>
#include <stdint.h>

class config {
  public:
    // wifiCredentials index correspons to one WiFi network.
    // numberOfNetworks should be manually changed, depending on how many networks are used.
    static constexpr uint8_t numberOfNetworks = 2;
    static constexpr const char* wifiCredentials[numberOfNetworks][2] = {
      {"SSID1", "PASS1"},
      {"SSID2", "PASS2"}
    };

    // For default time, it works during summer. For winter, I'm not so sure...
    static constexpr TimeChangeRule standardTime = {"CET", Last, Sun, Oct, 3, 60};   // Standard Time (Default: Sweden)
    static constexpr TimeChangeRule summerTime = {"CEST", Last, Sun, Mar, 3, 120};   // Summer Time (Default: Sweden)
};

#endif
