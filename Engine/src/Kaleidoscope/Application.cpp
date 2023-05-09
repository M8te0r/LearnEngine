#include "kldpch.h"
#include "Kaleidoscope/Application.h"

#include "Kaleidoscope/Log.h"

#include "glad/glad.h"

#include "Kaleidoscope/Input.h"

#include "glm/glm.hpp"

namespace Kaleidoscope
{

#define BIND_EVENT_FN(x) std::bind(&Application::x, this, std::placeholders::_1)
    Application *Application::s_Instance = nullptr;

    Application::Application()
    {
        KLD_CORE_ASSERT(!s_Instance, "Application already exists!");
        s_Instance = this;
        m_Window = std::unique_ptr<Window>(Window::Create());
        m_Window->SetEventCallback(BIND_EVENT_FN(OnEvent));

        m_ImGuiLayer = new ImGuiLayer();
        PushOverlay(m_ImGuiLayer);

        // 创建、绑定顶点数组
        glGenVertexArrays(1, &m_VertexArray);
        glBindVertexArray(m_VertexArray);

        // 创建、绑定顶点缓冲
        glGenBuffers(1, &m_VertexBuffer);
        glBindBuffer(GL_ARRAY_BUFFER, m_VertexBuffer);

        // 顶点数据（CPU中
        float vertices[3 * 3] = {
            -0.5f, -0.5f, 0.0f,
            0.5f, -0.5f, 0.0f,
            0.0f, 0.5f, 0.0f};

        // 上传顶点数据到GPU
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

        // 告诉GPU数据内的信息是如何布局的
        glEnableVertexAttribArray(0);                                                // 数据中的信息1
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), nullptr); // 从0开始，包含3个浮点数，不启用归一化，步长为3*float，没有偏移

        // 创建、绑定索引缓冲
        glGenBuffers(1, &m_IndexBuffer);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IndexBuffer);

        unsigned int indices[3] = {0, 1, 2};
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

        std::string vertexSrc = R"(
            #version 330 core
            
            layout(location = 0) in vec3 a_Position;

            out vec3 v_Position;

            void main(){
                v_Position = a_Position;
                gl_Position = vec4(a_Position, 1.0);
            }
        )";

        std::string fragmentSrc = R"(
            #version 330 core
            
            layout(location = 0) out vec4  color;

            in vec3 v_Position;

            void main(){
                // color = vec4(0.8, 0.2, 0.3, 1.0);
                color = vec4(v_Position * 0.5 + 0.5, 1.0);
            }
        )";

        // 等价于m_Shader=std::make_unique<Shader>();
        m_Shader.reset(new Shader(vertexSrc, fragmentSrc));
    }

    Application::~Application()
    {
    }

    void Application::PushLayer(Layer *layer)
    {
        m_LayerStack.PushLayer(layer);
        layer->OnAttach();
    }

    void Application::PushOverlay(Layer *layer)
    {
        m_LayerStack.PushOverlay(layer);
        layer->OnAttach();
    }

    void Application::OnEvent(Event &e)
    {
        EventDispatcher dispatcher(e);

        dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(OnWindowClose));

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
        while (m_Running)
        {
            // glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
            glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT);

            m_Shader->Bind();

            // 启用顶点数据，并绘制
            glBindVertexArray(m_VertexArray);
            glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, nullptr);

            // 逐个更新layer
            for (Layer *layer : m_LayerStack)
            {
                layer->OnUpdate();
            }

            m_ImGuiLayer->Begin();
            for (Layer *layer : m_LayerStack)
            {
                layer->OnImGuiRender();
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

} // namespace Kaleidoscope
