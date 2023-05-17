#include "kldpch.h"
#include "Kaleidoscope/Application.h"

#include "Kaleidoscope/Log.h"

#include "Kaleidoscope/Renderer/Renderer.h"

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

        // 创建顶点数组
        m_VertexArray.reset(VertexArray::Create());

        // 创建、绑定vertexBuffer(同时将其添加至VertexArray中)
        // 顶点数据（CPU中
        float vertices[3 * 7] = {
            -0.5f, -0.5f, 0.0f, 0.8f, 0.2f, 0.8f, 1.0f,
            0.5f, -0.5f, 0.0f, 0.2f, 0.3f, 0.8f, 1.0f,
            0.0f, 0.5f, 0.0f, 0.8f, 0.7f, 0.2f, 1.0f};

        std::shared_ptr<VertexBuffer> vertexBuffer;
        // 等价于m_VertexBuffer buffer = VertexBuffer::Create(sizeof(vertices), vertices);
        vertexBuffer.reset(VertexBuffer::Create(vertices, sizeof(vertices)));
        BufferLayout layout = {
            {ShaderDataType::Float3, "a_Position"},
            {ShaderDataType::Float4, "a_Color"},

        };
        vertexBuffer->SetLayout(layout);
        m_VertexArray->AddVertexBuffer(vertexBuffer);

        // 创建、绑定indexBuffer(同时将其添加至VertexArray中)
        uint32_t indices[3] = {0, 1, 2};
        std::shared_ptr<IndexBuffer> indexBuffer;

        indexBuffer.reset(IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));
        m_VertexArray->SetIndexBuffer(indexBuffer);

        // 渲染正方形
        m_SquareVA.reset(VertexArray::Create());
        float squareVertices[3 * 4] = {
            -0.75f, -0.75f, 0.0f,
            0.75f, -0.75f, 0.0f,
            0.75f, 0.75f, 0.0f,
            -0.75f, 0.75f, 0.0f};
        std::shared_ptr<VertexBuffer> squareVB;
        squareVB.reset(VertexBuffer::Create(squareVertices, sizeof(squareVertices)));
        squareVB->SetLayout({{ShaderDataType::Float3, "a_Position"}});
        m_SquareVA->AddVertexBuffer(squareVB);

        // 创建、绑定indexBuffer(同时将其添加至VertexArray中)
        uint32_t squareIndices[6] = {0, 1, 2, 2, 3, 0};
        std::shared_ptr<IndexBuffer> squareIB;
        squareIB.reset(IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t)));
        m_SquareVA->SetIndexBuffer(squareIB);
        // m_SquareVA->SetIndexBuffer(m_IndexBuffer);

        std::string vertexSrc = R"(
            #version 330 core
            
            layout(location = 0) in vec3 a_Position;
            layout(location = 1) in vec4 a_Color;

            

            out vec3 v_Position;
            out vec4 v_Color;

            void main(){
                v_Position = a_Position;
                v_Color = a_Color;
                gl_Position = vec4(a_Position, 1.0);
            }
        )";

        std::string fragmentSrc = R"(
            #version 330 core
            
            layout(location = 0) out vec4  color;

            in vec3 v_Position;
            in vec4 v_Color;


            void main(){
                // color = vec4(0.8, 0.2, 0.3, 1.0);
                // color = vec4(v_Position * 0.5 + 0.5, 1.0);
                color =  v_Color;
            }
        )";

        // 等价于m_Shader=std::make_unique<Shader>();
        m_Shader.reset(new Shader(vertexSrc, fragmentSrc));

        std::string blueShaderVertexSrc = R"(
            #version 330 core
            
            layout(location = 0) in vec3 a_Position;

            out vec3 v_Position;

            void main(){
                v_Position = a_Position;
                gl_Position = vec4(a_Position, 1.0);
            }
        )";

        std::string blueShaderFragmentSrc = R"(
            #version 330 core
            
            layout(location = 0) out vec4  color;

            in vec3 v_Position;

            void main(){
                color =  vec4(0.2, 0.3, 0.8, 1.0);
            }
        )";

        m_BlueShader.reset(new Shader(blueShaderVertexSrc, blueShaderFragmentSrc));
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

            RenderCommand::SetClearColor({0.1f, 0.1f, 0.1f, 1.0f});
            RenderCommand::Clear();

            Renderer::BeginScene();

            m_BlueShader->Bind();
            Renderer::Submit(m_SquareVA);

            m_Shader->Bind();
            Renderer::Submit(m_VertexArray);

            Renderer::EndScene();

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
