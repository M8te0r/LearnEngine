#include "kldpch.h"
#include "Platform/MacOS/MacOSInput.h"

#include "GLFW/glfw3.h"
#include "Kaleidoscope/Core/Application.h"
namespace Kaleidoscope
{
    Input *Input::s_Instance = new MacOSInput();

    bool MacOSInput::IsKeyPressedImpl(int keycode)
    {
        auto window = static_cast<GLFWwindow *>(Application::Get().GetWindow().GetNativeWindow());
        auto state = glfwGetKey(window, keycode);
        return state == GLFW_PRESS || state == GLFW_REPEAT;
    }

    bool MacOSInput::IsMouseButtonPressedImpl(int button)
    {
        auto window = static_cast<GLFWwindow *>(Application::Get().GetWindow().GetNativeWindow());
        auto state = glfwGetMouseButton(window, button);
        return state == GLFW_PRESS;
    }

    std::pair<float, float> MacOSInput::GetMousePositionImpl()
    {
        auto window = static_cast<GLFWwindow *>(Application::Get().GetWindow().GetNativeWindow());
        double xpos, ypos;
        glfwGetCursorPos(window, &xpos, &ypos);
        return {(float)xpos, (float)ypos};
    }

    float MacOSInput::GetMouseXImpl()
    {
        auto [x, y] = GetMousePositionImpl(); // c++ 17语法
        return x;
    }

    float MacOSInput::GetMouseYImpl()
    {
        auto [x, y] = GetMousePositionImpl(); // c++ 17语法
        return y;
    }
} // namespace Kaleidoscope
