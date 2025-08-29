#include <stdint.h>
#include <Arduino.h>
#include "Logging.h"

bool Logging::canWrite() {
  static bool serialInitialized = false;

  // Init Serial if not already initialized
  if(!Serial && !serialInitialized) {
    Serial.begin(DEFAULT_BAUD_RATE);
    serialInitialized = true;
    delay(500);
  }

  // Don't write if not in debug
  return DEBUG_ON && Serial;
}

void Logging::writeLogLevel(LoggingLevel logLevel) {
  if(logLevel == LoggingLevel::Normal) {
    return;
  }
  if(logLevel == LoggingLevel::Warning) {
    Serial.write("[WARNING] : ");
  }
  else if(logLevel == LoggingLevel::Error) {
    Serial.write("[ERROR] : ");
  }
  else if(logLevel == LoggingLevel::Cataclysmic) {
    Serial.write("!!! [YOU FUCKING DUMBASS] !!! : ");
  }
}

void Logging::write(const char* message, LoggingLevel logLevel) { 
  if(!Logging::canWrite()) {
    return;
  }

  writeLogLevel(logLevel);
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

void Logging::writelnf(const char* format, LoggingLevel logLevel, ...) {
  static const uint8_t bufferSize = 255;
  static char buffer[bufferSize];

  if(!Logging::canWrite()) {
    return;
  }

  va_list args;
  va_start(args, format);
  va_end(args);

  int length = vsnprintf(buffer, bufferSize, format, args);
  Logging::writeln(buffer, logLevel);
}