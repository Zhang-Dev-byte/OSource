  
#include "Log.h"

#include "spdlog/sinks/stdout_color_sinks.h"

#include "spdlog/spdlog.h"


std::shared_ptr<spdlog::logger> OSource::Log::s_CoreLogger;
std::shared_ptr<spdlog::logger> OSource::Log::s_ClientLogger;

void OSource::Log::Init()
{
	spdlog::set_pattern("%^[%T] %n: %v%$");
	s_CoreLogger = spdlog::stdout_color_mt("OSOURCE");
	s_CoreLogger->set_level(spdlog::level::trace);

	s_ClientLogger = spdlog::stdout_color_mt("APP");
	s_ClientLogger->set_level(spdlog::level::trace);
}

std::shared_ptr<spdlog::logger>& OSource::Log::GetCoreLogger() { return s_CoreLogger; }
std::shared_ptr<spdlog::logger>& OSource::Log::GetClientLogger() { return s_ClientLogger; }
    