#include <Arduino.h>
#include <rpcWiFi.h>
#include <WiFiMulti.h>

#include "config.h"
#include "rootCertificates.h"
#include "Logging.h"
#include "HTTPSRequestHandler.h"
#include "TFTScreen.h"
#include "HomeScreen.h"

//#define DEBUG_ON 1; // Will uncomment when I figure out a good way for this to be referenced

// Very, very, VERY interesting stuff:
// https://arduino.github.io/arduino-cli/0.21/sketch-specification/
// Example for helping users download dependencies: http://librarymanager#rpcwifi

TFTScreen* tftScreen;
WiFiMulti wifiMulti;

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
  for(int i = 0; i < config::numberOfNetworks; i++) {
    Logging::writeln(i + 1);
    Logging::writeln(config::wifiCredentials[i][0]);
    Logging::writeln(config::wifiCredentials[i][1]);
    wifiMulti.addAP(
      config::wifiCredentials[i][0], 
      config::wifiCredentials[i][1]
    );
  }

  Logging::writeln("Connecting to WiFi");
  bool wifiSuccess = wifiMulti.run() == WL_CONNECTED;
  if(wifiSuccess) {
    Logging::write("WiFi connection success. Network: ");
    Logging::writeln(WiFi.localIP());
  }
  else {
    Logging::writeln("WiFi connection failure", LoggingLevel::Warning);
  }

  return wifiSuccess;
}