#pragma once
#include <fstream>
#include <format>

namespace Engine
{
	enum LogLevel
	{
		Critical = 0,
		Error = 1,
		Warning = 2,
		Info = 3,
		Verbose = 4,
		Debug = 5
	};

	class Logger
	{

	private:
		// TODO: enum LogLevel to string
		static const char* s_logLevelString[];
		static std::ofstream s_log;
		static std::tm localtime_xp_now();
		static std::string get_timestamp();

		static void Log(LogLevel level, std::string message);

	public:
		template <class... Args>
		static void LogCritical(const std::string& fmt_string, Args&&... args) { Log(LogLevel::Critical, std::vformat(fmt_string, std::make_format_args(args...))); }

		template <class... Args>
		static void LogError(const std::string& fmt_string, Args&&... args) { Log(LogLevel::Error, std::vformat(fmt_string, std::make_format_args(args...))); }

		template <class... Args>
		static void LogWarning(const std::string& fmt_string, Args&&... args) { Log(LogLevel::Warning, std::vformat(fmt_string, std::make_format_args(args...))); }

		template <class... Args>
		static void LogInfo(const std::string& fmt_string, Args&&... args) { Log(LogLevel::Info, std::vformat(fmt_string, std::make_format_args(args...))); }

		template <class... Args>
		static void LogVerbose(const std::string& fmt_string, Args&&... args) { Log(LogLevel::Verbose, std::vformat(fmt_string, std::make_format_args(args...))); }

		template <class... Args>
		static void LogDebug(const std::string& fmt_string, Args&&... args) { Log(LogLevel::Debug, std::vformat(fmt_string, std::make_format_args(args...))); }

	};
}