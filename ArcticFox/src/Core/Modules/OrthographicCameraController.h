#pragma once
#include <AppFrame.h>
#include "Render/Camera.h"

namespace Graphics {
	class OrthographicCameraController : AppFrame::InputHandler {
	public:
		//OrthographicCameraController();
		OrthographicCameraController(float aspectRatio);
		virtual ~OrthographicCameraController();

		void OnUpdate(float deltaTime);
		void OnEvent(AppFrame::BasicEvent* event);
		virtual bool OnInput(int x, int y, int action, int key) override;

		 OrthographicCamera& GetCamera();
		const OrthographicCamera& GetCamera() const;
	private:
		float m_AspectRatio;
		float m_ZoomLevel = 1.0f;

		OrthographicCamera m_camera;

		glm::vec3 m_Position = { 0.0f, 0.0f, 0.0f };
		float m_Rotation = 0.0f;

		float m_CameraSpeed = 0.1f;
		float m_RotationSpeed = 0.5f;
		// Inherited via InputHandler
	};
}