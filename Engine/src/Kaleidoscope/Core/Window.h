#pragma once
#include "Kaleidoscope/Core/Base.h"
#include "Kaleidoscope/Events/Event.h"
#include <sstream>

namespace Kaleidoscope
{

    struct WindowProps
    {
        std::string Title;
        uint32_t Width;
        uint32_t Height;

        WindowProps(const std::string &title = "Kaleidoscope Engine",
                    uint32_t width = 1280,
                    uint32_t height = 720)
            : Title(title), Width(width), Height(height) {}
    };

    // window基类，在不同的os上实现
    class Window
    {
    public:
        using EventCallbackFn = std::function<void(Event &)>;

        virtual ~Window() = default;

        virtual void OnUpdate() = 0;

        virtual uint32_t GetWidth() const = 0;
        virtual uint32_t GetHeight() const = 0;

        // Window 属性
        virtual void SetEventCallback(const EventCallbackFn &callback) = 0;
        virtual void SetVSync(bool enabled) = 0;
        virtual bool IsVSync() const = 0;

        virtual void *GetNativeWindow() const = 0;

        static Scope<Window> Create(const WindowProps &props = WindowProps());
    };

} // namespace Kaleidoscope
