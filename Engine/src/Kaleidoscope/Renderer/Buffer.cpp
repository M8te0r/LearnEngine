#include "kldpch.h"
#include "Kaleidoscope/Renderer/Buffer.h"

#include "Kaleidoscope/Renderer/Renderer.h"
#include "Platform/OpenGL/OpenGLBuffer.h"

namespace Kaleidoscope
{
    Ref<VertexBuffer> VertexBuffer::Create(uint32_t size)
    {
        switch (Renderer::GetAPI())
        {
        case RendererAPI::API::None:
            KLD_CORE_ASSERT(false, "RendererAPI::None currently is not supported!");
            return nullptr;

        case RendererAPI::API::OpenGL:

            return CreateRef<OpenGLVertexBuffer>( size);
        }
        KLD_CORE_ASSERT(false, "Unknown renderer API!");
        return nullptr;
    }

    Ref<VertexBuffer> VertexBuffer::Create(float *vertices, uint32_t size)
    {

        switch (Renderer::GetAPI())
        {
        case RendererAPI::API::None:
            KLD_CORE_ASSERT(false, "RendererAPI::None currently is not supported!");
            return nullptr;

        case RendererAPI::API::OpenGL:

            return CreateRef<OpenGLVertexBuffer>(vertices, size);
        }
        KLD_CORE_ASSERT(false, "Unknown renderer API!");
        return nullptr;
    }

    Ref<IndexBuffer> IndexBuffer::Create(uint32_t *indices, uint32_t count)
    {
        switch (Renderer::GetAPI())
        {
        case RendererAPI::API::None:
            KLD_CORE_ASSERT(false, "RendererAPI::None currently is not supported!");
            return nullptr;

        case RendererAPI::API::OpenGL:
            return CreateRef<OpenGLIndexBuffer>(indices, count);
        }
        KLD_CORE_ASSERT(false, "Unknown renderer API!");
        return nullptr;
    }

} // namespace Kaleidoscope
