#include <Arduino.h>
#include <rpcWiFi.h>

#include "config.h"
#include "rootCertificates.h"
#include "Logging.h"
#include "HTTPSRequestHandler.h"
#include "TFTScreen.h"
#include "HomeScreen.h"

//#define DEBUG_ON 1; // Will uncomment when I figure out a good way for this to be referenced

TFTScreen* tftScreen;

void setup() {
  //Logging::writeln("Waiting 5 seconds...");
  //delay(5000);
  Logging::writeln("Running setup... ");

  Logging::writeln("Initializing TFTScreen");
  tftScreen = TFTScreen::getInstance();


  // WiFi setup
  if(setupWifi()) {
    Logging::write("WiFi setup success on network: ");
    Logging::writeln(WiFi.SSID().c_str());
  }
  else {
    Logging::writeln("WiFi setup failure", LoggingLevel::Warning);
  }

  // Add screens
  tftScreen->addScreen(new HomeScreen());
  
  Logging::writeln("Setup complete. Entering loop.");
}


void loop() {
  tftScreen->update();
  delay(40);
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