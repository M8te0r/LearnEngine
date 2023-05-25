#include "Sandbox2D.h"
#include "imgui.h"

#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"


Sandbox2D::Sandbox2D()
    : Layer("Sandbox2D"), m_CameraController(1280.0f / 720.f)
{
}

void Sandbox2D::OnAttach()
{
    // m_CheckerboardTexture = Kaleidoscope::Texture2D::Create("/Users/crystalized/cpp_project/LearnEngine/Sandbox/assets/textures/Checkerboard.png");
    m_CheckerboardTexture = Kaleidoscope::Texture2D::Create("../Sandbox/assets/textures/Checkerboard.png");

   



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

    Kaleidoscope::Renderer2D::BeginScene(m_CameraController.GetCamera());

    Kaleidoscope::Renderer2D::DrawQuad({-1.0f, 0.0f}, {0.8f, 0.8f}, {0.8f, 0.2f, 0.3f, 1.0f});
    Kaleidoscope::Renderer2D::DrawQuad({0.5f, -0.5f}, {0.5f, 0.75f}, {0.2f, 0.3f, 0.8f, 1.0f});

    Kaleidoscope::Renderer2D::DrawQuad({ 0.0f, 0.0f, -0.1f }, { 10.0f, 10.0f }, m_CheckerboardTexture);



    Kaleidoscope::Renderer2D::EndScene();
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