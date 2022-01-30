#include "Renderer.h"

Graphics::Renderer::SceneData* Graphics::Renderer::m_SceneData = new Graphics::Renderer::SceneData();

void Graphics::Renderer::BeginScene(OrthographicCamera& camera) {
	m_SceneData->m_ViewProjectionMatrix = camera.GetViewProjectionMatrix();
}

void Graphics::Renderer::Submit(Graphics::VertexArray* vertexArray, Graphics::Shader* shader, const glm::mat4& transformation) {

	shader->Bind();
	shader->UploadUniform("u_ViewPeojection", m_SceneData->m_ViewProjectionMatrix);
	shader->UploadUniform("u_Transform", transformation);
	shader->UploadUniform("u_Image", 0);
	
	vertexArray->Bind();
	RenderCommand::DrawIndexed(vertexArray);
}

void Graphics::Renderer::EndScene() {}