#include "kldpch.h"
#include "Kaleidoscope/Renderer/Buffer.h"

#include "Kaleidoscope/Renderer/Renderer.h"
#include "Platform/OpenGL/OpenGLBuffer.h"

namespace Kaleidoscope
{
    VertexBuffer *VertexBuffer::Create(float *vertices, uint32_t size)
    {

        switch (Renderer::GetAPI())
        {
        case RendererAPI::None:
            KLD_CORE_ASSERT(false, "RendererAPI::None currently is not supported!");
            return nullptr;

        case RendererAPI::OpenGL:
            
            return new OpenGLVertexBuffer(vertices, size);
        }
        KLD_CORE_ASSERT(false, "Unknown renderer API!");
        return nullptr;
    }

    IndexBuffer *IndexBuffer::Create(uint32_t *indices, uint32_t size)
    {
        switch (Renderer::GetAPI())
        {
        case RendererAPI::None:
            KLD_CORE_ASSERT(false, "RendererAPI::None currently is not supported!");
            return nullptr;

        case RendererAPI::OpenGL:
            return new OpenGLIndexBuffer(indices, size);
        }
        KLD_CORE_ASSERT(false, "Unknown renderer API!");
        return nullptr;
    }

} // namespace Kaleidoscope
