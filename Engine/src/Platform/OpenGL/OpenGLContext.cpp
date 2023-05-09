#include "kldpch.h"
#include "Platform/OpenGL/OpenGLContext.h"

#include "GLFW/glfw3.h"
#include "glad/glad.h"

namespace Kaleidoscope
{
    OpenGLContext::OpenGLContext(GLFWwindow *windowHandle) : m_WindowHandle(windowHandle)
    {
        KLD_CORE_ASSERT(windowHandle, "Window handle is null!");
    }

    void OpenGLContext::Init()
    {
        glfwMakeContextCurrent(m_WindowHandle);
        // 使用glad载入所有opengl函数指针
        int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
        KLD_CORE_ASSERT(status, "Failed to initialize Glad!");

        KLD_CORE_INFO("OpenGL Info:");

        // spdlog 不再支持unsigned const char* 数据（glGetString()返回的）
        KLD_CORE_INFO("  Vendor: {0}", reinterpret_cast<const char *>(glGetString(GL_VENDOR)));
        KLD_CORE_INFO("  Vendor: {0}", reinterpret_cast<const char *>(glGetString(GL_RENDERER)));
        KLD_CORE_INFO("  Vendor: {0}", reinterpret_cast<const char *>(glGetString(GL_VERSION)));

        // KLD_CORE_INFO("  Renderer: {0}", glGetString(GL_RENDERER));
        // KLD_CORE_INFO("  Version: {0}", glGetString(GL_VERSION));
    }

    void OpenGLContext::SwapBuffers()
    {
        glfwSwapBuffers(m_WindowHandle);
    }

} // namespace Kaleidoscope