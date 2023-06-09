#include "kldpch.h"
#include "Kaleidoscope/Core/Input.h"

#include "GLFW/glfw3.h"
#include "Kaleidoscope/Core/Application.h"
namespace Kaleidoscope
{

    bool Input::IsKeyPressed(KeyCode key)
    {
        auto window = static_cast<GLFWwindow *>(Application::Get().GetWindow().GetNativeWindow());
        auto state = glfwGetKey(window, static_cast<int32_t>(key));
        return state == GLFW_PRESS || state == GLFW_REPEAT;
    }

    bool Input::IsMouseButtonPressed(MouseCode button)
    {
        auto window = static_cast<GLFWwindow *>(Application::Get().GetWindow().GetNativeWindow());
        auto state = glfwGetMouseButton(window, static_cast<int32_t>(button));
        return state == GLFW_PRESS;
    }

    std::pair<float, float> Input::GetMousePosition()
    {
        auto window = static_cast<GLFWwindow *>(Application::Get().GetWindow().GetNativeWindow());
        double xpos, ypos;
        glfwGetCursorPos(window, &xpos, &ypos);
        return {(float)xpos, (float)ypos};
    }

    float Input::GetMouseX()
    {
        auto [x, y] = GetMousePosition(); // c++ 17语法
        return x;
    }

    float Input::GetMouseY()
    {
        auto [x, y] = GetMousePosition(); // c++ 17语法
        return y;
    }
} // namespace Kaleidoscope
