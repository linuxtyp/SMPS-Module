#ifndef DEBUG_H
#define DEBUG_H

#include <Arduino.h>
#include <FS.h>
#include <SPIFFS.h>

// Enum for different log levels
enum LogLevel {
    LOG_LEVEL_NONE,
    LOG_LEVEL_ERROR,
    LOG_LEVEL_WARN,
    LOG_LEVEL_INFO,
    LOG_LEVEL_DEBUG,
    LOG_LEVEL_VERBOSE
};

class Debug {
public:
    // Initialize the logger with a log level and serial baud rate
    static void begin(LogLevel level = LOG_LEVEL_INFO, long baudRate = 115200);

    // Log error messages
    static void error(const char* format, ...);

    // Log warning messages
    static void warn(const char* format, ...);

    // Log informational messages
    static void info(const char* format, ...);

    // Log debug messages
    static void debug(const char* format, ...);

    // Log verbose messages
    static void verbose(const char* format, ...);

    // Set the log level
    static void setLogLevel(LogLevel level);

    // Enable or disable filesystem logging
    static void enableFileLogging(bool enable);

    // Set the log file retention period (in milliseconds)
    static void setLogFileRetentionPeriod(unsigned long period);

private:
    static LogLevel currentLogLevel;
    static bool fileLoggingEnabled;
    static unsigned long logFileRetentionPeriod;
    static unsigned long lastLogFileTime;

    // Internal method to log messages based on the log level
    static void log(LogLevel level, const char* format, va_list args);

    // Internal method to log messages to the filesystem
    static void logToFile(const char* message);
};

#endif
