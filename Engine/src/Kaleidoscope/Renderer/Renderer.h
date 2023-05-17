#pragma once
#include "Kaleidoscope/Renderer/RenderCommand.h"

namespace Kaleidoscope
{
    class Renderer
    {
    public:
        static void BeginScene();
        static void EndScene();

        static void Submit(const std::shared_ptr<VertexArray> &vertexArray);

        inline static RendererAPI::API GetAPI() { return RendererAPI::GetAPI(); }
    };

} // namespace Kaleidoscope
