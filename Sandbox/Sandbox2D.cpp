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
    KLD_PROFILE_FUNCTION();

    // m_CheckerboardTexture = Kaleidoscope::Texture2D::Create("/Users/crystalized/cpp_project/LearnEngine/Sandbox/assets/textures/Checkerboard.png");
    m_CheckerboardTexture = Kaleidoscope::Texture2D::Create("../Sandbox/assets/textures/Checkerboard.png");
}

void Sandbox2D::OnDetach()
{
    KLD_PROFILE_FUNCTION();
}

void Sandbox2D::OnUpdate(Kaleidoscope::Timestep ts)
{
    KLD_PROFILE_FUNCTION();

    // Update

    m_CameraController.OnUpdate(ts);

    // Render
    // Reset stats here
    Kaleidoscope::Renderer2D::ResetStats();
    {
        KLD_PROFILE_SCOPE("Renderer Prep");
        Kaleidoscope::RenderCommand::SetClearColor({0.1f, 0.1f, 0.1f, 1.0f});
        Kaleidoscope::RenderCommand::Clear();
    }

    {
        static float rotation = 0.0f;
        rotation += ts * 50.0f;
        KLD_PROFILE_SCOPE("Renderer Draw");

        Kaleidoscope::Renderer2D::BeginScene(m_CameraController.GetCamera());

        Kaleidoscope::Renderer2D::DrawRotateQuad({1.0f, 0.0f}, {0.8f, 0.8f},-45.0f, {0.8f, 0.2f, 0.3f, 1.0f});
        Kaleidoscope::Renderer2D::DrawQuad({-1.0f, 0.0f}, {0.8f, 0.8f}, {0.8f, 0.2f, 0.3f, 1.0f});
        Kaleidoscope::Renderer2D::DrawQuad({0.5f, -0.5f}, {0.5f, 0.75f}, {0.2f, 0.3f, 0.8f, 1.0f});
        Kaleidoscope::Renderer2D::DrawQuad({0.0f, 0.0f, -0.1f}, {20.0f, 20.0f}, m_CheckerboardTexture, 10.0f);
        Kaleidoscope::Renderer2D::DrawRotateQuad({ -2.0f, 0.0f, 0.0f }, { 1.0f, 1.0f }, rotation, m_CheckerboardTexture, 20.0f);

        Kaleidoscope::Renderer2D::EndScene();


        Kaleidoscope::Renderer2D::BeginScene(m_CameraController.GetCamera());
        for (float y = -5.0f; y < 5.0f; y += 0.5f) 
        {
            for (float x = -5.0f; x < 5.0f; x += 0.5f) 
            {
                glm::vec4 color = { (x + 5.0f) / 10.0f, 0.4f, (y + 5.0f) / 10.0f ,0.7f };
                Kaleidoscope::Renderer2D::DrawQuad({ x, y }, { 0.45f, 0.45f }, color);

            }
        }
        Kaleidoscope::Renderer2D::EndScene();


    }
}

void Sandbox2D::OnImGuiRender()
{
    KLD_PROFILE_FUNCTION();

    ImGui::Begin("Settings");
    auto stats = Kaleidoscope::Renderer2D::GetStats();
    ImGui::Text("Renderer2D Stats:");
    ImGui::Text("Draw Calls: %d", stats.DrawCalls);
    ImGui::Text("Quads: %d", stats.QuadCount);
    ImGui::Text("Vertices: %d", stats.GetTotalVertexCount());
    ImGui::Text("Indices: %d", stats.GetTotalIndexCount());

    ImGui::ColorEdit4("Square color", glm::value_ptr(m_SquareColor));
    ImGui::End();
}

void Sandbox2D::OnEvent(Kaleidoscope::Event &e)
{
    m_CameraController.OnEvent(e);
}