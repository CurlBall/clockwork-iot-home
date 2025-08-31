#include <Arduino.h>
#include <rpcWiFi.h>
#include <WiFiMulti.h>

#include "config.h"
#include "rootCertificates.h"
#include "Logging.h"
#include "HTTPSRequestHandler.h"
#include "TFTScreen.h"
#include "HomeScreen.h"

// Very, very, VERY interesting stuff:
// https://arduino.github.io/arduino-cli/0.21/sketch-specification/

/**
    Board Dependencies:
- Seeed SAMD Boards: http://boardsmanager#seeed_samd_boards

    Library Manager Dependencies: 
- rpcWiFi: http://librarymanager#rpcWiFi (And it's dependencies)
- NTPClient (Fabrice Weinberg): http://librarymanager#NTPClient
- SAMD51 Real-Time Clock (Seeed Studio): http://librarymanager#Seeed_Arduino_RTC
- Time (Michael Margolis) (Maybe automatically downloads for Timezone lib?): http://librarymanager#Time
- Timezone (Jack Christensen): http://librarymanager#Timezone

    Download manually and Sketch > Include Library > Add .ZIP Library:
- TFT_eSPI for Wio (Idk why I didn't use the library manager): https://github.com/Seeed-Studio/Seeed_Arduino_LCD
*/

TFTScreen* tftScreen;
WiFiMulti wifiMulti;
unsigned long millisTimestamp = 0;
uint8_t loopDelay = 50;

void setup() {
  Logging::writeln("Running setup... ");
  Logging::writeln("Initializing TFTScreen");
  tftScreen = TFTScreen::getInstance();
  Wire.begin(); // Enables I2C, intended for DHT11.

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
  unsigned long currentMillis = millis();
  if(currentMillis >= millisTimestamp + loopDelay) {
    tftScreen->update();
    millisTimestamp = currentMillis;
  }

  // If .run() is slow, maybe run it every now and then, millis style
  if(wifiMulti.run() != WL_CONNECTED) {
    Logging::writeln("WL_CONNECTED = false", LoggingLevel::Warning);
  }
}

bool setupWifi() {
  for(int i = 0; i < config::numberOfNetworks; i++) {
    Logging::writeln(i + 1);
    Logging::writeln(config::wifiCredentials[i][0]);
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