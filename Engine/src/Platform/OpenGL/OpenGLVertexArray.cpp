#include "kldpch.h"
#include "Platform/OpenGL/OpenGLVertexArray.h"

#include "glad/glad.h"

namespace Kaleidoscope
{
    static GLenum ShaderDataTypeToOpenGLBaseType(ShaderDataType type)
    {
        switch (type)
        {
        case ShaderDataType::Float:
            return GL_FLOAT;
        case ShaderDataType::Float2:
            return GL_FLOAT;
        case ShaderDataType::Float3:
            return GL_FLOAT;
        case ShaderDataType::Float4:
            return GL_FLOAT;
        case ShaderDataType::Mat3:
            return GL_FLOAT;
        case ShaderDataType::Mat4:
            return GL_FLOAT;
        case ShaderDataType::Int:
            return GL_INT;
        case ShaderDataType::Int2:
            return GL_INT;
        case ShaderDataType::Int3:
            return GL_INT;
        case ShaderDataType::Int4:
            return GL_INT;
        case ShaderDataType::Bool:
            return GL_BOOL;
        }

        KLD_CORE_ASSERT(false, "Unknown ShaderDataType!");

        return 0;
    }

    OpenGLVertexArray::OpenGLVertexArray()
    {
        KLD_PROFILE_FUNCTION();

        glGenVertexArrays(1, &m_RendererID);
    }

    OpenGLVertexArray::~OpenGLVertexArray()
    {
        KLD_PROFILE_FUNCTION();

        glDeleteVertexArrays(1, &m_RendererID);
    }

    void OpenGLVertexArray::Bind() const
    {
        KLD_PROFILE_FUNCTION();

        glBindVertexArray(m_RendererID);
    }

    void OpenGLVertexArray::UnBind() const
    {
        KLD_PROFILE_FUNCTION();

        glBindVertexArray(0);
    }

    void OpenGLVertexArray::AddVertexBuffer(const Ref<VertexBuffer> &vertexBuffer)
    {
        KLD_PROFILE_FUNCTION();

        // 设置好了buffer的layout（即bufferData）后，才能将其添加至vertexArray中
        KLD_CORE_ASSERT(vertexBuffer->GetLayout().GetElements().size(), "Vertex Buffer has no layout!");

        glBindVertexArray(m_RendererID);
        vertexBuffer->Bind();

        uint32_t index = 0;
        const auto &layout = vertexBuffer->GetLayout();
        for (const auto &element : layout)
        {
            // 告诉GPU数据内的信息是如何布局的
            glEnableVertexAttribArray(index); // 数据中的信息0
            glVertexAttribPointer(index,
                                  element.GetComponentCount(),
                                  ShaderDataTypeToOpenGLBaseType(element.Type),
                                  element.Normalized ? GL_TRUE : GL_FALSE,
                                  layout.GetStride(),
                                  (const void *)element.Offset); // 在下标0处，有3个浮点数，不启用归一化，步长为3*float，没有偏移
            index++;
        }
        m_VertexBuffers.push_back(vertexBuffer);
    }

    void OpenGLVertexArray::SetIndexBuffer(const Ref<IndexBuffer> &indexBuffer)
    {
        KLD_PROFILE_FUNCTION();

        glBindVertexArray(m_RendererID);
        indexBuffer->Bind();

        m_IndexBuffer = indexBuffer;
    }

} // namespace Kaleidoscope
