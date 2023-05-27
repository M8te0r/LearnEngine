#include "kldpch.h"
#include "Kaleidoscope/Renderer/GraphicsContext.h"

#include "Kaleidoscope/Renderer/Renderer.h"
#include "Platform/OpenGL/OpenGLContext.h"

namespace Kaleidoscope
{
    Scope<GraphicsContext> GraphicsContext::Create(void *window)
    {
        switch (Renderer::GetAPI())
        {
        case RendererAPI::API::None:
            KLD_CORE_ASSERT(false, "RendererAPI::None is currently not supported!");
            return nullptr;
        case RendererAPI::API::OpenGL:
            return CreateScope<OpenGLContext>(static_cast<GLFWwindow *>(window));
        }

        KLD_CORE_ASSERT(false, "Unknown RendererAPI!");
        return nullptr;
    }

} // namespace Kaleidoscope
