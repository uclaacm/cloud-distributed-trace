#include <iostream>
#include <fstream>
#include <mutex>
#include <string>
#include <stdexcept>
#include <algorithm>

class LamportClock {
private:
    unsigned long timestamp;
    std::mutex mtx;

public:
    LamportClock() : timestamp(0) {}

    unsigned long tick() {
        std::lock_guard<std::mutex> lock(mtx);
        timestamp++;
        return timestamp;
    }

    unsigned long update(unsigned long received) {
        std::lock_guard<std::mutex> lock(mtx);
        timestamp = std::max(timestamp, received) + 1;
        return timestamp;
    }


    unsigned long get_time() {
        std::lock_guard<std::mutex> lock(mtx);
        return timestamp;
    }
};

// Logger: Logs messages with Lamport Logical Clock timestamps
class Logger {
private:
    std::ofstream log_file;
    LamportClock clock;
    std::mutex log_mtx;

public:
    Logger(const std::string &filename) {
        log_file.open(filename, std::ios::out | std::ios::app);
        if (!log_file.is_open()) {
            throw std::runtime_error("Cannot open log file: " + filename);
        }
    }

    ~Logger() {
        if (log_file.is_open()) {
            log_file.close();
        }
    }

    // Logs an internal event. The logical clock is incremented.
    void log(const std::string &node_id, const std::string &source_filename, int line_number, const std::string &message) {
        unsigned long ts = clock.tick();
        std::lock_guard<std::mutex> lock(log_mtx);
        log_file << ts << " " << node_id << " " << source_filename << " " << line_number << " " << message << std::endl;
    }

    // Logs an external event that carries a Lamport timestamp.
    void log_received(const std::string &node_id, const std::string &source_filename, int line_number, const std::string &message, unsigned long received_timestamp) {
        unsigned long ts = clock.update(received_timestamp);
        std::lock_guard<std::mutex> lock(log_mtx);
        log_file << ts << " " << node_id << " " << source_filename << " " << line_number << " " << message << std::endl;
    }
};