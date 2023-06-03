#pragma once
#include "Kaleidoscope/Renderer/OrthographicCamera.h"
#include "Kaleidoscope//Renderer/Texture.h"
#include "Kaleidoscope//Renderer/SubTexture2D.h"

namespace Kaleidoscope
{
    class Renderer2D
    {

    public:
        static void Init();
        static void Shutdown();

        static void BeginScene(const OrthographicCamera &camera);
        static void EndScene();
        static void Flush();

        // Primitives
        static void DrawQuad(const glm::vec2 &position, const glm::vec2 &size, const glm::vec4 &color);
        static void DrawQuad(const glm::vec3 &position, const glm::vec2 &size, const glm::vec4 &color);
        static void DrawQuad(const glm::vec2 &position, const glm::vec2 &size, const Ref<Texture2D> &texture, float tilingFactor = 1.0f, const glm::vec4 &tintColor = glm::vec4(1.0f));
        static void DrawQuad(const glm::vec3 &position, const glm::vec2 &size, const Ref<Texture2D> &texture, float tilingFactor = 1.0f, const glm::vec4 &tintColor = glm::vec4(1.0f));
        static void DrawQuad(const glm::vec2 &position, const glm::vec2 &size, const Ref<SubTexture2D> &subtexture, float tilingFactor = 1.0f, const glm::vec4 &tintColor = glm::vec4(1.0f));
        static void DrawQuad(const glm::vec3 &position, const glm::vec2 &size, const Ref<SubTexture2D> &subtexture, float tilingFactor = 1.0f, const glm::vec4 &tintColor = glm::vec4(1.0f));

        // Rotation is in radians
        static void DrawRotateQuad(const glm::vec2 &position, const glm::vec2 &size, float rotation, const glm::vec4 &color);
        static void DrawRotateQuad(const glm::vec3 &position, const glm::vec2 &size, float rotation, const glm::vec4 &color);
        static void DrawRotateQuad(const glm::vec2 &position, const glm::vec2 &size, float rotation, const Ref<Texture2D> &texture, float tilingFactor = 1.0f, const glm::vec4 &tintColor = glm::vec4(1.0f));
        static void DrawRotateQuad(const glm::vec3 &position, const glm::vec2 &size, float rotation, const Ref<Texture2D> &texture, float tilingFactor = 1.0f, const glm::vec4 &tintColor = glm::vec4(1.0f));
        static void DrawRotateQuad(const glm::vec2 &position, const glm::vec2 &size, float rotation, const Ref<SubTexture2D> &subtexture, float tilingFactor = 1.0f, const glm::vec4 &tintColor = glm::vec4(1.0f));
        static void DrawRotateQuad(const glm::vec3 &position, const glm::vec2 &size, float rotation, const Ref<SubTexture2D> &subtexture, float tilingFactor = 1.0f, const glm::vec4 &tintColor = glm::vec4(1.0f));

        // Stats
        struct Statistics
        {
            uint32_t DrawCalls = 0;
            uint32_t QuadCount = 0;

            uint32_t GetTotalVertexCount() { return QuadCount * 4; }
            uint32_t GetTotalIndexCount() { return QuadCount * 6; }
        };

        static void ResetStats();
        static Statistics GetStats();

    private:
        static void FlushAndReset();
    };

} // namespace Kaleidoscope
