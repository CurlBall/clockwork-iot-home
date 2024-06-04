#ifndef HTTPSRequestHandler_h
#define HTTPSRequestHandler_h

#include <WiFiClientSecure.h>
#include <WiFiClient.h>
#include <HTTPClient.h>

// This object could actually be saved and reused.
class HTTPSRequestHandler {
  private:
    static constexpr byte MAX_URL_SIZE = 182; // Somewhat arbitrary number. 
    char _url[MAX_URL_SIZE];   // Holy shit, this works?
    WiFiClient _wifiClient;
    HTTPClient _httpClient;
    bool isValidUrl(const char* url);
    bool setUrl(const char* newUrl);
  public:
    HTTPSRequestHandler(const char* url); // Remember to strcpy probably.
    ~HTTPSRequestHandler();
    bool GET();
    String getString();
    WiFiClient* getStream();  // Ampersand or asterisk? I keep forgetting.
    HTTPClient* getHttpClient();

};

#endif