#pragma once
#include "Kaleidoscope/Core/Base.h"

#ifdef KLD_PLATFORM_WINDOWS
extern Kaleidoscope::Application* Kaleidoscope::CreateApplication();
int main(int argc, char** argv)
{
	auto app = Kaleidoscope::CreateApplication();
	app->Run();
	delete app;
}
#endif

#ifdef KLD_PLATFORM_MACOS
extern Kaleidoscope::Application* Kaleidoscope::CreateApplication();
int main(int argc, char** argv)
{
	Kaleidoscope::Log::Init();

	KLD_PROFILE_BEGIN_SESSION("Startup", "KaleidoscopeProfile-Startup.json");
	auto app = Kaleidoscope::CreateApplication();
	KLD_PROFILE_END_SESSION();

	KLD_PROFILE_BEGIN_SESSION("Runtime", "KaleidoscopeProfile-Runtime.json");
	app->Run();
	KLD_PROFILE_END_SESSION();

	KLD_PROFILE_BEGIN_SESSION("Shutdown", "KaleidoscopeProfile-Shutdown.json");
	delete app;
	KLD_PROFILE_END_SESSION();
}
#endif