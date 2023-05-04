#pragma once

#include "Core.h"
#include "Window.h"

namespace Kaleidoscope
{
    class Application
    {
    public:
        Application();
        virtual ~Application();
        void Run();

    private:
        std::unique_ptr<Window> m_Window;
        bool m_Running = true;
    };

    // 在客户端定义
    Application *CreateApplication();

} // namespace Kaleidoscope
