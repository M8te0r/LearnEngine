#pragma once

#include "Kaleidoscope/Renderer/GraphicsContext.h"

// forward declare
struct GLFWwindow;
namespace Kaleidoscope
{
    class OpenGLContext : public GraphicsContext
    {
    public:
        OpenGLContext(GLFWwindow *windowHandle);
        virtual void Init() override;
        virtual void SwapBuffers() override;

    private:
        GLFWwindow *m_WindowHandle;
    };

} // namespace Kaleidoscope
