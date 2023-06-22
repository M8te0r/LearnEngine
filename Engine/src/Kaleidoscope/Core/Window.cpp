#include "kldpch.h"
#include "Kaleidoscope/Core/Window.h"

#ifdef KLD_PLATFORM_MACOS
#include "Platform/MacOS/MacOSWindow.h"
#endif // KLD_PLATFORM_MACOS

#ifdef KLD_PLATFORM_WINDOWS
#include "Platform/Windows/WindowsWindow.h"
#endif // KLD_PLATFORM_WINDOWS

namespace Kaleidoscope 
{
	Scope<Window> Window::Create(const WindowProps& props)
	{

#ifdef KLD_PLATFORM_MACOS
		return CreateScope<MacOSWindow>(props);

#elif defined(KLD_PLATFORM_WINDOWS)
		return CreateScope<WindowsWindow>(props);

#else
		KLD_CORE_ASSERT(false, "Unknown platform!");
		return nullptr;
#endif

	}

}
