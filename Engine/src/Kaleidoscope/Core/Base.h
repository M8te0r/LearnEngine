#pragma once

#include <memory>



#ifdef KLD_PLATFORM_MACOS


#endif

// TODO: 需要支持KLD_ASSERT(x)也能用
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

//#define KLD_BIND_EVENT_FN(fn) std::bind(&fn, this, std::placeholders::_1)// 替换成下面的lambda函数
#define KLD_BIND_EVENT_FN(fn) [this](auto&&... args) -> decltype(auto) { return this->fn(std::forward<decltype(args)>(args)...); }



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
