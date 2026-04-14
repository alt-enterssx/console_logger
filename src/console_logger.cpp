#include "console_logger/console_logger.h"

altenter::ConsoleLogger::ConsoleLogger() {
    this->thrd = std::thread(&ConsoleLogger::process, this);
}

altenter::ConsoleLogger::~ConsoleLogger() {
    this->run = false;
    this->cv.notify_all();
    if (this->thrd.joinable()) {
        this->thrd.join();
    }
}

void altenter::ConsoleLogger::log(std::string&& msg, LogType type) {
    {
        std::lock_guard<std::mutex> lock(this->mtx);
        this->logMessages.emplace(std::move(msg), type);
    }
    this->cv.notify_one();
}

void altenter::ConsoleLogger::process() {
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

std::string altenter::ConsoleLogger::getPrefix(altenter::LogType type) {
    std::string combined;
    switch(type) {
        case altenter::LogType::WARGNING: {
            combined = WARNING_COLOR;
            combined = combined + " | WARNING  ";

            break;
        }
        case altenter::LogType::DEBUG: {
            combined = DEBUG_COLOR;
            combined = combined + " | DEBUG    ";

            break;
        }
        case altenter::LogType::INFO: {
            combined = INFO_COLOR;
            combined = combined + " | INFO     ";

            break;
        }
        case altenter::LogType::ERROR: {
            combined = ERROR_COLOR;
            combined = combined + " | ERROR    ";

            break;
        }
        case altenter::LogType::CRITICAL: {
            combined = CRITICAL_COLOR;
            combined = combined + " | CRITICAL ";

            break;
        }
        default: { return ""; }
    }

    return combined;
}

std::string altenter::ConsoleLogger::getTimeInfo() {
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

char* altenter::ConsoleLogger::getColorText(altenter::LogType type) {
    switch(type) {
        case altenter::LogType::WARGNING: {
            return WARNING_COLOR_TEXT;
        }
        case altenter::LogType::DEBUG: {
            return DEBUG_COLOR_TEXT;
        }
        case altenter::LogType::INFO: {
            return INFO_COLOR_TEXT;
        }
        case altenter::LogType::ERROR: {
            return ERROR_COLOR_TEXT;
        }
        case altenter::LogType::CRITICAL: {
            return CRITICAL_COLOR_TEXT;
        }
        default: { return ""; }
    }
}

char* altenter::ConsoleLogger::getColorBg(altenter::LogType type) {
    switch(type) {
        case altenter::LogType::WARGNING: {
            return WARNING_COLOR;
        }
        case altenter::LogType::DEBUG: {
            return DEBUG_COLOR;
        }
        case altenter::LogType::INFO: {
            return INFO_COLOR;
        }
        case altenter::LogType::ERROR: {
            return ERROR_COLOR;
        }
        case altenter::LogType::CRITICAL: {
            return CRITICAL_COLOR;
        }
        default: { return ""; }
    }
}