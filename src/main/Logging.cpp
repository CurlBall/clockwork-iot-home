#include <Arduino.h>
#include "Logging.h"

#define DEFAULT_BAUD_RATE 19200

bool Logging::canWrite() {
  // Don't write if not in debug
  if(!DEBUG_ON) {
    return false;
  }

  // Init Serial if not already initialized
  if(!Serial) {
    Serial.begin(DEFAULT_BAUD_RATE);
    while(!Serial);
  }

  return true;
}

void Logging::write(const char* message, LoggingLevel logLevel) { 
  if(!Logging::canWrite()) {
    return;
  }

  if(logLevel == LoggingLevel::Warning) {
    Serial.write("[WARNING] : ");
  }
  else if(logLevel == LoggingLevel::Error) {
    Serial.write("[ERROR] : ");
  }
  Serial.write(message);
}

void Logging::writeln(const char* message, LoggingLevel logLevel) {
  if(!Logging::canWrite()) {
    return;
  }

  Logging::write(message, logLevel);
  Serial.write('\n');
}

void Logging::write(int number) {
  if(!Logging::canWrite()) {
    return;
  }
  
  // I hate this.
  byte bufferSize = 14;
  char buffer[bufferSize];
  snprintf(buffer, bufferSize, "%d", number);
  Logging::write(buffer);
}

void Logging::writeln(int number) {
  if(!Logging::canWrite()) {
    return;
  }
  
  Logging::write(number);
  Serial.write('\n');
}