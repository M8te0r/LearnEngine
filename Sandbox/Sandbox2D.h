#pragma once
#include "Engine.h"

#include "ParticleSystem.h"

class Sandbox2D : public Kaleidoscope::Layer
{
public:
    Sandbox2D();
    virtual ~Sandbox2D() = default;

    virtual void OnAttach() override;
    virtual void OnDetach() override;
    void OnUpdate(Kaleidoscope::Timestep ts) override;
    virtual void OnImGuiRender() override;
    void OnEvent(Kaleidoscope::Event &e) override;

private:
    Kaleidoscope::OrthographicCameraController m_CameraController;

    // Temp
    Kaleidoscope::Ref<Kaleidoscope::VertexArray> m_SquareVA;
    Kaleidoscope::Ref<Kaleidoscope::Shader> m_FlatColorShader;

    Kaleidoscope::Ref<Kaleidoscope::Texture2D> m_CheckerboardTexture;
    Kaleidoscope::Ref<Kaleidoscope::Texture2D> m_SpriteSheet;
    Kaleidoscope::Ref<Kaleidoscope::SubTexture2D> m_TextureStairs, m_TextureBarrel, m_TextureTree;

    glm::vec4 m_SquareColor = {0.2f, 0.3f, 0.8f, 1.0f};

    ParticleSystem m_ParticleSystem;
    ParticleProps m_Particle;
};
