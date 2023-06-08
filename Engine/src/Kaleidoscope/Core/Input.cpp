#include "kldpch.h"
#include "Kaleidoscope/Core/Input.h"

#ifdef KLD_PLATFORM_MACOS
#include "Platform/MacOS/MacOSInput.h"
#endif

namespace Kaleidoscope {

	Scope<Input> Input::s_Instance = Input::Create();

	Scope<Input> Input::Create()
	{
#ifdef KLD_PLATFORM_MACOS
		return CreateScope<MacOSInput>();
#else
		KLD_CORE_ASSERT(false, "Unknown platform!");
		return nullptr;
#endif
	}
}