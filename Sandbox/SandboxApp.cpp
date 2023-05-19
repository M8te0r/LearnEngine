
#include "Engine.h"

#include "Platform/OpenGL/OpenGLShader.h"

#include "imgui.h"

#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

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

        Kaleidoscope::Ref<Kaleidoscope::VertexBuffer> vertexBuffer;
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
        Kaleidoscope::Ref<Kaleidoscope::IndexBuffer> indexBuffer;

        indexBuffer.reset(Kaleidoscope::IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));
        m_VertexArray->SetIndexBuffer(indexBuffer);

        // 渲染正方形
        m_SquareVA.reset(Kaleidoscope::VertexArray::Create());
        float squareVertices[5 * 4] = {
            -0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
            0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
            0.5f, 0.5f, 0.0f, 1.0f, 1.0f,
            -0.5f, 0.5f, 0.0f, 0.0f, 1.0f};
        Kaleidoscope::Ref<Kaleidoscope::VertexBuffer> squareVB;
        squareVB.reset(Kaleidoscope::VertexBuffer::Create(squareVertices, sizeof(squareVertices)));
        squareVB->SetLayout({{Kaleidoscope::ShaderDataType::Float3, "a_Position"},
                             {Kaleidoscope::ShaderDataType::Float2, "a_TexCoord"}});
        m_SquareVA->AddVertexBuffer(squareVB);

        // 创建、绑定indexBuffer(同时将其添加至VertexArray中)
        uint32_t squareIndices[6] = {0, 1, 2, 2, 3, 0};
        Kaleidoscope::Ref<Kaleidoscope::IndexBuffer> squareIB;
        squareIB.reset(Kaleidoscope::IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t)));
        m_SquareVA->SetIndexBuffer(squareIB);
        // m_SquareVA->SetIndexBuffer(m_IndexBuffer);

        std::string vertexSrc = R"(
            #version 330 core
            
            layout(location = 0) in vec3 a_Position;
            layout(location = 1) in vec4 a_Color;

            uniform mat4 u_ViewProjection;
            uniform mat4 u_Transform;
            

            out vec3 v_Position;
            out vec4 v_Color;

            void main(){
                v_Position = a_Position;
                v_Color = a_Color;
                gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);
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
        m_Shader.reset(Kaleidoscope::Shader::Create(vertexSrc, fragmentSrc));

        std::string flatColorShaderVertexSrc = R"(
            #version 330 core
            
            layout(location = 0) in vec3 a_Position;

            uniform mat4 u_ViewProjection;
            uniform mat4 u_Transform;

            out vec3 v_Position;

            void main(){
                v_Position = a_Position;
                gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);
            }
        )";

        std::string flatColorShaderFragmentSrc = R"(
            #version 330 core
            
            layout(location = 0) out vec4  color;

            in vec3 v_Position;

            uniform vec3 u_Color;

            void main(){
                color =  vec4( u_Color, 1.0);
            }
        )";

        m_FlatColorShader.reset(Kaleidoscope::Shader::Create(flatColorShaderVertexSrc, flatColorShaderFragmentSrc));

        std::string textureShaderVertexSrc = R"(
            #version 330 core
            
            layout(location = 0) in vec3 a_Position;
            layout(location = 1) in vec2 a_TexCoord;

            uniform mat4 u_ViewProjection;
            uniform mat4 u_Transform;

            out vec2 v_TexCoord;

            void main(){
                v_TexCoord = a_TexCoord;
                gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);
            }
        )";

        std::string textureShaderFragmentSrc = R"(
            #version 330 core
            
            layout(location = 0) out vec4  color;

            in vec2 v_TexCoord ;

            uniform sampler2D u_Texture;

            void main(){
                color =  texture(u_Texture,  v_TexCoord);
            }
        )";

        m_TextureShader.reset(Kaleidoscope::Shader::Create(textureShaderVertexSrc, textureShaderFragmentSrc));

        m_Texture = Kaleidoscope::Texture2D::Create("../Sandbox/assets/textures/Checkerboard.png");

        std::dynamic_pointer_cast<Kaleidoscope::OpenGLShader>(m_TextureShader)->Bind();
        std::dynamic_pointer_cast<Kaleidoscope::OpenGLShader>(m_TextureShader)->UploadUniformInt("u_Texture", 0);
    }

    void OnUpdate(Kaleidoscope::Timestep ts) override
    {
        KLD_TRACE("Delta time {0}s {1}ms", ts.GetSeconds(), ts.GetMilliseconds());

        if (Kaleidoscope::Input::IsKeyPressed(KLD_KEY_LEFT))
        {
            m_CameraPosition.x -= m_CameraMoveSpeed * ts;
        }
        else if (Kaleidoscope::Input::IsKeyPressed(KLD_KEY_RIGHT))
        {
            m_CameraPosition.x += m_CameraMoveSpeed * ts;
        }

        if (Kaleidoscope::Input::IsKeyPressed(KLD_KEY_UP))
        {
            m_CameraPosition.y += m_CameraMoveSpeed * ts;
        }
        else if (Kaleidoscope::Input::IsKeyPressed(KLD_KEY_DOWN))
        {
            m_CameraPosition.y -= m_CameraMoveSpeed * ts;
        }

        if (Kaleidoscope::Input::IsKeyPressed(KLD_KEY_A))
        {
            m_CameraRotation += m_CameraRotationSpeed * ts;
        }
        else if (Kaleidoscope::Input::IsKeyPressed(KLD_KEY_D))
        {
            m_CameraRotation -= m_CameraRotationSpeed * ts;
        }

        Kaleidoscope::RenderCommand::SetClearColor({0.1f, 0.1f, 0.1f, 1.0f});
        Kaleidoscope::RenderCommand::Clear();

        // m_Camera.SetPostion();
        m_Camera.SetPosition(m_CameraPosition);
        m_Camera.SetRotation(m_CameraRotation);

        Kaleidoscope::Renderer::BeginScene(m_Camera);

        glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(0.1f)); // 因为不需要一直计算，所以可以定义为static或者设置为成员变量，从而优化性能

        std::dynamic_pointer_cast<Kaleidoscope::OpenGLShader>(m_FlatColorShader)->Bind();
        std::dynamic_pointer_cast<Kaleidoscope::OpenGLShader>(m_FlatColorShader)->UploadUniformFloat3("u_Color", m_SquareColor);

        for (int y = 0; y < 20; y++)
        {
            for (int x = 0; x < 20; x++)
            {
                glm::vec3 pos(x * 0.11f, y * 0.11f, 0.0f);
                glm::mat4 transform = glm::translate(glm::mat4(1.0f), pos) * scale;

                Kaleidoscope::Renderer::Submit(m_FlatColorShader, m_SquareVA, transform);
            }
        }

        m_Texture->Bind();

        Kaleidoscope::Renderer::Submit(m_TextureShader, m_SquareVA, glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));

        // Triangle
        // Kaleidoscope::Renderer::Submit(m_Shader, m_VertexArray);

        Kaleidoscope::Renderer::EndScene();
    }

    virtual void OnImGuiRender() override
    {
        ImGui::Begin("Settings");
        ImGui::ColorEdit3("Square color", glm::value_ptr(m_SquareColor));
        ImGui::End();
    }

    void OnEvent(Kaleidoscope::Event &event) override
    {
    }

private:
    Kaleidoscope::Ref<Kaleidoscope::Shader> m_Shader;
    Kaleidoscope::Ref<Kaleidoscope::VertexArray> m_VertexArray;

    Kaleidoscope::Ref<Kaleidoscope::Shader> m_FlatColorShader, m_TextureShader;
    Kaleidoscope::Ref<Kaleidoscope::VertexArray> m_SquareVA;

    Kaleidoscope::Ref<Kaleidoscope::Texture2D> m_Texture;

    Kaleidoscope::OrthographicCamera m_Camera;
    glm::vec3 m_CameraPosition;
    float m_CameraMoveSpeed = 5.0f; // 5 unit per second(VSync off)

    float m_CameraRotation = 0.0f;
    float m_CameraRotationSpeed = 180.0f; // 180 degree per second(VSync off)

    glm::vec3 m_SquareColor = {0.2f, 0.3f, 0.8f};
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