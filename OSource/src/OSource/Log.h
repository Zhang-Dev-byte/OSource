#pragma once

#include <memory>

#include "spdlog/spdlog.h"

namespace OSource {

	class Log
	{
	public:
		static void Init();

		inline static std::shared_ptr<spdlog::logger>& GetCoreLogger(); //{ return s_CoreLogger; }
	    inline static std::shared_ptr<spdlog::logger>& GetClientLogger(); //{ return s_ClientLogger; }
	private:
		static std::shared_ptr<spdlog::logger> s_CoreLogger;
		static std::shared_ptr<spdlog::logger> s_ClientLogger;
	};

}

// Core log macros
#define OS_CORE_TRACE(...)    ::OSource::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define OS_CORE_INFO(...)     ::OSource::Log::GetCoreLogger()->info(__VA_ARGS__)
#define OS_CORE_WARN(...)     ::OSource::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define OS_CORE_ERROR(...)    ::OSource::Log::GetCoreLogger()->error(__VA_ARGS__)
#define OS_CORE_FATAL(...)    ::OSource::Log::GetCoreLogger()->fatal(__VA_ARGS__)

// Client log macros
#define OS_TRACE(...)	      ::OSource::Log::GetClientLogger()->trace(__VA_ARGS__)
#define OS_INFO(...)	      ::OSource::Log::GetClientLogger()->info(__VA_ARGS__)
#define OS_WARN(...)	      ::OSource::Log::GetClientLogger()->warn(__VA_ARGS__)
#define OS_ERROR(...)	      ::OSource::Log::GetClientLogger()->error(__VA_ARGS__)
#define OS_FATAL(...)	      ::OSource::Log::GetClientLogger()->fatal(__VA_ARGS__)