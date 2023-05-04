#include "Kaleidoscope/Core.h"
#include "Kaleidoscope/Events/Event.h"
#include <sstream>

namespace Kaleidoscope
{

    struct WindowProps
    {
        std::string Title;
        unsigned int Width;
        unsigned int Height;

        WindowProps(const std::string &title = "Kaleidoscope Engine",
                    unsigned int width = 1280,
                    unsigned int height = 720)
            : Title(title), Width(width), Height(height) {}
    };

    // window基类，在不同的os上实现
    class Window
    {
    public:
        using EventCallbackFn = std::function<void(Event &)>;
        virtual ~Window() {}
        virtual void OnUpdate() = 0;
        virtual unsigned int GetWidth() const = 0;
        virtual unsigned int GetHeight() const = 0;

        // Window 属性
        virtual void SetEventCallback(const EventCallbackFn &callback) = 0;
        virtual void SetVSync(bool enabled) = 0;
        virtual bool IsVSync() const = 0;

        static Window *Create(const WindowProps &props = WindowProps());
    };

} // namespace Kaleidoscope
