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

        virtual void OnAttach() override;
        virtual void OnDetach() override;
        virtual void OnUpdate() override;
        virtual void OnEvent(Event &event) override;

    private:
        float m_Time = 0.0f;
    };

} // namespace Kaleidoscope
