#include "kldpch.h"
#include "Kaleidoscope/OrthographicCameraController.h"

#include "Kaleidoscope/Input.h"
#include "Kaleidoscope/KeyCodes.h"

namespace Kaleidoscope
{
    OrthographicCameraController::OrthographicCameraController(float aspectRatio, bool rotation)
        : m_AspectRatio(aspectRatio), m_Camera(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel), m_Rotation(rotation)
    {
    }

    void OrthographicCameraController::OnUpdate(Timestep ts)
    {
        if (Input::IsKeyPressed(KLD_KEY_A))
        {
            m_CameraPosition.x -= m_CameraTranslationSpeed * ts;
        }
        else if (Input::IsKeyPressed(KLD_KEY_D))
        {
            m_CameraPosition.x += m_CameraTranslationSpeed * ts;
        }

        if (Input::IsKeyPressed(KLD_KEY_W))
        {
            m_CameraPosition.y += m_CameraTranslationSpeed * ts;
        }
        else if (Input::IsKeyPressed(KLD_KEY_S))
        {
            m_CameraPosition.y -= m_CameraTranslationSpeed * ts;
        }

        if (m_Rotation)
        {
            if (Input::IsKeyPressed(KLD_KEY_Q))
            {
                m_CameraRotation += m_CameraRotationSpeed * ts;
            }
            else if (Input::IsKeyPressed(KLD_KEY_E))
            {
                m_CameraRotation -= m_CameraRotationSpeed * ts;
            }
            m_Camera.SetRotation(m_CameraRotation);
        }
        m_Camera.SetPosition(m_CameraPosition);

        // 当放大物体的时候，降低相机速度，当缩小物体的时候，提高相机速度
        m_CameraTranslationSpeed = m_ZoomLevel;
    }

    void OrthographicCameraController::OnEvent(Event &e)
    {
        EventDispatcher dispatcher(e);
        dispatcher.Dispatch<MouseScrolledEvent>(KLD_BIND_EVENT_FN(OrthographicCameraController::OnMouseScrolled));
        dispatcher.Dispatch<WindowResizeEvent>(KLD_BIND_EVENT_FN(OrthographicCameraController::OnWindowResized));
    }

    bool OrthographicCameraController::OnMouseScrolled(MouseScrolledEvent &e)
    {
        m_ZoomLevel -= e.GetYOffset() * 0.25f;
        m_ZoomLevel = std::max(m_ZoomLevel, 0.25f);
        m_Camera.SetProjection(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel);
        return false;
    }

    bool OrthographicCameraController::OnWindowResized(WindowResizeEvent &e)
    {

        // FIXME: 改变窗口大小的时候，画面不能正确显示
        m_AspectRatio -= (float)e.GetWidth() / (float)e.GetHeight();
        m_Camera.SetProjection(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel);
        return false;
    }

} // namespace Kaleidoscope
