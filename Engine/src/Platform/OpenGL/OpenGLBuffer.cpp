#include "kldpch.h"
#include "Platform/OpenGL/OpenGLBuffer.h"

#include "glad/glad.h"

namespace Kaleidoscope
{
    //= = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =
    // VertexBuffer
    //= = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =
    OpenGLVertexBuffer::OpenGLVertexBuffer(float *vertices, uint32_t size)
    {
        KLD_PROFILE_FUNCTION();

        // FIXME glCreateBuffers(1, &m_RendererID); OpenGL 4.5以上才支持
        glGenBuffers(1, &m_RendererID);
        glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
        glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
    }

    OpenGLVertexBuffer::~OpenGLVertexBuffer()
    {
        KLD_PROFILE_FUNCTION();

        glDeleteBuffers(1, &m_RendererID);
    }

    void OpenGLVertexBuffer::Bind() const
    {
        KLD_PROFILE_FUNCTION();

        glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
    }

    void OpenGLVertexBuffer::UnBind() const
    {
        KLD_PROFILE_FUNCTION();

        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }

    //= = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =
    // IndexBuffer
    //= = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =

    OpenGLIndexBuffer::OpenGLIndexBuffer(uint32_t *indices, uint32_t count) : m_Count(count)
    {
        KLD_PROFILE_FUNCTION();

        // FIXME glCreateBuffers(1, &m_RendererID);OpenGL 4.5以上才支持
        glGenBuffers(1, &m_RendererID);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(uint32_t), indices, GL_STATIC_DRAW);
    }

    OpenGLIndexBuffer::~OpenGLIndexBuffer()
    {
        KLD_PROFILE_FUNCTION();

        glDeleteBuffers(1, &m_RendererID);
    }

    void OpenGLIndexBuffer::Bind() const
    {
        KLD_PROFILE_FUNCTION();

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID);
    }

    void OpenGLIndexBuffer::UnBind() const
    {
        KLD_PROFILE_FUNCTION();

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    }
} // namespace Kaleidoscope
