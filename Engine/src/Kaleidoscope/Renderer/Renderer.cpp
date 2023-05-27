#include "kldpch.h"
#include "Kaleidoscope/Renderer/Renderer.h"
#include "Platform/OpenGL/OpenGLShader.h"
#include "Kaleidoscope/Renderer/Renderer2D.h"

namespace Kaleidoscope
{
    Scope<Renderer::SceneData> Renderer::s_SceneData = CreateScope<Renderer::SceneData>();

    void Renderer::Init()
    {
        KLD_PROFILE_FUNCTION();

        RenderCommand::Init();
        Renderer2D::Init();
    }

    void Renderer::Shutdown()
    {
        KLD_PROFILE_FUNCTION();
        Renderer2D::Shutdown();
    }

    void Renderer::OnWindowResize(uint32_t width, uint32_t height)
    {
        RenderCommand::SetViewPort(0, 0, width, height);
    }

    void Renderer::BeginScene(OrthographicCamera &camera)
    {
        s_SceneData->ViewProjectionMatrix = camera.GetViewProjectionMatrix();
    }

    void Renderer::EndScene()
    {
    }

    void Renderer::Submit(const Ref<Shader> &shader, const Ref<VertexArray> &vertexArray, const glm::mat4 &transform)
    {
        shader->Bind();
        shader->SetMat4("u_ViewProjection", s_SceneData->ViewProjectionMatrix); // 通常来说View和Projection矩阵不会频繁的变化
        shader->SetMat4("u_Transform", transform);                              // 而Model矩阵则是变化最为频繁的

        vertexArray->Bind();
        RenderCommand::DrawIndexed(vertexArray);
    }
} // namespace Kaleidoscope
