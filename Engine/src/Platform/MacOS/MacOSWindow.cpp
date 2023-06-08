#include "kldpch.h"
#include "Platform/MacOS/MacOSWindow.h"

#include "Kaleidoscope/Core/Input.h"

#include "Kaleidoscope/Events/ApplicationEvent.h"
#include "Kaleidoscope/Events/MouseEvent.h"
#include "Kaleidoscope/Events/KeyEvent.h"

#include "Platform/OpenGL/OpenGLContext.h"

namespace Kaleidoscope
{
    static uint8_t s_GLFWWindowCount = 0;

    static void GLFWErrorCallback(int error, const char *description)
    {
        KLD_CORE_ERROR("GLFW Error ({0}): {1}", error, description);
    }



    MacOSWindow::MacOSWindow(const WindowProps &props)
    {
        KLD_PROFILE_FUNCTION();

        Init(props);
    }

    MacOSWindow::~MacOSWindow()
    {
        KLD_PROFILE_FUNCTION();

        Shutdown();
    }

    void MacOSWindow::Init(const WindowProps &props)
    {
        KLD_PROFILE_FUNCTION();

        m_Data.Title = props.Title;
        m_Data.Width = props.Width;
        m_Data.Height = props.Height;

        KLD_CORE_INFO("Creating Window {0} {1}, {2}", props.Title, props.Width, props.Height);

        if (s_GLFWWindowCount == 0)
        {
            KLD_PROFILE_SCOPE("glfwInit");
            int success = glfwInit();
            KLD_CORE_ASSERT(success, "Could not initialize GLFW!");
            glfwSetErrorCallback(GLFWErrorCallback);
        }

        {
            KLD_PROFILE_SCOPE("glfwCreateWindow");
            // GL 3.2 + GLSL 150
            // const char *glsl_version = "#version 150";
            glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
            glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
            glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // 3.2+ only
            glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GLFW_TRUE);         // Required on Mac

            m_Window = glfwCreateWindow((int)props.Width, (int)props.Height, m_Data.Title.c_str(), nullptr, nullptr);
            ++s_GLFWWindowCount;
        }

        // 初始化上下文
        m_Context = GraphicsContext::Create(m_Window);
        m_Context->Init();

        glfwSetWindowUserPointer(m_Window, &m_Data);
        SetVSync(true);

        // = = = = = = = = = = = = = = = = = = = = = = =
        // 设置GLFW的callback（callback函数为lambda表达式形式）
        // = = = = = = = = = = = = = = = = = = = = = = =

        glfwSetWindowSizeCallback(m_Window, [](GLFWwindow *window, int width, int height)
                                  {
                                    // 获取当前窗口的指针，将指针转换为WindowData类型，再解引用获取指向的内容
                                    // 简而言之，获取当前window的指针，为其绑定对应的event
                                      WindowData &data = *(WindowData *)glfwGetWindowUserPointer(window);
                                      data.Width = width;
                                      data.Height = height;
                                      WindowResizeEvent event(width, height);
                                      data.EventCallback(event); });

        glfwSetWindowCloseCallback(m_Window, [](GLFWwindow *window)
                                   {
                                      WindowData &data = *(WindowData *)glfwGetWindowUserPointer(window);
                                      WindowCloseEvent event;
                                      data.EventCallback(event); });

        glfwSetKeyCallback(m_Window, [](GLFWwindow *window, int key, int scancode, int action, int mods)
                           {
                                WindowData &data = *(WindowData *)glfwGetWindowUserPointer(window);
                                switch (action)
                                {
                                    case GLFW_PRESS:
                                    {
                                        KeyPressedEvent event(key,0);
                                        data.EventCallback(event);
                                        break;
                                    }                                        
                                    case GLFW_RELEASE:
                                    {
                                        KeyReleasedEvent event(key);
                                        data.EventCallback(event);
                                        break;
                                    }
                                    case GLFW_REPEAT:
                                    {
                                        KeyPressedEvent event(key,1);
                                        data.EventCallback(event);
                                        break;
                                    }
                            } });

        glfwSetCharCallback(m_Window, [](GLFWwindow *window, unsigned int keycode)
                            {
            WindowData &data = *(WindowData *)glfwGetWindowUserPointer(window);
            KeyTypedEvent event(keycode);
            data.EventCallback(event); });

        glfwSetMouseButtonCallback(m_Window, [](GLFWwindow *window, int button, int action, int mods)
                                   {
            WindowData &data = *(WindowData *)glfwGetWindowUserPointer(window);
            switch (action)
            {
            case GLFW_PRESS:
            {
                MouseButtonPressedEvent event(button);
                data.EventCallback(event);
                break;
            }
            case GLFW_RELEASE:
            {
                MouseButtonReleasedEvent event(button);
                data.EventCallback(event);
                break;
            }
            } });

        glfwSetScrollCallback(m_Window, [](GLFWwindow *window, double xOffset, double yOffset)
                              {
            WindowData &data = *(WindowData *)glfwGetWindowUserPointer(window);
            MouseScrolledEvent event((float)xOffset, (float)yOffset);
            data.EventCallback(event); });

        glfwSetCursorPosCallback(m_Window, [](GLFWwindow *window, double xPos, double yPos)
                                 {
            WindowData &data = *(WindowData *)glfwGetWindowUserPointer(window);
            MouseMovedEvent event((float)xPos, (float)yPos);
            data.EventCallback(event); });
    }

    void MacOSWindow::Shutdown()
    {
        KLD_PROFILE_FUNCTION();

        glfwDestroyWindow(m_Window);
        --s_GLFWWindowCount;

        if (s_GLFWWindowCount == 0)
        {
            KLD_CORE_INFO("Terminating GLFW");
            glfwTerminate();
        }
    }

    void MacOSWindow::OnUpdate()
    {
        KLD_PROFILE_FUNCTION();

        glfwPollEvents();
        m_Context->SwapBuffers();
    }

    void MacOSWindow::SetVSync(bool enabled)
    {
        KLD_PROFILE_FUNCTION();

        if (enabled)
        {
            glfwSwapInterval(1);
        }
        else
        {
            glfwSwapInterval(0);
        }
        m_Data.VSync = enabled;
    }

    bool MacOSWindow::IsVSync() const
    {
        return m_Data.VSync;
    }

} // namespace Kaleidoscope
