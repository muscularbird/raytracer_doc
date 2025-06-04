#ifndef INCLUDED_LOGGER_HPP
    #define INCLUDED_LOGGER_HPP

#include <iostream>
#include <fstream>
#include <chrono>
#include <ctime>
#include <iomanip>
#include <mutex>
#include <string> 


enum class LogLevel {
    INFO,
    ERROR
};

class Logger {
    public:
        static Logger& getInstance();
    
        void log(const std::string& message, LogLevel level = LogLevel::INFO);
    
    private:
        Logger();
        ~Logger();
        Logger(const Logger&) = delete;
        Logger& operator=(const Logger&) = delete;
    
        std::string levelToString(LogLevel level);
    
        std::ofstream _logFile;
        std::mutex _mutex;
    };


#endif