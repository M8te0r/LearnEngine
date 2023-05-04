#pragma once

#include "Kaleidoscope/Core.h"
#include "Kaleidoscope/Events/Event.h"
#include "Kaleidoscope/Events/ApplicationEvent.h"
#include "Kaleidoscope/Window.h"

namespace Kaleidoscope
{
    class Application
    {
    public:
        Application();
        virtual ~Application();
        void Run();

        void OnEvent(Event &e);

    private:
        bool OnWindowClose(WindowCloseEvent &e);
        std::unique_ptr<Window> m_Window;
        bool m_Running = true;
    };

    // 在客户端定义
    Application *CreateApplication();

} // namespace Kaleidoscope
