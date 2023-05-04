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

#define BIT(x) (1 << x)
