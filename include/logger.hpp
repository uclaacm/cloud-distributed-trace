#ifndef LAMPORT_LOGGER_HPP
#define LAMPORT_LOGGER_HPP

#include <string>
#include <atomic>
#include <fstream>

enum class LogLevel {
    DEBUG,
    INFO,
    WARNING,
    ERROR,
    CRITICAL
};

class LamportLogger {
protected:
    std::atomic<uint64_t> lamportClock{0};
    std::ofstream logFile;

public:
    LamportLogger(const std::string& filename) : logFile(filename, std::ios::app) {
        if (!logFile.is_open()) {
            throw std::runtime_error("Unable to open log file: " + filename);
        }
    }

    virtual ~LamportLogger() {
        if (logFile.is_open()) {
            logFile.close();
        }
    }

    virtual void log(LogLevel level, const std::string& message, const char* file, int line) {
        uint64_t timestamp = lamportClock.fetch_add(1, std::memory_order_relaxed);
        
        std::string levelStr;
        switch (level) {
            case LogLevel::DEBUG:    levelStr = "DEBUG";    break;
            case LogLevel::INFO:     levelStr = "INFO";     break;
            case LogLevel::WARNING:  levelStr = "WARNING";  break;
            case LogLevel::ERROR:    levelStr = "ERROR";    break;
            case LogLevel::CRITICAL: levelStr = "CRITICAL"; break;
        }

        logFile << timestamp << " [" << levelStr << "] " << file << ":" << line << " - " << message << std::endl;
        logFile.flush();
    }

    void updateLamportClock(uint64_t receivedTime) {
        uint64_t currentTime = lamportClock.load(std::memory_order_relaxed);
        while (currentTime <= receivedTime &&
               !lamportClock.compare_exchange_weak(currentTime, receivedTime + 1,
                                                   std::memory_order_relaxed,
                                                   std::memory_order_relaxed)) {
            // Keep trying until we successfully update the clock
        }
    }

    uint64_t getLamportTime() {
        return lamportClock.load(std::memory_order_relaxed);
    }
};

#define LOG(logger, level, message) \
    logger.log(level, message, __FILE__, __LINE__)

#endif // LAMPORT_LOGGER_HPP
