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
			}

			static void BeginScene(OrthographicCamera& camera);
			static void SetViewPort(glm::vec4 size) { RenderCommand::SetViewPort(size); }

			static void Submit(Graphics::VertexArray* vertexArray, Graphics::Shader* shader, const glm::mat4& transformation = glm::mat4(1.0f));

			static void EndScene();
		private:
			struct SceneData {
				glm::mat4 m_ViewProjectionMatrix;
			};
			static SceneData* m_SceneData;
		};

	}
}