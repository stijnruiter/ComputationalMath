#include "Logger.hpp"
#include <ctime>
#include <mutex>

void Engine::Logger::Log(LogLevel level, std::string message)
{
    s_log << get_timestamp() << " [" << s_logLevelString[level] << "]: " << message << std::endl;
}

std::tm Engine::Logger::localtime_xp_now()
{
    std::time_t timer = std::time(0);
    std::tm bt{};
#if defined(__unix__)
    localtime_r(&timer, &bt);
#elif defined(_MSC_VER)
    localtime_s(&bt, &timer);
#else
    static std::mutex mtx;
    std::lock_guard<std::mutex> lock(mtx);
    bt = *std::localtime(&timer);
#endif
    return bt;
}

std::string Engine::Logger::get_timestamp()
{
    std::tm now = localtime_xp_now();
    return std::format("[{0}-{1:02d}-{2:02d} {3:02d}:{4:02d}:{5:02d}]",
        now.tm_year + 1900,
        now.tm_mon + 1,
        now.tm_mday,
        now.tm_hour,
        now.tm_min,
        now.tm_sec
    );
}


const char* Engine::Logger::s_logLevelString[] = { "CRITICAL", "ERROR", "WARNING", "INFO", "VERBOSE", "DEBUG" };

std::ofstream Engine::Logger::s_log("logfile.txt", std::ios_base::app | std::ios_base::out);
