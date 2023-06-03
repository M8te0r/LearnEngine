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
    m_SpriteSheet = Kaleidoscope::Texture2D::Create("../Sandbox/assets/game/textures/RPGpack_sheet_2X.png");

    // Init here
    m_Particle.ColorBegin = {254 / 255.0f, 212 / 255.0f, 123 / 255.0f, 1.0f};
    m_Particle.ColorEnd = {254 / 255.0f, 109 / 255.0f, 41 / 255.0f, 1.0f};
    m_Particle.SizeBegin = 0.5f, m_Particle.SizeVariation = 0.3f, m_Particle.SizeEnd = 0.0f;
    m_Particle.LifeTime = 1.0f;
    m_Particle.Velocity = {0.0f, 0.0f};
    m_Particle.VelocityVariation = {3.0f, 1.0f};
    m_Particle.Position = {0.0f, 0.0f};
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
#if 0
    // 4个Quad
    {
        static float rotation = 0.0f;
        rotation += ts * 50.0f;
        KLD_PROFILE_SCOPE("Renderer Draw");

        Kaleidoscope::Renderer2D::BeginScene(m_CameraController.GetCamera());

        Kaleidoscope::Renderer2D::DrawRotateQuad({1.0f, 0.0f}, {0.8f, 0.8f}, glm::radians(-45.0f), {0.8f, 0.2f, 0.3f, 1.0f});
        Kaleidoscope::Renderer2D::DrawQuad({-1.0f, 0.0f}, {0.8f, 0.8f}, {0.8f, 0.2f, 0.3f, 1.0f});
        Kaleidoscope::Renderer2D::DrawQuad({0.5f, -0.5f}, {0.5f, 0.75f}, {0.2f, 0.3f, 0.8f, 1.0f});
        Kaleidoscope::Renderer2D::DrawQuad({0.0f, 0.0f, -0.1f}, {20.0f, 20.0f}, m_CheckerboardTexture, 10.0f);
        Kaleidoscope::Renderer2D::DrawRotateQuad({-2.0f, 0.0f, 0.0f}, {1.0f, 1.0f}, glm::radians(rotation), m_CheckerboardTexture, 20.0f);

        Kaleidoscope::Renderer2D::EndScene();

        Kaleidoscope::Renderer2D::BeginScene(m_CameraController.GetCamera());
        for (float y = -5.0f; y < 5.0f; y += 0.5f)
        {
            for (float x = -5.0f; x < 5.0f; x += 0.5f)
            {
                glm::vec4 color = {(x + 5.0f) / 10.0f, 0.4f, (y + 5.0f) / 10.0f, 0.7f};
                Kaleidoscope::Renderer2D::DrawQuad({x, y}, {0.45f, 0.45f}, color);
            }
        }
        Kaleidoscope::Renderer2D::EndScene();
    }
#endif
    // 粒子系统
    if (Kaleidoscope::Input::IsMouseButtonPressed(KLD_MOUSE_BUTTON_LEFT))
    {
        auto [x, y] = Kaleidoscope::Input::GetMousePosition();
        auto width = Kaleidoscope::Application::Get().GetWindow().GetWidth();
        auto height = Kaleidoscope::Application::Get().GetWindow().GetHeight();

        auto bounds = m_CameraController.GetBounds();
        auto pos = m_CameraController.GetCamera().GetPosition();
        x = (x / width) * bounds.GetWidth() - bounds.GetWidth() * 0.5f;
        y = bounds.GetHeight() * 0.5f - (y / height) * bounds.GetHeight();
        m_Particle.Position = {x + pos.x, y + pos.y};
        for (int i = 0; i < 5; i++)
            m_ParticleSystem.Emit(m_Particle);
    }

    // 游戏材质
    Kaleidoscope::Renderer2D::BeginScene(m_CameraController.GetCamera());
    Kaleidoscope::Renderer2D::DrawQuad({0.0f, 0.0f, 0.0f}, {1.0f, 1.0f}, m_SpriteSheet);
    Kaleidoscope::Renderer2D::EndScene();

    m_ParticleSystem.OnUpdate(ts);
    m_ParticleSystem.OnRender(m_CameraController.GetCamera());
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