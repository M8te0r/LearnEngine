#include "Sandbox2D.h"
#include "imgui.h"

#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

#include "Platform/OpenGL/OpenGLShader.h"

Sandbox2D::Sandbox2D()
    : Layer("Sandbox2D"), m_CameraController(1280.0f / 720.f)
{
}

void Sandbox2D::OnAttach() 
{

    // 渲染正方形
    m_SquareVA = Kaleidoscope::VertexArray::Create();

    float squareVertices[5 * 4] = {
        -0.5f, -0.5f, 0.0f,
        0.5f, -0.5f, 0.0f,
        0.5f, 0.5f, 0.0f,
        -0.5f, 0.5f, 0.0f};
    Kaleidoscope::Ref<Kaleidoscope::VertexBuffer> squareVB;
    squareVB.reset(Kaleidoscope::VertexBuffer::Create(squareVertices, sizeof(squareVertices)));
    squareVB->SetLayout({{Kaleidoscope::ShaderDataType::Float3, "a_Position"}});
    m_SquareVA->AddVertexBuffer(squareVB);

    // 创建、绑定indexBuffer(同时将其添加至VertexArray中)
    uint32_t squareIndices[6] = {0, 1, 2, 2, 3, 0};
    Kaleidoscope::Ref<Kaleidoscope::IndexBuffer> squareIB;
    squareIB.reset(Kaleidoscope::IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t)));
    m_SquareVA->SetIndexBuffer(squareIB);
    // m_SquareVA->SetIndexBuffer(m_IndexBuffer);

    m_FlatColorShader = Kaleidoscope::Shader::Create("/Users/crystalized/cpp_project/LearnEngine/Sandbox/assets/shaders/FlatColor.glsl");
}

void Sandbox2D::OnDetach() 
{
}

void Sandbox2D::OnUpdate(Kaleidoscope::Timestep ts) 
{
    // Update
    m_CameraController.OnUpdate(ts);

    // Render
    Kaleidoscope::RenderCommand::SetClearColor({0.1f, 0.1f, 0.1f, 1.0f});
    Kaleidoscope::RenderCommand::Clear();

    Kaleidoscope::Renderer::BeginScene(m_CameraController.GetCamera());

    std::dynamic_pointer_cast<Kaleidoscope::OpenGLShader>(m_FlatColorShader)->Bind();
    std::dynamic_pointer_cast<Kaleidoscope::OpenGLShader>(m_FlatColorShader)->UploadUniformFloat4("u_Color", m_SquareColor);

    Kaleidoscope::Renderer::Submit(m_FlatColorShader, m_SquareVA, glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));

    Kaleidoscope::Renderer::EndScene();
}

void Sandbox2D::OnImGuiRender() 
{
    ImGui::Begin("Settings");
    ImGui::ColorEdit4("Square color", glm::value_ptr(m_SquareColor));
    ImGui::End();
}

void Sandbox2D::OnEvent(Kaleidoscope::Event &e) 
{
    m_CameraController.OnEvent(e);
}