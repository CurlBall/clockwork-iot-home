#ifndef Logging_h
#define Logging_h

#define DEBUG_ON 1 // Shouldn't be here, but... Well.
#define DEFAULT_BAUD_RATE 19200

enum class LoggingLevel : int {
  Normal = 0,
  Warning,
  Error,
  Cataclysmic
};

class Logging {
  private:
    Logging();
    static bool canWrite();
  public: 
    // I want me a 'writef' function...  
    static void write(const char* message, LoggingLevel logLevel = LoggingLevel::Normal);
    static void writeln(const char* message, LoggingLevel logLevel = LoggingLevel::Normal);
    static void write(int number);
    static void writeln(int number);
};

#endif