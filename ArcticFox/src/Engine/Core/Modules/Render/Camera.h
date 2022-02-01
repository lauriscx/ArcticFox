#pragma once
#include <glm/glm.hpp>

namespace ArcticFox {
	namespace Graphics {
		class Camera {
		public:
			Camera() = default;
			Camera(const glm::mat4& projection) : m_ProjectionMatrix(projection) {}
			const glm::mat4& GetProjectionMatrix() const { return m_ProjectionMatrix; }
			virtual ~Camera() = default;

		protected:
			glm::mat4 m_ProjectionMatrix = glm::mat4(1.0f);
		};

		class SceneCamera : public Camera {
		public:
			SceneCamera() { RecalculateProjection(); }
			virtual ~SceneCamera() = default;

			void SetOrthographic(float size, float near, float far);
			void SetViewPortSize(uint32_t width, uint32_t height);

			float GetOrthoGraphicSize() const { return m_OrthographicSize; }
			void SetOrthoGraphicSize(float size) { m_OrthographicSize = size; RecalculateProjection(); }

		private:
			void RecalculateProjection();
			float m_OrthographicSize = 10.0f;
			float m_OrthographicNear = -1.0f;
			float m_OrthographicFar = 1.0f;

			float m_AspectRation = 0;
		};

		class OrthographicCamera : public Camera {
		public:
			//OrthographicCamera() {}
			OrthographicCamera(float left, float right, float bottom, float top);
			void SetProjection(float left, float right, float bottom, float top);

			void SetPosition(const glm::vec3& position) { m_Position = position; RecalculateViewMatrix(); }
			void SetRotation(float rotation) { m_Rotation = rotation;  RecalculateViewMatrix(); }

			const glm::vec3& GetPosition() const { return m_Position; }
			float GetRotation() const { return m_Rotation; }

			
			const glm::mat4& GetViewMatrix() const { return m_ViewMatrix; }
			const glm::mat4& GetViewProjectionMatrix() const { return m_ViewProjectionMatrix; }

			~OrthographicCamera() {}
		private:
			void RecalculateViewMatrix();

		private:
			glm::mat4 m_ViewMatrix;
			glm::mat4 m_ViewProjectionMatrix;

			glm::vec3 m_Position;
			float m_Rotation = 0.0f;
		};
	}
}