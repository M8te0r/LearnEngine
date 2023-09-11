#include "kldpch.h"
#include "Platform/OpenGL/OpenGLShader.h"
#include "glad/glad.h"
#include <fstream>

#include "glm/gtc/type_ptr.hpp"

namespace Kaleidoscope
{
    static GLenum ShaderTypeFromString(const std::string &type)
    {
        if (type == "vertex")
            return GL_VERTEX_SHADER;
        if (type == "fragment" || type == "pixel")
            return GL_FRAGMENT_SHADER;

        // TODO 需要添加geometry shader类型
        KLD_CORE_ASSERT(false, "Unknown shader type!");
        return 0;
    }

    OpenGLShader::OpenGLShader(const std::string &filepath)
    {
        KLD_PROFILE_FUNCTION();

        std::string source = ReadFile(filepath);
        auto shaderSources = Preprocess(source);
        Compile(shaderSources);

        // 从文件的路径中提取文件名
        // 找最后一个斜杠
        // assets/shaders/Texture. glsl
        auto lastSlash = filepath.find_last_of("/\\");
        // 如果是没有斜杠，即文件就在目录下Texture.glsl
        lastSlash = lastSlash == std::string::npos ? 0 : lastSlash + 1;

        // 找最后一个点
        auto lastDot = filepath.rfind('.');

        // 获取文件名
        auto count = lastDot == std::string::npos ? filepath.size() - lastSlash : lastDot - lastSlash;
        m_Name = filepath.substr(lastSlash, count);
    }

    OpenGLShader::OpenGLShader(const std::string &name, const std::string &vertexSrc, const std::string &fragmentSrc)
        : m_Name(name)
    {
        KLD_PROFILE_FUNCTION();

        std::unordered_map<GLenum, std::string> sources;
        sources[GL_VERTEX_SHADER] = vertexSrc;
        sources[GL_FRAGMENT_SHADER] = fragmentSrc;
        Compile(sources);
    }

    OpenGLShader::~OpenGLShader()
    {
        KLD_PROFILE_FUNCTION();

        glDeleteProgram(m_RendererID);
    }

    std::string OpenGLShader::ReadFile(const std::string &filepath)
    {
        KLD_PROFILE_FUNCTION();

        std::string result;
        std::ifstream in(filepath, std::ios::in | std::ios::binary); // ifstream closes itself due to RAII

        if (in)
        {
            in.seekg(0, std::ios::end);
            result.resize(in.tellg());
            in.seekg(0, std::ios::beg);
            in.read(&result[0], result.size());
        }
        else
        {
            KLD_CORE_ERROR("Could not open file '{0}'!", filepath);
        }
        return result;
    }
    std::unordered_map<GLenum, std::string> OpenGLShader::Preprocess(const std::string &source)
    {
        KLD_PROFILE_FUNCTION();

        std::unordered_map<GLenum, std::string> shaderSources;

        const char *typeToken = "#type";
        size_t typeTokenLength = strlen(typeToken);
        size_t pos = source.find(typeToken, 0);
        while (pos != std::string::npos)
        {
            size_t eol = source.find_first_of("\r\n", pos);
            KLD_CORE_ASSERT(eol != std::string::npos, "Syntax error!");
            size_t begin = pos + typeTokenLength + 1;
            std::string type = source.substr(begin, eol - begin);
            KLD_CORE_ASSERT(ShaderTypeFromString(type), "Invalid shader type specified!");

            size_t nextLinePos = source.find_first_not_of("\r\n", eol);
            pos = source.find(typeToken, nextLinePos);
            shaderSources[ShaderTypeFromString(type)] = source.substr(nextLinePos, pos - (nextLinePos == std::string::npos ? source.size() - 1 : nextLinePos));
        }
        return shaderSources;
    }

    void OpenGLShader::Compile(const std::unordered_map<GLenum, std::string> &shaderSources)
    {
        KLD_PROFILE_FUNCTION();

        GLuint program = glCreateProgram();

        KLD_CORE_ASSERT(shaderSource.size() <= 2, "We only support 2 shaders for now!");
        std::array<GLenum, 2> glShaderIDs;
        int glShadersIDIndex = 0;

        // https://blog.csdn.net/hl_zzl/article/details/84944494
        // reserve的作用是更改vector的容量（capacity），使vector至少可以容纳n个元素。
        // 如果使用动态初始化，即std::vector<GLenum> glShaderIDs(shaderSources.size())，verctor会额外分配2个空内存占位
        // 且应为std::vector是采用堆内存分配机制的，性能不及栈内存分配机制的std::array

        for (auto &kv : shaderSources)
        {
            GLenum type = kv.first;
            const std::string &source = kv.second;

            // create shader
            GLuint shader = glCreateShader(type);

            // Send the vertex shader source code to GL
            // Note that std::string's .c_str is NULL character terminated.
            const GLchar *sourceCStr = source.c_str();
            glShaderSource(shader, 1, &sourceCStr, 0);

            // Compile the vertex shader
            glCompileShader(shader);

            GLint isCompiled = 0;
            glGetShaderiv(shader, GL_COMPILE_STATUS, &isCompiled);
            if (isCompiled == GL_FALSE)
            {
                GLint maxLength = 0;
                glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &maxLength);

                // The maxLength includes the NULL character
                std::vector<GLchar> infoLog(maxLength);
                glGetShaderInfoLog(shader, maxLength, &maxLength, &infoLog[0]);

                // We don't need the shader anymore.
                glDeleteShader(shader);

                KLD_CORE_ERROR("{0}", infoLog.data());
                KLD_CORE_ASSERT(false, "Shader compilation failure!");
                break;
            }

            // Attach our shaders to our program
            glAttachShader(program, shader);
            glShaderIDs[glShadersIDIndex++] = shader;
        }

        // Vertex and fragment shaders are successfully compiled.
        // Now time to link them together into a program.
        // Get a program object.

        // Link our program
        glLinkProgram(program);

        // Note the different functions here: glGetProgram* instead of glGetShader*.
        GLint isLinked = 0;
        glGetProgramiv(program, GL_LINK_STATUS, (int *)&isLinked);
        if (isLinked == GL_FALSE)
        {
            GLint maxLength = 0;
            glGetProgramiv(program, GL_INFO_LOG_LENGTH, &maxLength);

            // The maxLength includes the NULL character
            std::vector<GLchar> infoLog(maxLength);
            glGetProgramInfoLog(program, maxLength, &maxLength, &infoLog[0]);

            // We don't need the program anymore.
            glDeleteProgram(program);

            // Don't leak shaders either.
            for (auto id : glShaderIDs)
            {
                glDeleteShader(id);
            }

            KLD_CORE_ERROR("{0}", infoLog.data());
            KLD_CORE_ASSERT(false, "Shader link failure!");
            return;
        }

        // Always detach shaders after a successful link.
        for (auto id : glShaderIDs)
        {
            glDetachShader(program, id);
        }
        m_RendererID = program;
    }

    void OpenGLShader::Bind() const
    {
        KLD_PROFILE_FUNCTION();

        // FIXME: happed on Apple M1 only
        // UNSUPPORTED (log once): POSSIBLE ISSUE: unit 1 GLD_TEXTURE_INDEX_2D is unloadable and bound to sampler type (Float) - using zero texture because texture unloadable
        // possibly solutions:
        // https://stackoverflow.com/questions/70338946/gl-texturen1-activated-and-bound-instead-of-gl-texturen-on-apple-silicon-m1-po
        // https://developer.apple.com/forums/thread/683865

        glUseProgram(m_RendererID);
    }

    void OpenGLShader::UnBind() const
    {
        KLD_PROFILE_FUNCTION();

        glUseProgram(0);
    }

    void OpenGLShader::SetInt(const std::string &name, int value)
    {
        KLD_PROFILE_FUNCTION();

        UploadUniformInt(name, value);
    }

    void OpenGLShader::SetIntArray(const std::string &name, int *values, uint32_t count)
    {
        KLD_PROFILE_FUNCTION();

        UploadUniformIntArray(name, values, count);
    }

    void OpenGLShader::SetFloat(const std::string &name, float value)
    {
        KLD_PROFILE_FUNCTION();

        UploadUniformFloat(name, value);
    }

    void OpenGLShader::SetFloat2(const std::string& name, const glm::vec2& value)
    {
        KLD_PROFILE_FUNCTION();

        UploadUniformFloat2(name, value);
    }

    void OpenGLShader::SetFloat3(const std::string &name, const glm::vec3 &value)
    {
        KLD_PROFILE_FUNCTION();

        UploadUniformFloat3(name, value);
    }

    void OpenGLShader::SetFloat4(const std::string &name, const glm::vec4 &value)
    {
        KLD_PROFILE_FUNCTION();

        UploadUniformFloat4(name, value);
    }

    void OpenGLShader::SetMat4(const std::string &name, const glm::mat4 &value)
    {
        KLD_PROFILE_FUNCTION();

        UploadUniformMat4(name, value);
    }

    void OpenGLShader::UploadUniformInt(const std::string &name, int value)
    {
        GLint location = glGetUniformLocation(m_RendererID, name.c_str());
        glUniform1i(location, value);
    }

    void OpenGLShader::UploadUniformIntArray(const std::string &name, int *values, uint32_t count)
    {
        GLint location = glGetUniformLocation(m_RendererID, name.c_str());
        glUniform1iv(location, count, values);
    }

    void OpenGLShader::UploadUniformFloat(const std::string &name, float value)
    {
        GLint location = glGetUniformLocation(m_RendererID, name.c_str());
        glUniform1f(location, value);
    }

    void OpenGLShader::UploadUniformFloat2(const std::string &name, const glm::vec2 &value)
    {
        GLint location = glGetUniformLocation(m_RendererID, name.c_str());
        glUniform2f(location, value.x, value.y);
    }

    void OpenGLShader::UploadUniformFloat3(const std::string &name, const glm::vec3 &value)
    {
        GLint location = glGetUniformLocation(m_RendererID, name.c_str());
        glUniform3f(location, value.x, value.y, value.z);
    }

    void OpenGLShader::UploadUniformFloat4(const std::string &name, const glm::vec4 &value)
    {
        GLint location = glGetUniformLocation(m_RendererID, name.c_str());
        glUniform4f(location, value.x, value.y, value.z, value.w); // 位置索引location，1个矩阵，不需要转秩，矩阵指针
    }

    void OpenGLShader::UploadUniformMat3(const std::string &name, const glm::mat3 &matrix)
    {
        GLint location = glGetUniformLocation(m_RendererID, name.c_str());
        glUniformMatrix3fv(location, 1, GL_FALSE, glm::value_ptr(matrix)); // 位置索引location，1个矩阵，不需要转秩，矩阵指针
    }

    void OpenGLShader::UploadUniformMat4(const std::string &name, const glm::mat4 &matrix)
    {
        GLint location = glGetUniformLocation(m_RendererID, name.c_str());
        glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(matrix)); // 位置索引location，1个矩阵，不需要转秩，矩阵指针
    }

} // namespace Kaleidoscope
