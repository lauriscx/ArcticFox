#include "Camera.h"
#include <glm/gtc/matrix_transform.hpp>

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
