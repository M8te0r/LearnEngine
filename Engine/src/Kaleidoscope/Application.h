#pragma once

#include "Kaleidoscope/Core.h"


#include "Kaleidoscope/Window.h"
#include "Kaleidoscope/LayerStack.h"
#include "Kaleidoscope/Events/Event.h"
#include "Kaleidoscope/Events/ApplicationEvent.h"
#include "Kaleidoscope/ImGui/ImGuiLayer.h"

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

        inline Window &GetWindow() { return *m_Window; }
        inline static Application &Get() { return *s_Instance; }

    private:
        bool OnWindowClose(WindowCloseEvent &e);
        std::unique_ptr<Window> m_Window;
        ImGuiLayer* m_ImGuiLayer;
        bool m_Running = true;
        LayerStack m_LayerStack;

    private:
        static Application *s_Instance;
    };

    // 在客户端定义
    Application *CreateApplication();

} // namespace Kaleidoscope
