#include "kldpch.h"
#include "Platform/OpenGL/OpenGLTexture.h"

#include "stb_image/stb_image.h"
#include "glad/glad.h"

namespace Kaleidoscope
{

    // TODO: 采用相对路径时，std_image无法正确读取纹理图片
    OpenGLTexture2D::OpenGLTexture2D(const std::string &path)
        : m_Path(path)
    {
        int width, height, channels;
        stbi_set_flip_vertically_on_load(1);
        stbi_uc *data = stbi_load(path.c_str(), &width, &height, &channels, 0);

        // https://stackoverflow.com/questions/49462889/stbi-load-doesnt-return-any-value
        /*
        if (stbi_failure_reason())
            std::cout << "\n"
                      << stbi_failure_reason() << "\n";
        */

        KLD_CORE_ASSERT(data, "Failed to load image!");
        m_Width = width;
        m_Height = height;

        GLenum internalFormat = 0, dataFormat = 0; // 显卡上的存储格式，源图片的存储格式
        if (channels == 4)
        {
            internalFormat = GL_RGBA8;
            dataFormat = GL_RGBA;
        }
        else if (channels == 3)
        {
            internalFormat = GL_RGB8;
            dataFormat = GL_RGB;
        }

        KLD_CORE_ASSERT(internalFormat & dataFormat, "Format not supported!");

        // FIXME OpenGL 4.5 only
        // glCreateTextures(GL_TEXTURE_2D, 1, &m_RendererID);
        // glTextureStorage2D(m_RendererID, 1, internalFormat, m_Width, m_Height);
        // glTextureParameteri(m_RendererID, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        // glTextureParameteri(m_RendererID, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        // glTextureSubImage2D(m_RendererID, 0, 0, 0, m_Width, m_Height, dataFormat, GL_UNSIGNED_BYTE, data);

        glGenTextures(1, &m_RendererID);
        glBindTexture(GL_TEXTURE_2D, m_RendererID);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);



        glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, m_Width, m_Height, 0, dataFormat, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
        // glBindTexture(GL_TEXTURE_2D, 0);
        stbi_image_free(data);
    }

    OpenGLTexture2D::~OpenGLTexture2D()
    {
        glDeleteTextures(1, &m_RendererID);
    }

    void OpenGLTexture2D::Bind(uint32_t slot) const
    {

        // FIXME OpenGL 4.5 only
        // glBindTextureUnit(slot, m_RendererID);

        glActiveTexture(GL_TEXTURE0 + slot);
        glBindTexture(GL_TEXTURE_2D, m_RendererID);
    }

} // namespace Kaleidoscope
