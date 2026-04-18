#include "altenter/console_logger.h"

using namespace altenter;

ConsoleLogger::ConsoleLogger() {
    this->thrd = std::thread(&ConsoleLogger::process, this);
}

ConsoleLogger::~ConsoleLogger() {
    this->run = false;
    this->cv.notify_all();
    if (this->thrd.joinable()) {
        this->thrd.join();
    }
}

void ConsoleLogger::shutdown() {
    this->run = false;
    this->cv.notify_all();
    if (this->thrd.joinable()) {
        this->thrd.join();
    }
}

void ConsoleLogger::log(std::string&& msg, LogType type) {
    {
        std::lock_guard<std::mutex> lock(this->mtx);
        this->logMessages.emplace(std::move(msg), type);
    }
    this->cv.notify_one();
}

void ConsoleLogger::process() {
    while (run || !logMessages.empty()) {
        std::unique_lock<std::mutex> lock(mtx);

        cv.wait(lock, [this] {
            return !logMessages.empty() || !run;
        });

        while (!logMessages.empty()) {
            auto msg = std::move(logMessages.front());
            logMessages.pop();

            lock.unlock(); 

            std::string prefix = getPrefix(msg.type);
            std::string time_str = getTimeInfo();

            std::cout << prefix << RESET << TIME_COLOR << ' ' << time_str << ' '
                      << RESET << getColorBg(msg.type) << ' ' << RESET
                      << ' ' << getColorText(msg.type) << msg.msg << RESET << std::endl;

            lock.lock();
        }
    }
}

std::string ConsoleLogger::getPrefix(LogType type) {
    std::string combined;
    switch(type) {
        case LogType::WARGNING: {
            combined = WARNING_COLOR;
            combined = combined + " | WARNING  ";

            break;
        }
        case LogType::DEBUG: {
            combined = DEBUG_COLOR;
            combined = combined + " | DEBUG    ";

            break;
        }
        case LogType::INFO: {
            combined = INFO_COLOR;
            combined = combined + " | INFO     ";

            break;
        }
        case LogType::ERROR: {
            combined = ERROR_COLOR;
            combined = combined + " | ERROR    ";

            break;
        }
        case LogType::CRITICAL: {
            combined = CRITICAL_COLOR;
            combined = combined + " | CRITICAL ";

            break;
        }
        default: { return ""; }
    }

    return combined;
}

std::string ConsoleLogger::getTimeInfo() {
    std::time_t t = time(nullptr);
    std::tm* loctime = localtime(&t);

    std::stringstream ss;
    ss << loctime->tm_year + 1900 << '.'
        << std::setw(2) << std::setfill('0') << loctime->tm_mday << '.'
        << std::setw(2) << std::setfill('0') << loctime->tm_mon + 1 << ' '
        << std::setw(2) << std::setfill('0') << loctime->tm_hour << ':'
        << std::setw(2) << std::setfill('0') << loctime->tm_min << ':'
        << std::setw(2) << std::setfill('0') << loctime->tm_sec;

    std::string time_str = ss.str();
    return time_str;
}

char* ConsoleLogger::getColorText(LogType type) {
    switch(type) {
        case LogType::WARGNING: {
            return WARNING_COLOR_TEXT;
        }
        case LogType::DEBUG: {
            return DEBUG_COLOR_TEXT;
        }
        case LogType::INFO: {
            return INFO_COLOR_TEXT;
        }
        case LogType::ERROR: {
            return ERROR_COLOR_TEXT;
        }
        case LogType::CRITICAL: {
            return CRITICAL_COLOR_TEXT;
        }
        default: { return ""; }
    }
}

char* ConsoleLogger::getColorBg(LogType type) {
    switch(type) {
        case LogType::WARGNING: {
            return WARNING_COLOR;
        }
        case LogType::DEBUG: {
            return DEBUG_COLOR;
        }
        case LogType::INFO: {
            return INFO_COLOR;
        }
        case LogType::ERROR: {
            return ERROR_COLOR;
        }
        case LogType::CRITICAL: {
            return CRITICAL_COLOR;
        }
        default: { return ""; }
    }
}
