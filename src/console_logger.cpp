#include "console_logger/console_logger.h"

altenter::ConsoleLogger::ConsoleLogger() {}
altenter::ConsoleLogger::~ConsoleLogger() {}


void altenter::ConsoleLogger::log(const std::string&& msg, altenter::LogType type) {
    std::string prefix = this->getPrefix(type);
    std::string time_str = this->getTimeInfo();
    std::cout << prefix << RESET << ' ' << TIME_COLOR << ' ' << time_str << ' ' 
        << RESET << ' ' << this->getColorBg(type) << ' ' << RESET
        << ' ' << this->getColorText(type) << msg << RESET << std::endl;
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
        << std::setw(2) << std::setfill('0') << loctime->tm_mon + 1 << '.' << ' '
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