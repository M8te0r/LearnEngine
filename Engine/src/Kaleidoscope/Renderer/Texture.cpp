#include "kldpch.h"
#include "Kaleidoscope/Renderer/Texture.h"

#include "Kaleidoscope/Renderer/Renderer.h"
#include "Platform/OpenGL/OpenGLTexture.h"

namespace Kaleidoscope
{
    Ref<Texture2D> Texture2D::Create(const std::string &path)
    {
        switch (Renderer::GetAPI())
        {
        case RendererAPI::API::None:
            KLD_CORE_ASSERT(false, "RendererAPI::None currently is not supported!");
            return nullptr;

        case RendererAPI::API::OpenGL:

            return std::make_shared<OpenGLTexture2D>(path);
        }
        KLD_CORE_ASSERT(false, "Unknown renderer API!");
        return nullptr;
    }

} // namespace Kaleidoscope
