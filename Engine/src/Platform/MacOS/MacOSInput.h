#pragma once

#include "Kaleidoscope/Core/Input.h"

namespace Kaleidoscope
{
    class MacOSInput : public Input
    {
    protected:
        virtual bool IsKeyPressedImpl(int keycode) override;

        virtual bool IsMouseButtonPressedImpl(int button) override;
        virtual std::pair<float, float> GetMousePositionImpl() override;
        virtual float GetMouseXImpl() override;
        virtual float GetMouseYImpl() override;
    };

} // namespace Kaleidoscope
