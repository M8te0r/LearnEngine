#include "kldpch.h"
#include "Kaleidoscope/Renderer/Shader.h"

#include "Kaleidoscope/Renderer/Renderer.h"
#include "Platform/OpenGL/OpenGLShader.h"

namespace Kaleidoscope
{
    Shader *Shader::Create(const std::string &vertexSrc, const std::string &fragmentSrc)
    {
        switch (Renderer::GetAPI())
        {
        case RendererAPI::API::None:
            KLD_CORE_ASSERT(false, "RendererAPI::None currently is not supported!");
            return nullptr;

        case RendererAPI::API::OpenGL:

            return new OpenGLShader(vertexSrc, fragmentSrc);
        }
        KLD_CORE_ASSERT(false, "Unknown renderer API!");
        return nullptr;
    }

} // namespace Kaleidoscope
