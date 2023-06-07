#pragma once

#include "Kaleidoscope/Renderer/OrthographicCamera.h"
#include "Kaleidoscope/Core/Timestep.h"
#include "Kaleidoscope/Events/ApplicationEvent.h"
#include "Kaleidoscope/Events/MouseEvent.h"

namespace Kaleidoscope
{
    struct OrthographicCameraBounds
    {
        float Left, Right;
        float Bottom, Top;

        float GetWidth() { return Right - Left; }
        float GetHeight() { return Top - Bottom; }
    };

    class OrthographicCameraController
    {
    public:
        OrthographicCameraController(float aspectRatio, bool rotation = false);

        void OnUpdate(Timestep ts);
        void OnEvent(Event &e);

        OrthographicCamera &GetCamera() { return m_Camera; }
        const OrthographicCamera &GetCamera() const { return m_Camera; }

        void SetZoomLevel(float level) { m_ZoomLevel = level; CalculateView(); }
        float GetZoomLevel() const { return m_ZoomLevel; }

        const OrthographicCameraBounds& GetBounds() const { return m_Bounds; }

    private:
        void CalculateView();
        bool OnMouseScrolled(MouseScrolledEvent &e);
        bool OnWindowResized(WindowResizeEvent &e);

    private:
        float m_AspectRatio;
        float m_ZoomLevel = 1.0f;
        OrthographicCameraBounds m_Bounds;
        OrthographicCamera m_Camera;

        bool m_Rotation;
        glm::vec3 m_CameraPosition = {0.0f, 0.0f, 0.0f};
        float m_CameraRotation = 0.0f;
        float m_CameraTranslationSpeed = 5.0f, m_CameraRotationSpeed = 180.0f;
    };

} // namespace Kaleidoscope
