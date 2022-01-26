#include "Render2D.h"
#include "Buffer.h"
#include "Shader.h"
#include "Texture.h"
#include "RenderCommand.h"

#include <glm/gtc/matrix_transform.hpp>

namespace Graphics {
	struct Render2DStorage {
		VertexArray* m_VAO;
		Shader* m_Shader;
		Texture2D* m_Texture;
	};
	static Render2DStorage* s_2DRenderData;
}

void Graphics::Render2D::Init() {
	s_2DRenderData = new Render2DStorage();

	float square[5 * 4] = {
		-0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
		 0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
		 0.5f,  0.5f, 0.0f, 1.0f, 1.0f,
		-0.5f,  0.5f, 0.0f, 0.0f, 1.0f
	};

	uint32_t indices[6] = { 0, 1, 2, 2, 3, 0 };

	std::string Vertex =
		"#version 330 core\n"
		"layout(location = 0) in vec3 position;\n"
		"layout(location = 1) in vec2 Coords;\n"
		"uniform mat4 u_ViewPeojection;\n"
		"uniform mat4 u_Transform;\n"
		"out vec2 p_Coords;\n"
		"void main() {\n"
		"	p_Coords = Coords;\n"
		"	gl_Position = u_ViewPeojection * u_Transform * vec4(position, 1.0);\n"
		"}";

	std::string Fragment =
		"#version 330 core\n"
		"uniform vec4 u_color;\n"
		"uniform sampler2D u_texture;\n"
		"in vec2 p_Coords;\n"
		"out vec4 color;\n"
		"void main() {\n"
		"	color = texture(u_texture, p_Coords) * u_color;\n"
		"}";

	s_2DRenderData->m_Texture = Texture2D::Create(1, 1);
	uint32_t white = 0xfffffffff;
	s_2DRenderData->m_Texture->SetData(&white, sizeof(white));

	auto vertex = VertexBuffer::Create(square, sizeof(square));
	vertex->SetLayout({ {"position", DataType::FLOAT_3}, {"Coords", DataType::FLOAT_2} });

	s_2DRenderData->m_VAO = VertexArray::Create();
	s_2DRenderData->m_VAO->AddVertexBuffer(vertex);
	s_2DRenderData->m_VAO->SetIndexBuffer(IndexBuffer::Create(indices, sizeof(indices)));
	s_2DRenderData->m_Shader = Shader::Create("2DShader", Vertex, Fragment);
	s_2DRenderData->m_Shader->UploadUniform("u_texture", 0);
}

void Graphics::Render2D::BeginScene(const OrthographicCamera & camera) {
	s_2DRenderData->m_Shader->Bind();
	s_2DRenderData->m_Shader->UploadUniform("u_ViewPeojection", camera.GetViewProjectionMatrix());
	s_2DRenderData->m_VAO->Bind();
}

void Graphics::Render2D::DrawQuad(const glm::vec2 & position, const glm::vec2 & size, const glm::vec4 & color) {
	glm::mat4 transformation = glm::translate(glm::mat4(1.0f), glm::vec3(position.x, position.y, 1.0f)) * glm::scale(glm::mat4(1.0f), glm::vec3(size.x, size.y, 1.0f));

	s_2DRenderData->m_Shader->UploadUniform("u_color", color);
	s_2DRenderData->m_Shader->UploadUniform("u_Transform", transformation);
	s_2DRenderData->m_VAO->Bind();

	s_2DRenderData->m_Texture->Bind();

	RenderCommand::DrawIndexed(s_2DRenderData->m_VAO);
}

void Graphics::Render2D::DrawQuad(const glm::vec3 & position, const glm::vec2 & size, const glm::vec4 & color) {
	glm::mat4 transformation = glm::translate(glm::mat4(1.0f), position) * glm::scale(glm::mat4(1.0f), glm::vec3(size.x, size.y, 1.0f));

	s_2DRenderData->m_Shader->UploadUniform("u_color", glm::vec4(color.r, color.g, color.b, 1.0f));
	s_2DRenderData->m_Shader->UploadUniform("u_Transform", transformation);
	s_2DRenderData->m_VAO->Bind();

	s_2DRenderData->m_Texture->Bind();

	RenderCommand::DrawIndexed(s_2DRenderData->m_VAO);
}

void Graphics::Render2D::DrawQuad(const glm::vec2 & position, const glm::vec2 & size, Texture * texture) {
	glm::mat4 transformation = glm::translate(glm::mat4(1.0f), glm::vec3(position.x, position.y, 1.0f)) * glm::scale(glm::mat4(1.0f), glm::vec3(size.x, size.y, 1.0f));

	s_2DRenderData->m_Shader->UploadUniform("u_color", glm::vec4(1.0f));
	s_2DRenderData->m_Shader->UploadUniform("u_Transform", transformation);
	s_2DRenderData->m_VAO->Bind();

	texture->Bind();

	RenderCommand::DrawIndexed(s_2DRenderData->m_VAO);
}

void Graphics::Render2D::DrawQuad(const glm::vec3 & position, const glm::vec2 & size, Texture * texture) {
	glm::mat4 transformation = glm::translate(glm::mat4(1.0f), position) * glm::scale(glm::mat4(1.0f), glm::vec3(size.x, size.y, 1.0f));

	s_2DRenderData->m_Shader->UploadUniform("u_color", glm::vec4(1.0f));
	s_2DRenderData->m_Shader->UploadUniform("u_Transform", transformation);
	s_2DRenderData->m_VAO->Bind();
	
	texture->Bind();

	RenderCommand::DrawIndexed(s_2DRenderData->m_VAO);
}

void Graphics::Render2D::DrawQuad(const glm::vec2 & position, const glm::vec2 & size, const glm::vec4 & color, Texture * texture) {
	glm::mat4 transformation = glm::translate(glm::mat4(1.0f), glm::vec3(position.x, position.y, 1.0f)) * glm::scale(glm::mat4(1.0f), glm::vec3(size.x, size.y, 1.0f));

	s_2DRenderData->m_Shader->UploadUniform("u_color", glm::vec4(color.r, color.g, color.b, 1.0f));
	s_2DRenderData->m_Shader->UploadUniform("u_Transform", transformation);
	s_2DRenderData->m_VAO->Bind();

	texture->Bind();

	RenderCommand::DrawIndexed(s_2DRenderData->m_VAO);
}

void Graphics::Render2D::DrawQuad(const glm::vec3 & position, const glm::vec2 & size, const glm::vec4 & color, Texture * texture) {
	glm::mat4 transformation = glm::translate(glm::mat4(1.0f), position) * glm::scale(glm::mat4(1.0f), glm::vec3(size.x, size.y, 1.0f));

	s_2DRenderData->m_Shader->UploadUniform("u_color", glm::vec4(color.r, color.g, color.b, 1.0f));
	s_2DRenderData->m_Shader->UploadUniform("u_Transform", transformation);
	s_2DRenderData->m_VAO->Bind();

	texture->Bind();

	RenderCommand::DrawIndexed(s_2DRenderData->m_VAO);
}

void Graphics::Render2D::EndScene() {
	s_2DRenderData->m_Shader->Unbind();
	s_2DRenderData->m_VAO->Unbind();
}

void Graphics::Render2D::ShutDown() {
	delete s_2DRenderData->m_Shader;
	delete s_2DRenderData->m_VAO;
	delete s_2DRenderData;
}
