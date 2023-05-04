#pragma once
#include <memory>

#include "Kaleidoscope/Core.h"
#include "spdlog/spdlog.h"
#include "spdlog/fmt/ostr.h"

namespace Kaleidoscope
{
    class Log
    {

    public:
        static void Init();
        inline static std::shared_ptr<spdlog::logger> &GetCoreLogger() { return s_CoreLogger; }
        inline static std::shared_ptr<spdlog::logger> &GetClientLogger() { return s_ClientLogger; }

    private:
        static std::shared_ptr<spdlog::logger> s_CoreLogger;
        static std::shared_ptr<spdlog::logger> s_ClientLogger;
    };

} // namespace Kaleidoscope

// core logger macros
#define KLD_CORE_TRACE(...) ::Kaleidoscope::Log::GetCoreLogger()->trace(__VA_ARGS__);
#define KLD_CORE_INFO(...) ::Kaleidoscope::Log::GetCoreLogger()->info(__VA_ARGS__);
#define KLD_CORE_WARN(...) ::Kaleidoscope::Log::GetCoreLogger()->warn(__VA_ARGS__);
#define KLD_CORE_ERROR(...) ::Kaleidoscope::Log::GetCoreLogger()->error(__VA_ARGS__);
#define KLD_CORE_FATAL(...) ::Kaleidoscope::Log::GetCoreLogger()->fatal(__VA_ARGS__);

// client logger macros
#define KLD_TRACE(...) ::Kaleidoscope::Log::GetClientLogger()->trace(__VA_ARGS__);
#define KLD_INFO(...) ::Kaleidoscope::Log::GetClientLogger()->info(__VA_ARGS__);
#define KLD_WARN(...) ::Kaleidoscope::Log::GetClientLogger()->warn(__VA_ARGS__);
#define KLD_ERROR(...) ::Kaleidoscope::Log::GetClientLogger()->error(__VA_ARGS__);
#define KLD_FATAL(...) ::Kaleidoscope::Log::GetClientLogger()->fatal(__VA_ARGS__);