#include "kldpch.h"
#include "Kaleidoscope/Renderer/Renderer2D.h"

#include "Kaleidoscope/Renderer/VertexArray.h"
#include "Kaleidoscope/Renderer/Shader.h"
#include "Kaleidoscope/Renderer/RenderCommand.h"

#include "glm/gtc/matrix_transform.hpp"

namespace Kaleidoscope
{
    struct Renderer2DStorage
    {
        Ref<VertexArray> QuadVertexArray;
        Ref<Shader> TextureShader;
        Ref<Texture2D> WhiteTexture;
    };

    static Renderer2DStorage *s_Data;

    void Renderer2D::Init()
    {
        s_Data = new Renderer2DStorage();
        // 渲染正方形
        s_Data->QuadVertexArray = VertexArray::Create();

        float squareVertices[5 * 4] = {
            -0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
            0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
            0.5f, 0.5f, 0.0f, 1.0f, 1.0f,
            -0.5f, 0.5f, 0.0f, 0.0f, 1.0f};
        Ref<VertexBuffer> squareVB;
        squareVB.reset(VertexBuffer::Create(squareVertices, sizeof(squareVertices)));
        squareVB->SetLayout({{ShaderDataType::Float3, "a_Position"},
                             {ShaderDataType::Float2, "a_TexCoord"}});
        s_Data->QuadVertexArray->AddVertexBuffer(squareVB);

        // 创建、绑定indexBuffer(同时将其添加至VertexArray中)
        uint32_t squareIndices[6] = {0, 1, 2, 2, 3, 0};
        Ref<IndexBuffer> squareIB;
        squareIB.reset(IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t)));
        s_Data->QuadVertexArray->SetIndexBuffer(squareIB);
        // m_SquareVA->SetIndexBuffer(m_IndexBuffer);

        // 创建一个空数据纹理
        s_Data->WhiteTexture = Texture2D::Create(1, 1);
        uint32_t whiteTextureData = 0xffffffff;                             // RGBA颜色数据(32位)，纯白色
        s_Data->WhiteTexture->SetData(&whiteTextureData, sizeof(uint32_t)); // 为这个空数据纹理设置颜色数据

        // 根据图片生成纹理
        s_Data->TextureShader = Shader::Create("../Sandbox/assets/shaders/Texture.glsl");
        s_Data->TextureShader->Bind();
        s_Data->TextureShader->SetInt("u_Texture", 0);
    }

    void Renderer2D::Shutdown()
    {
        delete s_Data;
    }

    void Renderer2D::BeginScene(const OrthographicCamera &camera)
    {
        s_Data->TextureShader->Bind();
        s_Data->TextureShader->SetMat4("u_ViewProjection", camera.GetViewProjectionMatrix());
    }

    void Renderer2D::EndScene()
    {
    }

    void Renderer2D::DrawQuad(const glm::vec2 &position, const glm::vec2 &size, const glm::vec4 &color)
    {
        DrawQuad({position.x, position.y, 0.0f}, size, color);
    }

    void Renderer2D::DrawQuad(const glm::vec3 &position, const glm::vec2 &size, const glm::vec4 &color)
    {
        /*
            DrawQuad()根据传入参数的不同，动态的改变Fragment Shader的参数
            当传入的第三个参数为color时，shader接收这个color数据，使用默认的white texture，从而使最终颜色为color
            当传入的第三个参数为texture时，shader接收这个texture数据，使u_color=vec4(1.0)1，从而使最终颜色为texture
        */

        // 使用color，则默认的u_Texture设置为(1,1,1,1)纯白，从而使fragment shader输出color的颜色
        s_Data->TextureShader->SetFloat4("u_Color", color); // 绑定color
        s_Data->WhiteTexture->Bind();                       // 绑定纯白texture

        glm::mat4 transform = glm::translate(glm::mat4(1.0f), position) * glm::scale(glm::mat4(1.0f), {size.x, size.y, 1.0f});
        s_Data->TextureShader->SetMat4("u_Transform", transform);

        s_Data->QuadVertexArray->Bind();
        RenderCommand::DrawIndexed(s_Data->QuadVertexArray);
    }

    void Renderer2D::DrawQuad(const glm::vec2 &position, const glm::vec2 &size, const Ref<Texture2D> &texture)
    {
        DrawQuad({position.x, position.y, 0.0f}, size, texture);
    }

    void Renderer2D::DrawQuad(const glm::vec3 &position, const glm::vec2 &size, const Ref<Texture2D> &texture)
    {
        // 使用texture，则默认的u_Color设置为(1,1,1,1)纯白，从而使fragment shader输出texture的颜色
        s_Data->TextureShader->SetFloat4("u_Color", glm::vec4(1.0f)); // 绑定纯白color
        texture->Bind();                                              // 绑定shader

        glm::mat4 transform = glm::translate(glm::mat4(1.0f), position) * glm::scale(glm::mat4(1.0f), {size.x, size.y, 1.0f});
        s_Data->TextureShader->SetMat4("u_Transform", transform);

        s_Data->QuadVertexArray->Bind();
        RenderCommand::DrawIndexed(s_Data->QuadVertexArray);
    }

} // namespace Kaleidoscope
