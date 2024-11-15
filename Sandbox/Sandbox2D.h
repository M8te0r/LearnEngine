#pragma once
#include "Engine.h"


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

    glm::vec4 m_SquareColor = {0.2f, 0.3f, 0.8f, 1.0f};



};
