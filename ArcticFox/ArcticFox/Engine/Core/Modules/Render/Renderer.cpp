#include "Renderer.h"

void Graphics::Renderer::BeginScene() {}

void Graphics::Renderer::Submit(Graphics::VertexArray* vertexArray) {
	vertexArray->Bind();
	RenderCommand::DrawIndexed(vertexArray);
}

void Graphics::Renderer::EndScene() {}