#ifndef FILE_LOGGER_HPP
#define FILE_LOGGER_HPP

#include "logger.hpp"
#include <fstream>
#include <iomanip>
#include <chrono>
#include <sstream>
using namespace std;

class FileLogger : public Logger {
private:
    ofstream logFile;

    string getTimestamp() {
        auto now = chrono::system_clock::now();
        auto now_c = chrono::system_clock::to_time_t(now);
        stringstream ss;
        ss << put_time(localtime(&now_c), "%Y-%m-%d %H:%M:%S");
        return ss.str();
    }

public:
    FileLogger(const string& filename) : logFile(filename, ios::app) {
        if (!logFile.is_open()) {
            throw runtime_error("Unable to open log file: " + filename);
        }
    }

    ~FileLogger() {
        if (logFile.is_open()) {
            logFile.close();
        }
    }

    void log(LogLevel level, const string& message, const char* file, int line) override {
        if (!logFile.is_open()) return;

        string timestamp = getTimestamp();
        string levelStr;

        switch (level) {
            case LogLevel::DEBUG:    levelStr = "DEBUG";    break;
            case LogLevel::INFO:     levelStr = "INFO";     break;
            case LogLevel::WARNING:  levelStr = "WARNING";  break;
            case LogLevel::ERROR:    levelStr = "ERROR";    break;
            case LogLevel::CRITICAL: levelStr = "CRITICAL"; break;
        }

        logFile << timestamp << " [" << levelStr << "] " << file << ":" << line << " - " << message << endl;
        logFile.flush(); // Ensure the log is written immediately
    }
};

#endif // FILE_LOGGER_HPP
