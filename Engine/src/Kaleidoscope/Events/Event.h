#pragma once

#include <functional>
#include "Kaleidoscope/Debug/Instrumentor.h"
#include "Kaleidoscope/Core/Base.h"

namespace Kaleidoscope
{
    // = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =
    // FIXME 事件系统，参考《设计模式》 https://zhuanlan.zhihu.com/p/535574136
    // = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =

    // Event种类
    enum class EventType
    {
        None = 0,
        // 窗口
        WindowClose,
        WindowResize,
        WindowFocus,
        WindowLostFocus,
        WindowMoved,
        // 渲染
        AppTick,
        AppUpdate,
        AppRender,
        KeyPressed,
        KeyReleased,
        KeyTyped,
        // 鼠标
        MouseButtonPressed,
        MouseButtonReleased,
        MouseMoved,
        MouseScrolled
    };

    // 用于过滤不同的Event类型
    enum EventCategory
    {
        None = 0,
        EventCategoryApplication = BIT(0),
        EventCategoryInput = BIT(1),
        EventCategoryKeyboard = BIT(2),
        EventCategoryMouse = BIT(3),
        EventCategoryMouseButton = BIT(4)
    };

// 定义一个宏，用于在每个Event派生类中获取当前Event的类型名称
#define EVENT_CLASS_TYPE(type)                                                  \
    static EventType GetStaticType() { return EventType::type; }                \
    virtual EventType GetEventType() const override { return GetStaticType(); } \
    virtual const char *GetName() const override { return #type; }

// 定义一个宏，用于在每个Event派生类中获取当前Event的所属的分类
#define EVENT_CLASS_CATEGORY(category) \
    virtual int GetCategoryFlags() const override { return category; }

    class Event
    {

    public:
        virtual ~Event() = default;

        bool Handled = false;

        virtual EventType GetEventType() const = 0;
        virtual const char *GetName() const = 0;
        virtual int GetCategoryFlags() const = 0;
        virtual std::string ToString() const { return GetName(); }

        inline bool IsInCategory(EventCategory category)
        {
            return GetCategoryFlags() & category;
        }
    };

    class EventDispatcher
    {
    public:
        EventDispatcher(Event &event)
            : m_Event(event)
        {
        }

        // F will be deduced by the compiler
        template <typename T, typename F>
        bool Dispatch(const F &func)
        {
            if (m_Event.GetEventType() == T::GetStaticType())
            {
                m_Event.Handled |= func(static_cast<T &>(m_Event));
                return true;
            }
            return false;
        }

    private:
        Event &m_Event;
    };

    inline std::ostream &operator<<(std::ostream &os, const Event &e)
    {
        return os << e.ToString();
    }

} // namespace Kaleidoscope
