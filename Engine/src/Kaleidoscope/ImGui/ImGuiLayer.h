#pragma once
#include "Kaleidoscope/Core/Layer.h"

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
        virtual void OnImGuiRender() override;

        void Begin();
        void End();

    private:
        float m_Time = 0.0f;
    };

} // namespace Kaleidoscope
