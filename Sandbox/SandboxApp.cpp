
#include "Engine.h"
#include "imgui.h"

class ExampleLayer : public Kaleidoscope::Layer
{
public:
    ExampleLayer()
        : Layer("Example"), m_Camera(-1.6f, 1.6f, -0.9f, 0.9f), m_CameraPosition(0.0f)
    {
        // 创建顶点数组
        m_VertexArray.reset(Kaleidoscope::VertexArray::Create());

        // 创建、绑定vertexBuffer(同时将其添加至VertexArray中)
        // 顶点数据（CPU中
        float vertices[3 * 7] = {
            -0.5f, -0.5f, 0.0f, 0.8f, 0.2f, 0.8f, 1.0f,
            0.5f, -0.5f, 0.0f, 0.2f, 0.3f, 0.8f, 1.0f,
            0.0f, 0.5f, 0.0f, 0.8f, 0.7f, 0.2f, 1.0f};

        std::shared_ptr<Kaleidoscope::VertexBuffer> vertexBuffer;
        // 等价于m_VertexBuffer buffer = VertexBuffer::Create(sizeof(vertices), vertices);
        vertexBuffer.reset(Kaleidoscope::VertexBuffer::Create(vertices, sizeof(vertices)));
        Kaleidoscope::BufferLayout layout = {
            {Kaleidoscope::ShaderDataType::Float3, "a_Position"},
            {Kaleidoscope::ShaderDataType::Float4, "a_Color"},

        };
        vertexBuffer->SetLayout(layout);
        m_VertexArray->AddVertexBuffer(vertexBuffer);

        // 创建、绑定indexBuffer(同时将其添加至VertexArray中)
        uint32_t indices[3] = {0, 1, 2};
        std::shared_ptr<Kaleidoscope::IndexBuffer> indexBuffer;

        indexBuffer.reset(Kaleidoscope::IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));
        m_VertexArray->SetIndexBuffer(indexBuffer);

        // 渲染正方形
        m_SquareVA.reset(Kaleidoscope::VertexArray::Create());
        float squareVertices[3 * 4] = {
            -0.75f, -0.75f, 0.0f,
            0.75f, -0.75f, 0.0f,
            0.75f, 0.75f, 0.0f,
            -0.75f, 0.75f, 0.0f};
        std::shared_ptr<Kaleidoscope::VertexBuffer> squareVB;
        squareVB.reset(Kaleidoscope::VertexBuffer::Create(squareVertices, sizeof(squareVertices)));
        squareVB->SetLayout({{Kaleidoscope::ShaderDataType::Float3, "a_Position"}});
        m_SquareVA->AddVertexBuffer(squareVB);

        // 创建、绑定indexBuffer(同时将其添加至VertexArray中)
        uint32_t squareIndices[6] = {0, 1, 2, 2, 3, 0};
        std::shared_ptr<Kaleidoscope::IndexBuffer> squareIB;
        squareIB.reset(Kaleidoscope::IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t)));
        m_SquareVA->SetIndexBuffer(squareIB);
        // m_SquareVA->SetIndexBuffer(m_IndexBuffer);

        std::string vertexSrc = R"(
            #version 330 core
            
            layout(location = 0) in vec3 a_Position;
            layout(location = 1) in vec4 a_Color;

            uniform mat4 u_ViewProjection;
            

            out vec3 v_Position;
            out vec4 v_Color;

            void main(){
                v_Position = a_Position;
                v_Color = a_Color;
                gl_Position = u_ViewProjection * vec4(a_Position, 1.0);
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
        m_Shader.reset(new Kaleidoscope::Shader(vertexSrc, fragmentSrc));

        std::string blueShaderVertexSrc = R"(
            #version 330 core
            
            layout(location = 0) in vec3 a_Position;

            uniform mat4 u_ViewProjection;

            out vec3 v_Position;

            void main(){
                v_Position = a_Position;
                gl_Position = u_ViewProjection * vec4(a_Position, 1.0);
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

        m_BlueShader.reset(new Kaleidoscope::Shader(blueShaderVertexSrc, blueShaderFragmentSrc));
    }

    void OnUpdate() override
    {
        if (Kaleidoscope::Input::IsKeyPressed(KLD_KEY_LEFT))
        {
            m_CameraPosition.x -= m_CameraMoveSpeed;
        }
        else if (Kaleidoscope::Input::IsKeyPressed(KLD_KEY_RIGHT))
        {
            m_CameraPosition.x += m_CameraMoveSpeed;
        }

        if (Kaleidoscope::Input::IsKeyPressed(KLD_KEY_UP))
        {
            m_CameraPosition.y += m_CameraMoveSpeed;
        }
        else if (Kaleidoscope::Input::IsKeyPressed(KLD_KEY_DOWN))
        {
            m_CameraPosition.y -= m_CameraMoveSpeed;
        }

        if (Kaleidoscope::Input::IsKeyPressed(KLD_KEY_A))
        {
            m_CameraRotation += m_CameraRotationSpeed;
        }
        else if (Kaleidoscope::Input::IsKeyPressed(KLD_KEY_D))
        {
            m_CameraRotation -= m_CameraRotationSpeed;
        }

        Kaleidoscope::RenderCommand::SetClearColor({0.1f, 0.1f, 0.1f, 1.0f});
        Kaleidoscope::RenderCommand::Clear();

        // m_Camera.SetPostion();
        m_Camera.SetPosition(m_CameraPosition);
        m_Camera.SetRotation(m_CameraRotation);

        Kaleidoscope::Renderer::BeginScene(m_Camera);

        Kaleidoscope::Renderer::Submit(m_BlueShader, m_SquareVA);

        Kaleidoscope::Renderer::Submit(m_Shader, m_VertexArray);

        Kaleidoscope::Renderer::EndScene();
    }

    virtual void OnImGuiRender() override
    {
    }

    void OnEvent(Kaleidoscope::Event &event) override
    {
    }

private:
    std::shared_ptr<Kaleidoscope::Shader> m_Shader;
    std::shared_ptr<Kaleidoscope::VertexArray> m_VertexArray;

    std::shared_ptr<Kaleidoscope::Shader> m_BlueShader;
    std::shared_ptr<Kaleidoscope::VertexArray> m_SquareVA;

    Kaleidoscope::OrthographicCamera m_Camera;
    glm::vec3 m_CameraPosition;
    float m_CameraMoveSpeed = 0.1f;
    float m_CameraRotation = 0.0f;
    float m_CameraRotationSpeed = 2.0f;
};

class Sandbox : public Kaleidoscope::Application
{
public:
    Sandbox()
    {
        PushLayer(new ExampleLayer());
    }
    ~Sandbox()
    {
    }
};

Kaleidoscope::Application *Kaleidoscope::CreateApplication()
{
    return new Sandbox();
}