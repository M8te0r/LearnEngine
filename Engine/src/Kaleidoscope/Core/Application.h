#pragma once

#include "Kaleidoscope/Core/Core.h"

#include "Kaleidoscope/Core/Window.h"
#include "Kaleidoscope/Core/LayerStack.h"
#include "Kaleidoscope/Events/Event.h"
#include "Kaleidoscope/Events/ApplicationEvent.h"

#include "Kaleidoscope/Core/Timestep.h"

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
        bool OnWindowResize(WindowResizeEvent &e);

    private:
        std::unique_ptr<Window> m_Window;
        ImGuiLayer *m_ImGuiLayer;
        bool m_Running = true;
        bool m_Minimized = false;
        LayerStack m_LayerStack;
        float m_LastFrameTime = 0.0f;

    private:
        static Application *s_Instance;
    };

    // 在客户端定义
    Application *CreateApplication();

} // namespace Kaleidoscope
