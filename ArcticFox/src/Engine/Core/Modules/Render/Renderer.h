#pragma once
#include "RenderCommand.h"
#include "Camera.h"
#include "Shader.h"
#include "Render2D.h"

namespace ArcticFox {
	namespace Graphics {
		class Renderer {
		public:
			static void Init() {
				RenderCommand::Init();
				Render2D::Init();
				m_SceneData->m_CameraBuffer = UniformBuffer::Create(sizeof(SceneData::CameraData), 1);
				m_SceneData->m_TransformationBuffer = UniformBuffer::Create(sizeof(SceneData::TransformationData), 2);
			}

			static void BeginScene(OrthographicCamera& camera);
			static void BeginScene(EditorCamera& camera);
			static void SetViewPort(glm::vec4 size) { RenderCommand::SetViewPort(size); }

			static void Submit(Graphics::VertexArray* vertexArray, const std::shared_ptr<Graphics::Shader>& shader, glm::mat4 transformation = glm::mat4(1.0f));

			static void EndScene();
		private:
			struct SceneData {
				struct CameraData {
					glm::mat4 ViewProjection;
				} m_Camera;
				UniformBuffer* m_CameraBuffer;

				struct TransformationData {
					glm::mat4 ViewProjection;
				} m_Transformation;
				UniformBuffer* m_TransformationBuffer;
			};
			static SceneData* m_SceneData;
		};

	}
}