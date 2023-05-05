#pragma once

#include "Kaleidoscope/Window.h"
#include "Kaleidoscope/LayerStack.h"
#include "Kaleidoscope/Events/Event.h"
#include "Kaleidoscope/Events/ApplicationEvent.h"

namespace Kaleidoscope
{
    class Application
    {
    public:
        Application();
        virtual ~Application();
        void Run();

        void OnEvent(Event &e);

        void PushLayer(Layer *layer);
        void PushOverlay(Layer *layer);

    private:
        bool OnWindowClose(WindowCloseEvent &e);
        std::unique_ptr<Window> m_Window;
        bool m_Running = true;
        LayerStack m_LayerStack;
    };

    // 在客户端定义
    Application *CreateApplication();

} // namespace Kaleidoscope
