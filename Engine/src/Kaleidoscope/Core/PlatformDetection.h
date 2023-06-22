#pragma once

// Platform detection using predefined macros
#ifdef _WIN32
	#ifdef _WIN64
		#define KLD_PLATFORM_WINDOWS
	#else
		#error "x86 Builds are not supported!"
	#endif // _WIN64

#elif defined(__APPLE__)||defined(__MACH__)
	#define KLD_PLATFORM_MACOS
	
#endif // _WIN32


