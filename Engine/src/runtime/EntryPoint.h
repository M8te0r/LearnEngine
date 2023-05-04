#pragma once

#ifdef KLD_PLATFORM_WINDOWS
extern Kaleidoscope::Application *Kaleidoscope::CreateApplication();
int main(int argc, char **argv)
{
    auto app = Kaleidoscope::CreateApplication();
    app->Run();
    delete app;
}
#endif

#ifdef KLD_PLATFORM_MACOS
extern Kaleidoscope::Application *Kaleidoscope::CreateApplication();
int main(int argc, char **argv)
{
    Kaleidoscope::Log::Init();
    KLD_CORE_WARN("Initialized Log!");
    KLD_INFO("Hello");

    auto app = Kaleidoscope::CreateApplication();
    app->Run();
    delete app;
}
#endif