#include "kldpch.h"
#include "Kaleidoscope/Core/Application.h"

#include "Kaleidoscope/Core/Log.h"

#include "Kaleidoscope/Renderer/Renderer.h"

#include "Kaleidoscope/Core/Input.h"

#include "GLFW/glfw3.h"

namespace Kaleidoscope
{

    Application *Application::s_Instance = nullptr;

    Application::Application()
    {
        KLD_PROFILE_FUNCTION();

        KLD_CORE_ASSERT(!s_Instance, "Application already exists!");
        s_Instance = this;
        m_Window = Window::Create();
        m_Window->SetEventCallback(KLD_BIND_EVENT_FN(Application::OnEvent));

        // m_Window->SetVSync(false);

        Renderer::Init();

        m_ImGuiLayer = new ImGuiLayer();
        PushOverlay(m_ImGuiLayer);
    }

    Application::~Application()
    {
        KLD_PROFILE_FUNCTION();

        Renderer::Shutdown();
    }

    void Application::PushLayer(Layer *layer)
    {
        KLD_PROFILE_FUNCTION();

        m_LayerStack.PushLayer(layer);
        layer->OnAttach();
    }

    void Application::PushOverlay(Layer *layer)
    {
        KLD_PROFILE_FUNCTION();

        m_LayerStack.PushOverlay(layer);
        layer->OnAttach();
    }

    void Application::OnEvent(Event &e)
    {
        KLD_PROFILE_FUNCTION();

        EventDispatcher dispatcher(e);

        dispatcher.Dispatch<WindowCloseEvent>(KLD_BIND_EVENT_FN(Application::OnWindowClose));
        dispatcher.Dispatch<WindowResizeEvent>(KLD_BIND_EVENT_FN(Application::OnWindowResize));

        // 从后向前执行layer的event
        for (auto it = m_LayerStack.end(); it != m_LayerStack.begin();)
        {
            (*--it)->OnEvent(e);
            // 如果这个event已经处理过了，则跳过
            if (e.Handled)
            {
                break;
            }
        }
    }

    void Application::Run()
    {
        KLD_PROFILE_FUNCTION();

        while (m_Running)
        {
            KLD_PROFILE_SCOPE("RunLoop");

            float time = (float)glfwGetTime(); // 使用平台对应的获取时间函数
            Timestep timestep = time - m_LastFrameTime;
            m_LastFrameTime = time;

            // 逐个更新layer(最小化时窗口不渲染，但是imgui因为有docking功能，依旧保持渲染)
            if (!m_Minimized)
            {
                {
                    KLD_PROFILE_SCOPE("LayerStack OnUpdate");
                    for (Layer *layer : m_LayerStack)
                    {
                        layer->OnUpdate(timestep);
                    }
                }
            }

            m_ImGuiLayer->Begin();
            {
                KLD_PROFILE_SCOPE("LayerStack OnImGuiRender");
                for (Layer *layer : m_LayerStack)
                {
                    layer->OnImGuiRender();
                }
            }
            m_ImGuiLayer->End();

            m_Window->OnUpdate();
        }
    }

    bool Application::OnWindowClose(WindowCloseEvent &e)
    {
        m_Running = false;
        return true;
    }

    bool Application::OnWindowResize(WindowResizeEvent &e)
    {
        KLD_PROFILE_FUNCTION();

        // 当最小化的时候停止渲染，节省资源
        if (e.GetWidth() == 0 || e.GetHeight() == 0)
        {
            m_Minimized = true;
            return false;
        }
        m_Minimized = false;
        Renderer::OnWindowResize(e.GetWidth(), e.GetHeight());

        return true;
    }

} // namespace Kaleidoscope
