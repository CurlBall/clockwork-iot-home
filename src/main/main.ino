#include <Arduino.h>
#include <TFT_eSPI.h>
#include <rpcWiFi.h>

#include "config.h"
#include "rootCertificates.h"
#include "Logging.h"
#include "HTTPSRequestHandler.h"

//#define DEBUG_ON 1; // Will uncomment when I figure out a good way for this to be referenced

TFT_eSPI tft;

void setup() {
  Logging::writeln("Running setup... ");

  // WiFi setup
  if(setupWifi()) {
    Logging::write("WiFi setup success on network: ");
    Logging::writeln(WiFi.SSID().c_str());
  }
  else {
    Logging::writeln("WiFi setup failure", LoggingLevel::Warning);
  }

  // Breathing space in case crashes forces one to reset hardware
  Logging::writeln("Starting");
  for(int i = 0; i < 5; i++) {
    Logging::write(".");
    delay(1000);
  }
  Logging::writeln("");
  
  Logging::writeln("Setup complete. Entering loop.");
}


void loop() {

}

bool setupWifi() {
  WiFi.mode(WIFI_STA);
  WiFi.begin(config::ssid, config::wifiPassword);

  uint8_t timeOutSec = 15;
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