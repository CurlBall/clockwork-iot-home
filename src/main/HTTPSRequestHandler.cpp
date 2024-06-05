#include <string.h>
#include "HTTPSRequestHandler.h"
#include "Logging.h"
#include <WiFiClientSecure.h>
#include <HTTPClient.h>

/*
However the GET result should be handled, could possibly be done with strategy pattern?
Or, assuming most if not all requests will include stuff in .json format, an overloaded
method could take a JsonDocument (filter) as an argument, and only necessary data would be retrieved.
If content size is too large, reading one jsonObject at a time could become simplified and reusable.
Might still be a good idea to have that be modular though?
*/

HTTPSRequestHandler::HTTPSRequestHandler(const char* url, const char* rootCA) {
  // c-strings are the bane of my existence. This inspires:
  // https://forum.arduino.cc/t/more-with-char-arrays-and-class-functions/674431/7
  if(!setUrl(url)) {
    _url[0] = '\0';
  }

  _wifiClient.setCACert(rootCA);  // Assuming I don't have to save it.

  Logging::writeln("Constructor finished.");
}

HTTPSRequestHandler::~HTTPSRequestHandler() {
  // I'll figure something out
}

bool HTTPSRequestHandler::isValidUrl(const char* url) {
  bool isValid = true;

  size_t length = strlen(url);
  if(url[0] == '\0') {
    Logging::writeln("URL appears to be empty", LoggingLevel::Warning);
    isValid = false;
  }
  else if(length >= MAX_URL_SIZE) {
    Logging::write("New URL too big! Size = ", LoggingLevel::Warning);
    Logging::writeln(length);
    isValid = false;
  }
  else if(strncmp("https", url, 5) != 0) { 
    Logging::write("Following URL doesn't use https: ", LoggingLevel::Warning);
    Logging::writeln(url);
    isValid = false;
  }

  return isValid;
}

bool HTTPSRequestHandler::setUrl(const char* newUrl) {
  bool setUrlSuccess;
  if(isValidUrl(newUrl)) {
    strncpy(_url, newUrl, sizeof(_url));
    Logging::write("New URL set: ");
    Logging::writeln(_url);
    setUrlSuccess = true;
  }
  else {
    setUrlSuccess = false;
  }

  return setUrlSuccess;
}

bool HTTPSRequestHandler::GET() {
  Logging::write("Begin: ");
  Logging::writeln(_url);
  bool beginSuccess = _httpClient.begin(_wifiClient, _url);
  if(!beginSuccess) {
    Logging::writeln("HTTPClient begin() failed!", LoggingLevel::Error);
    return false;
  }

  Logging::writeln("Get...");
  int httpCode = _httpClient.GET();
  if(httpCode < 0) {
    Logging::write("HTTPClient failure! GET HTTP code: ", LoggingLevel::Error);
    Logging::writeln(httpCode);
    return false;
  }

  return httpCode == HTTP_CODE_OK;
}

String HTTPSRequestHandler::getString() {
  return _httpClient.getString();
}

HTTPClient* HTTPSRequestHandler::getHttpClient() {
  return &_httpClient;
}

WiFiClient* HTTPSRequestHandler::getStream() {
  return &_wifiClient;
}