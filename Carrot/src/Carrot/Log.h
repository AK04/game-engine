#pragma once

#include "Core.h"
#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_color_sinks.h"

namespace Carrot {

	class CARROT_API Log {

	public:
		static void Init();

		inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }
		inline static std::shared_ptr<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }

	private:

		static std::shared_ptr<spdlog::logger> s_CoreLogger;
		static std::shared_ptr<spdlog::logger> s_ClientLogger;

	};

}

// Core Log macros

#define CT_CORE_TRACE(...)  ::Carrot::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define CT_CORE_INFO(...)   ::Carrot::Log::GetCoreLogger()->info(__VA_ARGS__)
#define CT_CORE_WARN(...)   ::Carrot::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define CT_CORE_ERROR(...)  ::Carrot::Log::GetCoreLogger()->error(__VA_ARGS__)
#define CT_CORE_FATAL(...)  ::Carrot::Log::GetCoreLogger()->fatal(__VA_ARGS__)

// Client Log macros

#define CT_TRACE(...)  ::Carrot::Log::GetClientLogger()->trace(__VA_ARGS__)
#define CT_INFO(...)   ::Carrot::Log::GetClientLogger()->info(__VA_ARGS__)
#define CT_WARN(...)   ::Carrot::Log::GetClientLogger()->warn(__VA_ARGS__)
#define CT_ERROR(...)  ::Carrot::Log::GetClientLogger()->error(__VA_ARGS__)
#define CT_FATAL(...)  ::Carrot::Log::GetClientLogger()->fatal(__VA_ARGS__)
