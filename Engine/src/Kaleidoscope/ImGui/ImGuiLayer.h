#pragma once
#include "Kaleidoscope/Layer.h"

#include "Kaleidoscope/Events/KeyEvent.h"
#include "Kaleidoscope/Events/MouseEvent.h"
#include "Kaleidoscope/Events/ApplicationEvent.h"

namespace Kaleidoscope
{
    class ImGuiLayer : public Layer
    {
    public:
        ImGuiLayer();
        ~ImGuiLayer();

        void OnAttach();
        void OnDetach();
        void OnUpdate();
        void OnEvent(Event &event);

    private:
        bool OnMouseButtonPressedEvent(MouseButtonPressedEvent &e);
        bool OnMouseButtonReleasedEvent(MouseButtonReleasedEvent &e);
        bool OnMouseMovedEvent(MouseMovedEvent &e);
        bool OnMouseScrolledEvent(MouseScrolledEvent &e);
        bool OnKeyPressedEvent(KeyPressedEvent &e);
        bool OnKeyReleasedEvent(KeyReleasedEvent &e);
        bool OnKeyTypedEvent(KeyTypedEvent &e);
        bool OnWindowResizeEvent(WindowResizeEvent &e);

    private:
        float m_Time = 0.0f;
    };

} // namespace Kaleidoscope
