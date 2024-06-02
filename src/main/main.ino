#include <Arduino.h>
#include <TFT_eSPI.h>
#include <rpcWiFi.h>

#include "Config.h"
#include "Logging.h"

//#define DEBUG_ON 1; // Will uncomment when I figure out a good way for this to be referenced

TFT_eSPI tft;

void setup() {
  Logging::writeln("Running setup... ");
  if(setupWifi()) {
    Logging::write("WiFi setup success on network: ");
    Logging::writeln(WiFi.SSID().c_str());
  }
  else {
    Logging::writeln("WiFi setup failure", LoggingLevel::Warning);
  }

  Logging::writeln("Setup complete. Entering loop.");
}


void loop() {
}

bool setupWifi() {
  WiFi.mode(WIFI_STA);
  WiFi.begin(Config::ssid, Config::wifiPassword);

  uint8_t timeOutSec = 10;
  for(uint8_t i = 0; i < timeOutSec; i++) {
    Logging::writeln("Connecting...");
    if(WiFi.status() == WL_CONNECTED) {
      return true;
    }
    
    delay(1000);
  }

  // Couldn't connect
  return false;
}