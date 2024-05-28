#include "debug.h"

// Initialize static member variables
LogLevel Debug::currentLogLevel = LOG_LEVEL_INFO;
//bool Debug::fileLoggingEnabled = false;
//nsigned long Debug::logFileRetentionPeriod = 0;
//unsigned long Debug::lastLogFileTime = 0;

void Debug::begin(LogLevel level, long baudRate) {
    currentLogLevel = level;
    Serial.begin(baudRate);
    while (!Serial) {
        // Wait for the serial port to connect
    }
    // Initialize SPIFFS
    //if (!SPIFFS.begin(true)) {
    //    Serial.println("An error has occurred while mounting SPIFFS");
    //}
}

void Debug::setLogLevel(LogLevel level) {
    currentLogLevel = level;
}

//void Debug::enableFileLogging(bool enable) {
//    fileLoggingEnabled = enable;
//}
//
//void Debug::setLogFileRetentionPeriod(unsigned long period) {
//    logFileRetentionPeriod = period;
//}

void Debug::log(LogLevel level, const char* format, va_list args) {
    if (level <= currentLogLevel) {
        char logBuffer[256];
        vsnprintf(logBuffer, sizeof(logBuffer), format, args);

        // Print log level prefix
        switch (level) {
            case LOG_LEVEL_ERROR:
                Serial.print("[ERROR] ");
                break;
            case LOG_LEVEL_WARN:
                Serial.print("[WARN] ");
                break;
            case LOG_LEVEL_INFO:
                Serial.print("[INFO] ");
                break;
            case LOG_LEVEL_DEBUG:
                Serial.print("[DEBUG] ");
                break;
            case LOG_LEVEL_VERBOSE:
                Serial.print("[VERBOSE] ");
                break;
            default:
                break;
        }

        // Print the log message to serial
        Serial.println(logBuffer);

        // Log to file if enabled
        //if (fileLoggingEnabled) {
        //    logToFile(logBuffer);
        //}
    }
}

/*void Debug::logToFile(const char* message) {
    // Append the log message to the file
    File logFile = SPIFFS.open("/log.txt", FILE_APPEND);
    if (!logFile) {
        Serial.println("Failed to open log file for writing");
        return;
    }
    logFile.println(message);
    logFile.close();

    // Check if we need to rotate the log file
    unsigned long currentTime = millis();
    if (logFileRetentionPeriod > 0 && (currentTime - lastLogFileTime) > logFileRetentionPeriod) {
        // Rename the log file with a timestamp
        String oldLogFileName = "/log_" + String(lastLogFileTime) + ".txt";
        SPIFFS.rename("/log.txt", oldLogFileName.c_str());
        lastLogFileTime = currentTime;
    }
}*/

void Debug::error(const char* format, ...) {
    va_list args;
    va_start(args, format);
    log(LOG_LEVEL_ERROR, format, args);
    va_end(args);
}

void Debug::warn(const char* format, ...) {
    va_list args;
    va_start(args, format);
    log(LOG_LEVEL_WARN, format, args);
    va_end(args);
}

void Debug::info(const char* format, ...) {
    va_list args;
    va_start(args, format);
    log(LOG_LEVEL_INFO, format, args);
    va_end(args);
}

void Debug::debug(const char* format, ...) {
    va_list args;
    va_start(args, format);
    log(LOG_LEVEL_DEBUG, format, args);
    va_end(args);
}

void Debug::verbose(const char* format, ...) {
    va_list args;
    va_start(args, format);
    log(LOG_LEVEL_VERBOSE, format, args);
    va_end(args);
}
