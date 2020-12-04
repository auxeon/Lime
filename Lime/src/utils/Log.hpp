#ifndef LOG_HPP
#define LOG_HPP


//#define SILENT


#include "Pch.hpp"
#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_color_sinks.h"
class Log {
public:
	static std::shared_ptr<spdlog::logger>& getCorelogger() {
		return mCoreLogger;
	}
	static std::shared_ptr<spdlog::logger>& getClientlogger() {
		return mClientLogger;
	}
	static void init() {
		spdlog::set_pattern("%^[%T] %n: %v%$");
		mCoreLogger = spdlog::stdout_color_mt("LIME");
		mCoreLogger->set_level(spdlog::level::trace);

		mClientLogger = spdlog::stdout_color_mt("APP");
		mClientLogger->set_level(spdlog::level::trace);
	}
private:
	static std::shared_ptr<spdlog::logger> mCoreLogger;
	static std::shared_ptr<spdlog::logger> mClientLogger;
};

#ifndef SILENT

#define LM_CORE_ERROR(...)	Log::getCorelogger()->error(__VA_ARGS__);
#define LM_CORE_WARN(...)	Log::getCorelogger()->warn(__VA_ARGS__);
#define LM_CORE_INFO(...)	Log::getCorelogger()->info(__VA_ARGS__);
#define LM_CORE_TRACE(...)	Log::getCorelogger()->trace(__VA_ARGS__);
#define LM_CORE_FATAL(...)	Log::getCorelogger()->fatal(__VA_ARGS__);


#define LM_ERROR(...)	Log::getClientlogger()->error(__VA_ARGS__);
#define LM_WARN(...)	Log::getClientlogger()->warn(__VA_ARGS__);
#define LM_INFO(...)	Log::getClientlogger()->info(__VA_ARGS__);
#define LM_TRACE(...)	Log::getClientlogger()->trace(__VA_ARGS__);
#define LM_FATAL(...)	Log::getClientlogger()->fatal(__VA_ARGS__);

#endif


#ifdef SILENT
#define LM_CORE_ERROR(...)
#define LM_CORE_WARN(...)
#define LM_CORE_INFO(...)
#define LM_CORE_TRACE(...)
#define LM_CORE_FATAL(...)


#define LM_ERROR(...)
#define LM_WARN(...)
#define LM_INFO(...)
#define LM_TRACE(...)
#define LM_FATAL(...)	
#endif

#endif