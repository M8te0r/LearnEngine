#include "kldpch.h"
#include "Kaleidoscope/Renderer/Renderer.h"

namespace Kaleidoscope
{
    Renderer::SceneData *Renderer::m_SceneData = new Renderer::SceneData;
    void Renderer::BeginScene(OrthographicCamera &camera)
    {
        m_SceneData->ViewProjectionMatrix = camera.GetViewProjectionMatrix();
    }

    void Renderer::EndScene()
    {
    }

    void Renderer::Submit(const std::shared_ptr<Shader> &shader, const std::shared_ptr<VertexArray> &vertexArray, const glm::mat4 &transform)
    {
        shader->Bind();
        shader->UploadUniformMat4("u_ViewProjection", m_SceneData->ViewProjectionMatrix); // 通常来说View和Projection矩阵不会频繁的变化
        shader->UploadUniformMat4("u_Transform", transform);                              // 而Model矩阵则是变化最为频繁的
        vertexArray->Bind();
        RenderCommand::DrawIndexed(vertexArray);
    }
} // namespace Kaleidoscope
