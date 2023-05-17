#include "kldpch.h"
#include "Kaleidoscope/Renderer/VertexArray.h"

#include "Kaleidoscope/Renderer/Renderer.h"
#include "Platform/OpenGL/OpenGLVertexArray.h"

namespace Kaleidoscope
{
    VertexArray *VertexArray::Create()
    {
        switch (Renderer::GetAPI())
        {
        case RendererAPI::API::None:
            KLD_CORE_ASSERT(false, "RendererAPI::None currently is not supported!");
            return nullptr;

        case RendererAPI::API::OpenGL:

            return new OpenGLVertexArray();
        }
        KLD_CORE_ASSERT(false, "Unknown renderer API!");
        return nullptr;
    }

} // namespace Kaleidoscope
