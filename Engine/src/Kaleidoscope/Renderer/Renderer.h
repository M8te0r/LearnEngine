#pragma once
#include "Kaleidoscope/Renderer/RenderCommand.h"
#include "Kaleidoscope/Renderer/OrthographicCamera.h"
#include "Kaleidoscope/Renderer/Shader.h"

namespace Kaleidoscope
{
    class Renderer
    {
    public:
        static void BeginScene(OrthographicCamera &camera);
        static void EndScene();

        static void Submit(const std::shared_ptr<Shader> &shader, const std::shared_ptr<VertexArray> &vertexArray);

        inline static RendererAPI::API GetAPI() { return RendererAPI::GetAPI(); }

    private:
        struct SceneData
        {
            glm::mat4 ViewProjectionMatrix;
        };
        static SceneData *m_SceneData;
    };

} // namespace Kaleidoscope
