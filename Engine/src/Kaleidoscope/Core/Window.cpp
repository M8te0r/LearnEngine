#include "kldpch.h"
#include "Kaleidoscope/Core/Window.h"

#ifdef KLD_PLATFORM_MACOS
#include "Platform/MacOS/MacOSWindow.h"
#endif // KLD_PLATFORM_MACOS

namespace Kaleidoscope 
{
	Scope<Window> Window::Create(const WindowProps& props)
	{
#ifdef KLD_PLATFORM_MACOS
		return CreateScope<MacOSWindow>(props);
#else
		KLD_CORE_ASSERT(false, "Unknown platform!");
		return nullptr;
#endif
	}

}
