#ifndef config_h
#define config_h

#include <Timezone.h>

class config {
   public:
    static constexpr const char* ssid = "SSID";
    static constexpr const char* wifiPassword = "WiFiPassword";

    // For default time, it works during summer. For winter, I'm not so sure...
    static constexpr TimeChangeRule standardTime = {"CET", Last, Sun, Oct, 3, 60};   // Standard Time (Default: Sweden)
    static constexpr TimeChangeRule summerTime = {"CEST", Last, Sun, Mar, 3, 120};   // Summer Time (Default: Sweden)
};

#endif
