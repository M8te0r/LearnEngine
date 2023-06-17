#pragma once
#include <memory>

#include "Kaleidoscope/Core/Base.h"

// 忽略外部头文件产生的警告
#pragma warning(push, 0)
#include "spdlog/spdlog.h"
#include "spdlog/fmt/ostr.h"
#pragma warning(pop)

namespace Kaleidoscope
{
    class Log
    {

    public:
        static void Init();
        inline static Ref<spdlog::logger> &GetCoreLogger() { return s_CoreLogger; }
        inline static Ref<spdlog::logger> &GetClientLogger() { return s_ClientLogger; }

    private:
        static Ref<spdlog::logger> s_CoreLogger;
        static Ref<spdlog::logger> s_ClientLogger;
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