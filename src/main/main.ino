#include <Arduino.h>
#include <TFT_eSPI.h>

#include "Logging.h"

//#define DEBUG_ON 1; // Will uncomment when I figure out a good way for this to be referenced

TFT_eSPI tft;

void setup() {
  Logging::writeln("Am alive!");
  Logging::writeln("Am dying!", LoggingLevel::Warning);
  Logging::writeln("Am dead!", LoggingLevel::Error);

  for(int i = 0; i < 20; i++) {
    Logging::writeln(i + 1);
    delay(1000);
  }

}

void loop() {
  
}