#pragma once

#include "Render/OrthographicCamera.h"
#include "Core/Timestep.h"

#include "Events/MouseEvent.h"
#include "Events/ApplicationEvent.h"

namespace XuanWu {

	class OrthographicCameraController
	{
	public:
		OrthographicCameraController(float aspectRatio, bool rotation = false);

		void OnUpdate(Timestep ts);
		void OnEvent(Event& event);

		OrthographicCamera& GetCamera() { return m_Camera; }
		const OrthographicCamera& GetCamera() const { return m_Camera; }
	private:
		bool OnMouseScrolled(MouseScrolledEvent& event);
		bool OnWindowResized(WindowResizeEvent& event);
	private:
		float m_AspectRatio;
		float m_ZoomLevel = 1.0f;

		bool m_Rotation;

		glm::vec3 m_CameraPosition = { 0.f, 0.f, 0.f };
		float m_CameraTranslationSpeed = 5.0f, m_CameraRotationSpeed = 20.0f;
		float m_CameraRotation = 0.0f;

		OrthographicCamera m_Camera;
	};
}