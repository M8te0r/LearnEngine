#pragma once

#include <memory>

#ifdef KLD_PLATFORM_WINDOWS
#ifdef KLD_DYNAMIC_LINK
#ifdef KLD_BUILD_DLL
#define KLD_API ___declspec(dllexport)
#else
#define KLD_API ___declspec(dllimport)
#endif
#else
#define KLD_API
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

namespace Kaleidoscope
{
    template <typename T>
    using Scope = std::unique_ptr<T>;
    template<typename T,typename ...Args>
    constexpr Scope<T> CreateScope(Args&& ... args) 
    {
        return std::make_unique<T>(std::forward<Args>(args)...);
    }

    template <typename T>
    using Ref = std::shared_ptr<T>;
    template<typename T, typename ...Args>
    constexpr Ref<T> CreateRef(Args&& ... args)
    {
        return std::make_shared<T>(std::forward<Args>(args)...);
    }
} // namespace Kaleidoscope
