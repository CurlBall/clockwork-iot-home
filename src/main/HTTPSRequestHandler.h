#ifndef HTTPSRequestHandler_h
#define HTTPSRequestHandler_h

#include <WiFiClientSecure.h>
#include <WiFiClient.h>
#include <HTTPClient.h>

// If concurrent connections doesn't work (https://github.com/Seeed-Studio/Seeed_Arduino_rpcWiFi/issues/16), consider singleton? Maybe?
// Getting root CA certificates is an inconsistent process. Fix on demand.
// Consider making a HTTPRequestHandler which handles regular http connections, like that of openweathermap.org.
// This object could actually be saved and reused.
class HTTPSRequestHandler {
  private:
    static constexpr byte MAX_URL_SIZE = 182; // Somewhat arbitrary number. 
    char _url[MAX_URL_SIZE];   // Holy shit, this works?
    WiFiClientSecure _wifiClient;
    HTTPClient _httpClient;
    bool isValidUrl(const char* url);
    bool setUrl(const char* newUrl);
  public:
    HTTPSRequestHandler(const char* url, const char* rootCA); // Remember to strcpy probably.
    ~HTTPSRequestHandler();
    bool GET();
    String getString();
    WiFiClient* getStream();  // Ampersand or asterisk? I keep forgetting.
    HTTPClient* getHttpClient();

};

#endif