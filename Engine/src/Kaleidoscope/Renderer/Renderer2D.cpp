#include "kldpch.h"
#include "Kaleidoscope/Renderer/Renderer2D.h"

#include "Kaleidoscope/Renderer/VertexArray.h"
#include "Kaleidoscope/Renderer/Shader.h"
#include "Kaleidoscope/Renderer/RenderCommand.h"

#include "glm/gtc/matrix_transform.hpp"

namespace Kaleidoscope
{
    struct QuadVertex
    {
        glm::vec3 Position;
        glm::vec4 Color;
        glm::vec2 TexCoord;
        float TexIndex;
        float TilingFactor;
    };

    struct Renderer2DData
    {
        static const uint32_t MaxQuads = 20000;
        static const uint32_t MaxVertices = MaxQuads * 4;
        static const uint32_t MaxIndices = MaxQuads * 6;

        static const uint32_t MaxTextureSlots = 16; // TODO: Apple only support 16 unit

        Ref<VertexArray> QuadVertexArray;
        Ref<VertexBuffer> QuadVertexBuffer;
        Ref<Shader> TextureShader;
        Ref<Texture2D> WhiteTexture;

        uint32_t QuadIndexCount = 0;
        QuadVertex *QuadVertexBufferBase = nullptr;
        QuadVertex *QuadVertexBufferPtr = nullptr;

        std::array<Ref<Texture2D>, MaxTextureSlots> TextureSlots;
        uint32_t TextureSlotIndex = 1; // 下标为0时，启用的是white texture

        glm::vec4 QuadVertexPositions[4];

        Renderer2D::Statistics Stats;
    };

    static Renderer2DData s_Data;

    void Renderer2D::Init()
    {
        KLD_PROFILE_FUNCTION();

        // 渲染正方形
        s_Data.QuadVertexArray = VertexArray::Create();

        s_Data.QuadVertexBuffer = VertexBuffer::Create(s_Data.MaxVertices * sizeof(QuadVertex));
        s_Data.QuadVertexBuffer->SetLayout({{ShaderDataType::Float3, "a_Position"},
                                            {ShaderDataType::Float4, "a_Color"},
                                            {ShaderDataType::Float2, "a_TexCoord"},
                                            {ShaderDataType::Float, "a_TexIndex"},
                                            {ShaderDataType::Float, "a_TilingFactor"}});
        s_Data.QuadVertexArray->AddVertexBuffer(s_Data.QuadVertexBuffer);

        s_Data.QuadVertexBufferBase = new QuadVertex[s_Data.MaxVertices];

        // 创建、绑定indexBuffer(同时将其添加至VertexArray中)
        uint32_t *quadIndices = new uint32_t[s_Data.MaxIndices]; // 数量多，所以在堆上分配内存比较合适

        uint32_t offset = 0;
        for (uint32_t i = 0; i < s_Data.MaxIndices; i += 6)
        {
            quadIndices[i + 0] = offset + 0;
            quadIndices[i + 1] = offset + 1;
            quadIndices[i + 2] = offset + 2;

            quadIndices[i + 3] = offset + 2;
            quadIndices[i + 4] = offset + 3;
            quadIndices[i + 5] = offset + 0;

            offset += 4;
        }

        Ref<IndexBuffer> quadIB = IndexBuffer::Create(quadIndices, s_Data.MaxIndices);
        s_Data.QuadVertexArray->SetIndexBuffer(quadIB);
        delete[] quadIndices;
        // m_SquareVA->SetIndexBuffer(m_IndexBuffer);

        // 创建一个空数据纹理
        s_Data.WhiteTexture = Texture2D::Create(1, 1);
        uint32_t whiteTextureData = 0xffffffff;                            // RGBA颜色数据(32位)，纯白色
        s_Data.WhiteTexture->SetData(&whiteTextureData, sizeof(uint32_t)); // 为这个空数据纹理设置颜色数据

        int32_t samplers[s_Data.MaxTextureSlots];
        for (uint32_t i = 0; i < s_Data.MaxTextureSlots; i++)
        {
            samplers[i] = i;
        }

        // 根据图片生成纹理
        s_Data.TextureShader = Shader::Create("../Sandbox/assets/shaders/Texture.glsl");
        s_Data.TextureShader->Bind();
        s_Data.TextureShader->SetIntArray("u_Textures", samplers, s_Data.MaxTextureSlots);

        // 将某一块内存中的内容全部设置0

        s_Data.TextureSlots[0] = s_Data.WhiteTexture;

        s_Data.QuadVertexPositions[0] = {-0.5f, -0.5f, 0.0f, 1.0f};
        s_Data.QuadVertexPositions[1] = {0.5f, -0.5f, 0.0f, 1.0f};
        s_Data.QuadVertexPositions[2] = {0.5f, 0.5f, 0.0f, 1.0f};
        s_Data.QuadVertexPositions[3] = {-0.5f, 0.5f, 0.0f, 1.0f};
    }

    void Renderer2D::Shutdown()
    {
        KLD_PROFILE_FUNCTION();
    }

    void Renderer2D::BeginScene(const OrthographicCamera &camera)
    {
        KLD_PROFILE_FUNCTION();

        s_Data.TextureShader->Bind();
        s_Data.TextureShader->SetMat4("u_ViewProjection", camera.GetViewProjectionMatrix());

        s_Data.QuadIndexCount = 0;
        s_Data.QuadVertexBufferPtr = s_Data.QuadVertexBufferBase;

        s_Data.TextureSlotIndex = 1;
    }

    void Renderer2D::EndScene()
    {
        KLD_PROFILE_FUNCTION();

        uint32_t dataSize = (uint8_t *)s_Data.QuadVertexBufferPtr - (uint8_t *)s_Data.QuadVertexBufferBase;
        s_Data.QuadVertexBuffer->SetData(s_Data.QuadVertexBufferBase, dataSize);

        Flush();
    }

    void Renderer2D::Flush()
    {
        // 绑定纹理
        for (uint32_t i = 0; i < s_Data.TextureSlotIndex; i++)
        {
            s_Data.TextureSlots[i]->Bind(i);
        }

        RenderCommand::DrawIndexed(s_Data.QuadVertexArray, s_Data.QuadIndexCount);

        s_Data.Stats.DrawCalls++;
    }

    void Renderer2D::FlushAndReset()
    {

        EndScene();
        s_Data.QuadIndexCount = 0;
        s_Data.QuadVertexBufferPtr = s_Data.QuadVertexBufferBase;

        s_Data.TextureSlotIndex = 1;
    }

    void Renderer2D::DrawQuad(const glm::vec2 &position, const glm::vec2 &size, const glm::vec4 &color)
    {
        DrawQuad({position.x, position.y, 0.0f}, size, color);
    }

    void Renderer2D::DrawQuad(const glm::vec3 &position, const glm::vec2 &size, const glm::vec4 &color)
    {
        KLD_PROFILE_FUNCTION();

        constexpr size_t quadVertexCount = 4;
        const float textureIndex = 0.0f; // white texture
        constexpr glm::vec2 textureCoords[] = {{0.0f, 0.0f}, {1.0f, 0.0f}, {1.0f, 1.0f}, {0.0f, 1.0f}};
        const float tilingFactor = 1.0f;

        if (s_Data.QuadIndexCount >= Renderer2DData::MaxIndices)
        {
            FlushAndReset();
        }

        glm::mat4 transform = glm::translate(glm::mat4(1.0f), position) * glm::scale(glm::mat4(1.0f), {size.x, size.y, 1.0f});

        for (size_t i = 0; i < quadVertexCount; i++)
        {
            s_Data.QuadVertexBufferPtr->Position = transform * s_Data.QuadVertexPositions[i];
            s_Data.QuadVertexBufferPtr->Color = color;
            s_Data.QuadVertexBufferPtr->TexCoord = textureCoords[i];
            s_Data.QuadVertexBufferPtr->TexIndex = textureIndex;
            s_Data.QuadVertexBufferPtr->TilingFactor = tilingFactor;
            s_Data.QuadVertexBufferPtr++;
        }

        s_Data.QuadIndexCount += 6;

        s_Data.Stats.QuadCount++;
    }

    void Renderer2D::DrawQuad(const glm::vec2 &position, const glm::vec2 &size, const Ref<Texture2D> &texture, float tilingFactor, const glm::vec4 &tintColor)
    {
        DrawQuad({position.x, position.y, 0.0f}, size, texture, tilingFactor, tintColor);
    }

    void Renderer2D::DrawQuad(const glm::vec3 &position, const glm::vec2 &size, const Ref<Texture2D> &texture, float tilingFactor, const glm::vec4 &tintColor)
    {
        KLD_PROFILE_FUNCTION();

        constexpr float x = 7, y = 6;                                // 表示texture sheet上，从左边往右数第7个、从下往上数第6个texture（每个大小是128*128）
        constexpr float sheetWidth = 2560.0f, sheetHeight = 1664.0f; // texture sheet的实际长宽
        constexpr float spriteWidth = 128.0f, spriteHeight = 128.0f; // texture sheet上每个texture的大小

        constexpr size_t quadVertexCount = 4;
        constexpr glm::vec4 color = {1.0f, 1.0f, 1.0f, 1.0f};
        // 将texture sheet中的某一个区域重现映射到[0,1]区间内
        constexpr glm::vec2 textureCoords[] = {
            {(x * spriteWidth) / sheetWidth, (y * spriteHeight) / sheetHeight},
            {((x + 1) * spriteWidth) / sheetWidth, (y * spriteHeight) / sheetHeight},
            {((x + 1) * spriteWidth) / sheetWidth, ((y + 1) * spriteHeight) / sheetHeight},
            {(x * spriteWidth) / sheetWidth, ((y + 1) * spriteHeight) / sheetHeight}};

        if (s_Data.QuadIndexCount >= Renderer2DData::MaxIndices)
        {
            FlushAndReset();
        }

        float textureIndex = 0.0f;

        // 检查是否所有texture都提交至textureSlots中
        for (uint32_t i = 1; i < s_Data.TextureSlotIndex; i++)
        {
            // 遍历所有的slot，比较当前slot中texture的指针是否与参数指针相同
            if (*s_Data.TextureSlots[i].get() == *texture.get())
            {
                textureIndex = (float)i;
                break;
            }
        }

        if (textureIndex == 0.0f)
        {
            textureIndex = (float)s_Data.TextureSlotIndex;
            s_Data.TextureSlots[s_Data.TextureSlotIndex] = texture;
            s_Data.TextureSlotIndex++;
        }

        glm::mat4 transform = glm::translate(glm::mat4(1.0f), position) * glm::scale(glm::mat4(1.0f), {size.x, size.y, 1.0f});

        for (size_t i = 0; i < quadVertexCount; i++)
        {
            s_Data.QuadVertexBufferPtr->Position = transform * s_Data.QuadVertexPositions[i];
            s_Data.QuadVertexBufferPtr->Color = color;
            s_Data.QuadVertexBufferPtr->TexCoord = textureCoords[i];
            s_Data.QuadVertexBufferPtr->TexIndex = textureIndex;
            s_Data.QuadVertexBufferPtr->TilingFactor = tilingFactor;
            s_Data.QuadVertexBufferPtr++;
        }

        s_Data.QuadIndexCount += 6;

        s_Data.Stats.QuadCount++;
    }

    void Renderer2D::DrawRotateQuad(const glm::vec2 &position, const glm::vec2 &size, float rotation, const glm::vec4 &color)
    {
        DrawRotateQuad({position.x, position.y, 0.0f}, size, rotation, color);
    }

    void Renderer2D::DrawRotateQuad(const glm::vec3 &position, const glm::vec2 &size, float rotation, const glm::vec4 &color)
    {
        KLD_PROFILE_FUNCTION();

        constexpr size_t quadVertexCount = 4;
        const float textureIndex = 0.0f; // white texture
        constexpr glm::vec2 textureCoords[] = {{0.0f, 0.0f}, {1.0f, 0.0f}, {1.0f, 1.0f}, {0.0f, 1.0f}};
        const float tilingFactor = 1.0f;

        if (s_Data.QuadIndexCount >= Renderer2DData::MaxIndices)
        {
            FlushAndReset();
        }

        /*
            DrawQuad()根据传入参数的不同，动态的改变Fragment Shader的参数
            当传入的第三个参数为color时，shader接收这个color数据，使用默认的white texture，从而使最终颜色为color
            当传入的第三个参数为texture时，shader接收这个texture数据，使u_color=vec4(1.0)1，从而使最终颜色为texture
        */

        glm::mat4 transform = glm::translate(glm::mat4(1.0f), position) * glm::rotate(glm::mat4(1.0f), rotation, {0.0f, 0.0f, 1.0f}) * glm::scale(glm::mat4(1.0f), {size.x, size.y, 1.0f});

        for (size_t i = 0; i < quadVertexCount; i++)
        {
            s_Data.QuadVertexBufferPtr->Position = transform * s_Data.QuadVertexPositions[i];
            s_Data.QuadVertexBufferPtr->Color = color;
            s_Data.QuadVertexBufferPtr->TexCoord = textureCoords[i];
            s_Data.QuadVertexBufferPtr->TexIndex = textureIndex;
            s_Data.QuadVertexBufferPtr->TilingFactor = tilingFactor;
            s_Data.QuadVertexBufferPtr++;
        }

        s_Data.QuadIndexCount += 6;

        s_Data.Stats.QuadCount++;
    }

    void Renderer2D::DrawRotateQuad(const glm::vec2 &position, const glm::vec2 &size, float rotation, const Ref<Texture2D> &texture, float tilingFactor, const glm::vec4 &tintColor)
    {
        DrawRotateQuad({position.x, position.y, 0.0f}, size, rotation, texture, tilingFactor, tintColor);
    }

    void Renderer2D::DrawRotateQuad(const glm::vec3 &position, const glm::vec2 &size, float rotation, const Ref<Texture2D> &texture, float tilingFactor, const glm::vec4 &tintColor)
    {
        KLD_PROFILE_FUNCTION();

        constexpr size_t quadVertexCount = 4;
        constexpr glm::vec4 color = {1.0f, 1.0f, 1.0f, 1.0f};
        constexpr glm::vec2 textureCoords[] = {{0.0f, 0.0f}, {1.0f, 0.0f}, {1.0f, 1.0f}, {0.0f, 1.0f}};

        if (s_Data.QuadIndexCount >= Renderer2DData::MaxIndices)
        {
            FlushAndReset();
        }

        float textureIndex = 0.0f;

        // 检查是否所有texture都提交至textureSlots中
        for (uint32_t i = 1; i < s_Data.TextureSlotIndex; i++)
        {
            // 遍历所有的slot，比较当前slot中texture的指针是否与参数指针相同
            if (*s_Data.TextureSlots[i].get() == *texture.get())
            {
                textureIndex = (float)i;
                break;
            }
        }

        if (textureIndex == 0.0f)
        {
            textureIndex = (float)s_Data.TextureSlotIndex;
            s_Data.TextureSlots[s_Data.TextureSlotIndex] = texture;
            s_Data.TextureSlotIndex++;
        }

        glm::mat4 transform = glm::translate(glm::mat4(1.0f), position) * glm::rotate(glm::mat4(1.0f), rotation, {0.0f, 0.0f, 1.0f}) * glm::scale(glm::mat4(1.0f), {size.x, size.y, 1.0f});

        for (size_t i = 0; i < quadVertexCount; i++)
        {
            s_Data.QuadVertexBufferPtr->Position = transform * s_Data.QuadVertexPositions[i];
            s_Data.QuadVertexBufferPtr->Color = color;
            s_Data.QuadVertexBufferPtr->TexCoord = textureCoords[i];
            s_Data.QuadVertexBufferPtr->TexIndex = textureIndex;
            s_Data.QuadVertexBufferPtr->TilingFactor = tilingFactor;
            s_Data.QuadVertexBufferPtr++;
        }

        s_Data.QuadIndexCount += 6;

        s_Data.Stats.QuadCount++;
    }

    void Renderer2D::ResetStats()
    {
        memset(&s_Data.Stats, 0, sizeof(Statistics));
    }

    Renderer2D::Statistics Renderer2D::GetStats()
    {
        return s_Data.Stats;
    }

} // namespace Kaleidoscope
