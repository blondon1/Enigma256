#include "Logger.h"

Logger::Logger(LogLevel level, const std::string& filename) : logLevel(level), logFile(filename, std::ios::app) {}

void Logger::log(LogLevel level, const std::string& message) {
    std::lock_guard<std::mutex> guard(logMutex);
    if (level >= logLevel) {
        std::string logMessage = "[" + getLogLevelString(level) + "] " + message;
        std::cout << logMessage << std::endl;
        logFile << logMessage << std::endl;
    }
}

void Logger::setLogLevel(LogLevel level) {
    logLevel = level;
}

std::string Logger::getLogLevelString(LogLevel level) {
    switch (level) {
        case LogLevel::INFO: return "INFO";
        case LogLevel::DEBUG: return "DEBUG";
        case LogLevel::ERROR: return "ERROR";
        default: return "UNKNOWN";
    }
}
