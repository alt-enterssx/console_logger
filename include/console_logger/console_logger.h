#pragma once

#include <string>

namespace altenter {

    enum LogType {
        WARGNING,
        DEBUG,
        INFO,
        ERROR,
        CRITICAL
    };

    class ConsoleLogger {
        public:
            ConsoleLogger();
            ~ConsoleLogger();

            void log(const char* msg, altenter::LogType type = altenter::LogType::DEBUG);
            void log(const std::string& msg, altenter::LogType type = altenter::LogType::DEBUG);

        private:
    };
}