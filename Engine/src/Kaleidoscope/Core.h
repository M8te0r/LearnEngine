#pragma once

#ifdef KLD_PLATFORM_WINDOWS
#ifdef KLD_BUILD_DLL
#define KLD_API ___declspec(dllexport)
#else
#define KLD_API ___declspec(dllimport)
#endif

#endif

#ifdef KLD_PLATFORM_MACOS
#define KLD_API
#endif

// 调试用
#ifdef KLD_ENABLE_ASSERTS
#define KLD_ASSERT(x, ...)                                    \
    {                                                         \
        if (!(x))                                             \
        {                                                     \
            KLD_ERROR("Assertion Failed: {0}", __VAR_ARGS__); \
            __debugbreak();                                   \
        }                                                     \
    }
#define KLD_CORE_ASSERT(x, ...)                                    \
    {                                                              \
        if (!(x))                                                  \
        {                                                          \
            KLD_CORE_ERROR("Assertion Failed: {0}", __VAR_ARGS__); \
            __debugbreak();                                        \
        }                                                          \
    }
#else
#define KLD_ASSERT(x, ...)
#define KLD_CORE_ASSERT(x, ...)
#endif

#define BIT(x) (1 << x)

#define KLD_BIND_EVENT_FN(fn) std::bind(&fn, this, std::placeholders::_1)
