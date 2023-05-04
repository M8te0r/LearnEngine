#include "Application.h"

#include "runtime/Events/ApplicationEvent.h"
#include "runtime/Log.h"

namespace Kaleidoscope
{
    Application::Application()
    {
    }

    Application::~Application()
    {
    }

    void Application::Run()
    {
        WindowResizeEvent e(1280, 720);
        if (e.IsInCategory(EventCategoryApplication))
        {
            KLD_TRACE(e);
        }

        if (e.IsInCategory(EventCategoryInput))
        {
            KLD_TRACE(e);
        }

        while (true)
            ;
    }
} // namespace Kaleidoscope
