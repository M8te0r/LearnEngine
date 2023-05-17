#include "kldpch.h"
#include "Kaleidoscope/Renderer/Renderer.h"

namespace Kaleidoscope
{
    void Renderer::BeginScene()
    {
    }

    void Renderer::EndScene()
    {
    }

    void Renderer::Submit(const std::shared_ptr<VertexArray> &vertexArray)
    {
        vertexArray->Bind();
        RenderCommand::DrawIndexed(vertexArray);
    }
} // namespace Kaleidoscope
