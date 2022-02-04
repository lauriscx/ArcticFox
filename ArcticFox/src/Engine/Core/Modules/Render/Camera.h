#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

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
			enum class ProjectionType {
				Perspective = 0,
				Orthographic = 1
			};
		public:
			SceneCamera() { RecalculateProjection(); }
			virtual ~SceneCamera() = default;

			void SetOrthographic(float size, float near, float far);
			void SetPerspective(float fov, float near, float far);
			void SetViewPortSize(uint32_t width, uint32_t height);

			float GetOrthoGraphicSize() const { return m_OrthographicSize; }
			void SetOrthoGraphicSize(float size) { m_OrthographicSize = size; RecalculateProjection(); }
			ProjectionType GetProjectionType() const { return m_ProjectionType; }
			void SetProjectionType(ProjectionType type) { m_ProjectionType = type; RecalculateProjection(); }

			float GetOrthoNearClipt() const { return m_OrthographicNear; }
			float GetOrthoFarClipt() const { return m_OrthographicFar; }

			void SetOrthographicNearClip(float Near) { m_OrthographicNear = Near; RecalculateProjection(); }
			void SetOrthographicFarClip(float far) { m_OrthographicFar = far; RecalculateProjection(); }

			float GetPerspectiveNearClipt() const { return m_PerspectivecNear; }
			float GetPerspectiveFarClipt() const { return m_PerspectivecFar; }
			float GetPerspectiveFOV() const { return m_PerspectiveFOV; }

			void SetPerspectiveFOV(float fow) { m_PerspectiveFOV = fow; RecalculateProjection(); }
			void SetPerspectiveNearClip(float Near) { m_PerspectivecNear = Near; RecalculateProjection(); }
			void SetPerspectiveFarClip(float far) { m_PerspectivecFar = far; RecalculateProjection(); }

		private:
			void RecalculateProjection();
			
		private:
			ProjectionType m_ProjectionType = ProjectionType::Perspective;
			float m_OrthographicSize = 10.0f;
			float m_OrthographicNear = -1.0f;
			float m_OrthographicFar = 1.0f;

			float m_PerspectiveFOV = glm::radians(45.0f);
			float m_PerspectivecNear = 0.01f;
			float m_PerspectivecFar = 100.0f;

			float m_AspectRation = 0;
		};

		class EditorCamera : public Camera {
		public: 
			EditorCamera() = default;
			EditorCamera(float fov, float aspectRatio, float near, float far);

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