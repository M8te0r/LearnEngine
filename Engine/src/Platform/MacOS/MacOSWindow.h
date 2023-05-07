#pragma once
#include "Kaleidoscope/Window.h"

// GLFW和glad共用时需要启用（定义在cmake里）
// #define GLFW_INCLUDE_NONE
#include "GLFW/glfw3.h"

namespace Kaleidoscope
{
    class MacWindow : public Window
    {
    public:
        MacWindow(const WindowProps &props);
        virtual ~MacWindow();

        void OnUpdate() override;

        inline unsigned int GetWidth() const override { return m_Data.Width; }
        inline unsigned int GetHeight() const override { return m_Data.Height; }

        // window 属性
        inline void SetEventCallback(const EventCallbackFn &callback) override { m_Data.EventCallback = callback; }
        void SetVSync(bool enabled) override;
        bool IsVSync() const override;

        virtual void *GetNativeWindow() const override { return m_Window; }

    private:
        virtual void Init(const WindowProps &props);
        virtual void Shutdown();

    private:
        GLFWwindow *m_Window;
        struct WindowData
        {
            std::string Title;
            unsigned int Width, Height;
            bool VSync;

            EventCallbackFn EventCallback;
        };
        WindowData m_Data;
    };

} // namespace Kaleidoscope
