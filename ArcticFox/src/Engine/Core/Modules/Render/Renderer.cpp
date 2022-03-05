#include "Renderer.h"

ArcticFox::Graphics::Renderer::SceneData* ArcticFox::Graphics::Renderer::m_SceneData = new Graphics::Renderer::SceneData();

void ArcticFox::Graphics::Renderer::BeginScene(OrthographicCamera& camera) {
	m_SceneData->m_Camera.ViewProjection = camera.GetViewProjectionMatrix();
}

void ArcticFox::Graphics::Renderer::BeginScene(EditorCamera & camera) {
	m_SceneData->m_Camera.ViewProjection = camera.GetViewProjection();
}

void ArcticFox::Graphics::Renderer::Submit(Graphics::VertexArray* vertexArray, const std::shared_ptr<Graphics::Shader>& shader, glm::mat4 transformation) {
	m_SceneData->m_CameraBuffer->SetData(&m_SceneData->m_Camera.ViewProjection, sizeof(SceneData::CameraData), 0);
	m_SceneData->m_TransformationBuffer->SetData(&transformation, sizeof(SceneData::TransformationData), 0);
	
	shader->Bind();
	vertexArray->Bind();
	RenderCommand::DrawIndexed(vertexArray, vertexArray->GetIndexBuffer()->getCount());
}

void ArcticFox::Graphics::Renderer::EndScene() {}