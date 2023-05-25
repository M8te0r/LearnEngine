#include "kldpch.h"
#include "Kaleidoscope/Renderer/Texture.h"

#include "Kaleidoscope/Renderer/Renderer.h"
#include "Platform/OpenGL/OpenGLTexture.h"

namespace Kaleidoscope
{
    Ref<Texture2D> Texture2D::Create(uint32_t width, uint32_t height)
    {
        switch (Renderer::GetAPI())
        {
        case RendererAPI::API::None:
            KLD_CORE_ASSERT(false, "RendererAPI::None currently is not supported!");
            return nullptr;

        case RendererAPI::API::OpenGL:

            return CreateRef<OpenGLTexture2D>(width, height);
        }
        KLD_CORE_ASSERT(false, "Unknown renderer API!");
        return nullptr;
    }
    
    Ref<Texture2D> Texture2D::Create(const std::string &path)
    {
        switch (Renderer::GetAPI())
        {
        case RendererAPI::API::None:
            KLD_CORE_ASSERT(false, "RendererAPI::None currently is not supported!");
            return nullptr;

        case RendererAPI::API::OpenGL:

            return CreateRef<OpenGLTexture2D>(path);
        }
        KLD_CORE_ASSERT(false, "Unknown renderer API!");
        return nullptr;
    }

    

} // namespace Kaleidoscope
