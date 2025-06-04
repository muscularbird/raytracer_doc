#include "../../include/logger/Logger.hpp"


Logger::Logger()
{
    _logFile.open("./log_file/zappy_gui.log", std::ios::app);
    if (!_logFile.is_open()) {
        throw std::runtime_error("failed to open log file");
    }
}

Logger::~Logger()
{
    if (_logFile.is_open())
        _logFile.close();
}

Logger& Logger::getInstance()
{
    static Logger instance;
    return instance;
}

void Logger::log(const std::string& message, LogLevel level) {
    std::lock_guard<std::mutex> lock(_mutex);

    auto now = std::chrono::system_clock::now();
    auto now_c = std::chrono::system_clock::to_time_t(now);
    std::tm tm_time{};
#if defined(_WIN32)
    localtime_s(&tm_time, &now_c);
#else
    localtime_r(&now_c, &tm_time);
#endif

    if (_logFile.is_open()) {
        _logFile << "[" << std::put_time(&tm_time, "%Y-%m-%d %H:%M:%S") << "] "
                    << "[" << levelToString(level) << "] "
                    << message << std::endl;
    }
}

std::string Logger::levelToString(LogLevel level) {
    switch (level) {
        case LogLevel::INFO:    return "INFO";
        case LogLevel::ERROR:   return "ERROR";
        default:                return "UNKNOWN";
    }
}
