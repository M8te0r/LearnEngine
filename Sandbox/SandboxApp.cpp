
#include "Engine.h"

class ExampleLayer : public Kaleidoscope::Layer
{
public:
    ExampleLayer() : Layer("Example") {}

    void OnUpdate() override
    {
        KLD_INFO("ExampleLayer::Update");
    }

    void OnEvent(Kaleidoscope::Event &event) override
    {
        KLD_TRACE("{0}", event);
    }
};

class Sandbox : public Kaleidoscope::Application
{
public:
    Sandbox()
    {
        PushLayer(new ExampleLayer());
    }
    ~Sandbox()
    {
    }
};

Kaleidoscope::Application *Kaleidoscope::CreateApplication()
{
    return new Sandbox();
}