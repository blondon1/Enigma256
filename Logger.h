#ifndef LOGGER_H
#define LOGGER_H

#include <iostream>
#include <fstream>
#include <string>
#include <mutex>

enum class LogLevel {
    INFO,
    DEBUG,
    ERROR
};

class Logger {
public:
    Logger(LogLevel level = LogLevel::INFO, const std::string& filename = "encryption_log.txt");
    void log(LogLevel level, const std::string& message);
    void setLogLevel(LogLevel level);

private:
    LogLevel logLevel;
    std::ofstream logFile;
    std::mutex logMutex;

    std::string getLogLevelString(LogLevel level);
};

#endif // LOGGER_H
