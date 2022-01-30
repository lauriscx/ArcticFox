#include "OrthographicCameraController.h"
#include "glfw3.h"

//Graphics::OrthographicCameraController::OrthographicCameraController() : m_AspectRatio(0.0f), m_camera(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel) {}
ArcticFox::Graphics::OrthographicCameraController::OrthographicCameraController(float aspectRatio) : m_AspectRatio(aspectRatio), m_camera(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel) { }
ArcticFox::Graphics::OrthographicCameraController::~OrthographicCameraController() { }

void ArcticFox::Graphics::OrthographicCameraController::OnUpdate(float deltaTime) {}

void ArcticFox::Graphics::OrthographicCameraController::OnEvent(AppFrame::BasicEvent* event) {
	if (auto resize = AppFrame::WindowResize::Match(event)) {
		m_AspectRatio = (float)resize->GetX() / (float)resize->GetY();
		m_camera.SetProjection(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel);
	}
	if (auto scroll = AppFrame::InputScroll::Match(event)) {
		m_ZoomLevel += scroll->GetY() * 0.2f;
		m_ZoomLevel = std::max(m_ZoomLevel, 0.25f);//Set max zoom
		m_CameraSpeed = m_ZoomLevel;
		m_camera.SetProjection(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel);
	}
}
bool ArcticFox::Graphics::OrthographicCameraController::OnInput(int x, int y, int action, int key) {
	if (action == GLFW_PRESS || GLFW_REPEAT) {
		if (key == GLFW_KEY_A) {
			m_Position.x -= m_CameraSpeed * 0.1f;
		}
		else if (key == GLFW_KEY_D) {
			m_Position.x += m_CameraSpeed * 0.1f;
		}

		if (key == GLFW_KEY_W) {
			m_Position.y += m_CameraSpeed * 0.1f;
		}
		else if (key == GLFW_KEY_S) {
			m_Position.y -= m_CameraSpeed * 0.1f;
		}

		if (key == GLFW_KEY_Q) {
			m_Rotation += m_RotationSpeed;
		}
		else if (key == GLFW_KEY_E) {
			m_Rotation -= m_RotationSpeed;
		}
		m_camera.SetPosition(m_Position);
		m_camera.SetRotation(m_Rotation);
	}
	return false;
}

ArcticFox::Graphics::OrthographicCamera & ArcticFox::Graphics::OrthographicCameraController::GetCamera() {
	return m_camera;
}

const ArcticFox::Graphics::OrthographicCamera & ArcticFox::Graphics::OrthographicCameraController::GetCamera() const {
	return m_camera;
}

