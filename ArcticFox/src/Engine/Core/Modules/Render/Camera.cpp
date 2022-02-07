#include "Camera.h"
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/quaternion.hpp>
#include <AppFrame.h>

ArcticFox::Graphics::OrthographicCamera::OrthographicCamera(float left, float right, float bottom, float top) : m_ViewMatrix(1.0f), m_Position({0.0f, 0.0f, 0.0f}) {
	m_ProjectionMatrix = glm::ortho(left, right, bottom, top, -1.0f, 1.0f);
	m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
}

void ArcticFox::Graphics::OrthographicCamera::SetProjection(float left, float right, float bottom, float top) {
	m_ProjectionMatrix = glm::ortho(left, right, bottom, top, -1.0f, 1.0f);
	m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
}

void ArcticFox::Graphics::OrthographicCamera::RecalculateViewMatrix() {
	glm::mat4 transform = glm::translate(glm::mat4(1.0f), m_Position) * glm::rotate(glm::mat4(1.0f), glm::radians(m_Rotation), glm::vec3(0, 0, 1));

	m_ViewMatrix = glm::inverse(transform);
	m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
}

void ArcticFox::Graphics::SceneCamera::SetOrthographic(float size, float near, float far) {
	m_ProjectionType = ProjectionType::Orthographic;

	m_OrthographicSize = size;
	m_OrthographicNear = near;
	m_OrthographicFar = far;

	RecalculateProjection();
}

void ArcticFox::Graphics::SceneCamera::SetPerspective(float fov, float near, float far) {
	m_ProjectionType = ProjectionType::Perspective;

	m_PerspectiveFOV = fov;
	m_PerspectivecFar = far;
	m_PerspectivecNear = near;

	RecalculateProjection();
}

void ArcticFox::Graphics::SceneCamera::SetViewPortSize(uint32_t width, uint32_t height) {
	m_AspectRation = (float)width / (float)height;
	RecalculateProjection();
}

void ArcticFox::Graphics::SceneCamera::RecalculateProjection() {
	if (m_ProjectionType == ProjectionType::Perspective) {
		m_ProjectionMatrix = glm::perspective(m_PerspectiveFOV, m_AspectRation, m_PerspectivecNear, m_PerspectivecFar);
	}
	else
	{
		float orthoLeft = -m_OrthographicSize * 0.5f * m_AspectRation;
		float orthoRight = m_OrthographicSize * 0.5f * m_AspectRation;
		float orthoBottom = -m_OrthographicSize * 0.5f;
		float orthoTop = m_OrthographicSize * 0.5f;

		m_ProjectionMatrix = glm::ortho(orthoLeft, orthoRight, orthoBottom, orthoTop, m_OrthographicNear, m_OrthographicFar);
	}
}

ArcticFox::Graphics::EditorCamera::EditorCamera(float fov, float aspectRatio, float near, float far) : m_FOV(fov), m_AspectRatio(aspectRatio), m_NearClip(near), m_FarClip(far)
{
	UpdateView();
}

void ArcticFox::Graphics::EditorCamera::OnUpdate(float deltaTime)
{
	if (AppFrame::InputManager::GetInstance()->IsKeyPressed(AppFrame::Key::KEY_LEFT_ALT)) {
		const glm::vec2& mouse{ AppFrame::InputManager::GetInstance()->GetMousePosition().first, AppFrame::InputManager::GetInstance()->GetMousePosition().second };
		glm::vec2 delta = (mouse - m_InitialMousePosition) * 0.003f;
		m_InitialMousePosition = mouse;

		if (AppFrame::InputManager::GetInstance()->IsButtonPressed((AppFrame::Key)2)) {
			MousePan(delta);
		} else if (AppFrame::InputManager::GetInstance()->IsButtonPressed((AppFrame::Key)0)) {
			MouseRotate(delta);
		} else if (AppFrame::InputManager::GetInstance()->IsButtonPressed((AppFrame::Key)1)) {
			MouseZoom(delta.y);
		}
	}
	UpdateView();
}

void ArcticFox::Graphics::EditorCamera::OnEvent(AppFrame::BasicEvent * event) {
	if (auto scroll = AppFrame::InputScroll::Match(event)) {
		float delta = scroll->GetY();
		MouseZoom(delta);
		UpdateView();
	}
}

glm::vec3 ArcticFox::Graphics::EditorCamera::GetUpDirection() const
{
	return glm::rotate(GetOrentation(), glm::vec3(0.0f, 1.0f, 0.0f));
}

glm::vec3 ArcticFox::Graphics::EditorCamera::GetRightDirection() const
{
	return glm::rotate(GetOrentation(), glm::vec3(1.0f, 0.0f, 0.0f));
}

glm::vec3 ArcticFox::Graphics::EditorCamera::GetForwardDirection() const
{
	return glm::rotate(GetOrentation(), glm::vec3(0.0f, 0.0f, -1.0f));
}

glm::quat ArcticFox::Graphics::EditorCamera::GetOrentation() const
{
	return glm::quat(glm::vec3(-m_Pitch, -m_Yaw, 0.0f));
}

void ArcticFox::Graphics::EditorCamera::UpdateProjection()
{
	m_AspectRatio = m_ViewportWidth / m_ViewportHeight;
	m_ProjectionMatrix = glm::perspective(glm::radians(m_FOV), m_AspectRatio, m_NearClip, m_FarClip);
}

void ArcticFox::Graphics::EditorCamera::UpdateView()
{
	m_Position = CalculatePosition();

	glm::quat orientation = GetOrentation();
	m_ViewMatrix = glm::translate(glm::mat4(1.0f), m_Position) * glm::toMat4(orientation);
	m_ViewMatrix = glm::inverse(m_ViewMatrix);
}

void ArcticFox::Graphics::EditorCamera::MousePan(const glm::vec2 & delta)
{
	auto[xSpeed, ySpeed] = PanSpeed();
	m_FocalPoint += -GetRightDirection() * delta.x * xSpeed * m_Distance;
	m_FocalPoint += GetUpDirection() * delta.y * ySpeed * m_Distance;

}

void ArcticFox::Graphics::EditorCamera::MouseRotate(const glm::vec2 & delta)
{
	float yawSign = GetUpDirection().y < 0 ? -1.0f : 1.0f;
	m_Yaw += yawSign * delta.x * RotationSpeed();
	m_Pitch += delta.y * RotationSpeed();
}

void ArcticFox::Graphics::EditorCamera::MouseZoom(float delta)
{
	m_Distance -= delta * ZoomSpeed();
	if (m_Distance < 1.0f) {
		m_FocalPoint += GetForwardDirection();
		m_Distance = 1.0f;
	}
}

glm::vec3 ArcticFox::Graphics::EditorCamera::CalculatePosition() const
{
	return m_FocalPoint - GetForwardDirection() * m_Distance;
}

std::pair<float, float> ArcticFox::Graphics::EditorCamera::PanSpeed() const
{
	float x = std::min(m_ViewportWidth / 1000.0f, 2.4f);
	float xFactor = 0.0366f * (x * x) - 0.1778f * x + 0.3021f;

	float y = std::min(m_ViewportHeight / 1000.0f, 2.4f);
	float yFactor = 0.0366f * (y * y) - 0.1778f * y + 0.3021f;

	return { xFactor, yFactor };
}

float ArcticFox::Graphics::EditorCamera::RotationSpeed() const
{
	return 0.8f;
}

float ArcticFox::Graphics::EditorCamera::ZoomSpeed() const
{
	float distance = m_Distance * 0.2f;
	distance = std::max(distance, 0.0f);
	float speed = distance * distance;
	speed = std::min(speed, 100.0f);
	return speed;
}
