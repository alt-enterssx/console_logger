#pragma once

#include <iostream>
#include <string>
#include <ctime>
#include <time.h>
#include <sstream>
#include <iomanip>
#include <queue>
#include <mutex>
#include <thread>
#include <atomic>
#include <condition_variable>

#define WARNING_COLOR "\033[1;30;43m"
#define DEBUG_COLOR "\033[1;30;105m"
#define INFO_COLOR "\033[1;30;102m"
#define ERROR_COLOR "\033[1;97;101m"
#define CRITICAL_COLOR "\033[1;97;41m"

#define WARNING_COLOR_TEXT "\033[0;33m"
#define DEBUG_COLOR_TEXT "\033[0;95m"
#define INFO_COLOR_TEXT "\033[0;92m"
#define ERROR_COLOR_TEXT "\033[0;91m"
#define CRITICAL_COLOR_TEXT "\033[0;31m"

#define TIME_COLOR "\033[1;97;40m"

#define RESET "\033[0m"

namespace altenter {

    enum LogType {
        WARGNING,
        DEBUG,
        INFO,
        ERROR,
        CRITICAL
    };

    struct LogMessage {
        std::string msg;
        LogType type;

        LogMessage(std::string&& msg, LogType type = LogType::INFO): msg(msg), type(type) {}
    };

    class ConsoleLogger {
        public:
            ConsoleLogger();
            ~ConsoleLogger();
            void shutdown();

            void log(std::string&& msg, LogType type = LogType::INFO);
            
            template<typename... Args>
            void logFormat(const std::string& msg, LogType type, Args&&... args) {
                std::vector<std::string> params = {
                    toString(std::forward<Args>(args))...
                };

                std::string result;
                result.reserve(msg.size() + 32);

                size_t argIndex = 0;

                for (size_t i = 0; i < msg.size(); ++i) {
                    if (msg[i] == '{' && i + 1 < msg.size() && msg[i + 1] == '}') {
                        if (argIndex < params.size()) {
                            result += params[argIndex++];
                        } else {
                            result += "{}";
                        }
                        ++i;
                    } else {
                        result += msg[i];
                    }
                }

                this->log(std::move(result), type);
            }

            private:
            std::queue<LogMessage> logMessages;
        
            std::mutex mtx;
            std::condition_variable cv;
            std::thread thrd;
            std::atomic<bool> run{true};

            void process();

            std::string getPrefix(LogType type);
            std::string getTimeInfo();
            char* getColorText(LogType type);
            char* getColorBg(LogType type);
    };
}