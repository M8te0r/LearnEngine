
#include "Engine.h"

class ExampleLayer : public Kaleidoscope::Layer
{
public:
    ExampleLayer() : Layer("Example") {}

    void OnUpdate() override
    {
        // KLD_INFO("ExampleLayer::Update");
        if (Kaleidoscope::Input::IsKeyPressed(KLD_KEY_TAB))
        {
            KLD_TRACE("Tab key is pressed (poll)!");
        }
    }

    void OnEvent(Kaleidoscope::Event &event) override
    {
        // KLD_TRACE("{0}", event);
        if (event.GetEventType() == Kaleidoscope::EventType::KeyPressed)
        {
            Kaleidoscope::KeyPressedEvent &e = (Kaleidoscope::KeyPressedEvent &)event;
            if (e.GetKeyCode() == KLD_KEY_TAB)
            {
                KLD_TRACE("Tab key is pressed (evnet)!");
            }
            KLD_TRACE("{0}", (char)e.GetKeyCode());
        }
    }
};

class Sandbox : public Kaleidoscope::Application
{
public:
    Sandbox()
    {
        PushLayer(new ExampleLayer());
        PushOverlay(new Kaleidoscope::ImGuiLayer());
    }
    ~Sandbox()
    {
    }
};

Kaleidoscope::Application *Kaleidoscope::CreateApplication()
{
    return new Sandbox();
}