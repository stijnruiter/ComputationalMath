#include "Logger.hpp"
#include <ctime>
#include <mutex>
#include <format>

void Render::Debug::Logger::Log(LogLevel level, const std::string& message)
{
    s_log << get_timestamp() << " [" << s_logLevelString[level] << "]: " << message << std::endl;
}

std::tm Render::Debug::Logger::localtime_xp_now()
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

std::string Render::Debug::Logger::get_timestamp()
{
    char buffer[20];
    std::tm now = localtime_xp_now();
    std::strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", &now);
    return buffer;
}

const char* Render::Debug::Logger::s_logLevelString[] = {"CRITICAL", "ERROR", "WARNING", "INFO", "VERBOSE", "DEBUG"};

std::ofstream Render::Debug::Logger::s_log("logfile.txt", std::ios_base::app | std::ios_base::out);
