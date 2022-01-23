#pragma once
#include "RenderCommand.h"
#include "Camera.h"
#include "Shader.h"

namespace Graphics {
	class Renderer {
	public:
		static void Init() {
			RenderCommand::Init();
		}

		static void BeginScene(OrthographicCamera& camera);

		static void Submit(Graphics::VertexArray* vertexArray, Graphics::Shader* shader, const glm::mat4& transformation = glm::mat4(1.0f));

		static void EndScene();
	private:
		struct SceneData {
			glm::mat4 m_ViewProjectionMatrix;
		};
		static SceneData* m_SceneData;
	};

}