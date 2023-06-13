#include "kldpch.h"
#include "Kaleidoscope/Core/Log.h"

#include "spdlog/sinks/stdout_color_sinks.h"
#include "spdlog/sinks/basic_file_sink.h"

namespace Kaleidoscope
{
    Ref<spdlog::logger> Log::s_CoreLogger;
    Ref<spdlog::logger> Log::s_ClientLogger;

    void Log::Init()
    {
        spdlog::set_pattern("%^[%T] %n: %v%$"); // time, name of the logger, msg content
        s_CoreLogger = spdlog::stdout_color_mt("Engine");
        s_CoreLogger->set_level(spdlog::level::trace);

        s_ClientLogger = spdlog::stdout_color_mt("APP");
        s_ClientLogger->set_level(spdlog::level::trace);
    }

} // namespace Kaleidoscope
