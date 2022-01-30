#include "Render2D.h"
#include "Buffer.h"
#include "Shader.h"
#include "Texture.h"
#include "RenderCommand.h"

#include <array>
#include <glm/gtc/matrix_transform.hpp>

namespace ArcticFox {
	namespace Graphics {
		struct QuadVertex {
			glm::vec3 Position;
			glm::vec4 Color;
			glm::vec2 TexCoord;
			float ImageIndex;
		};

		struct Render2DCache {
			static const uint32_t maxQuads = 1000;
			static const uint32_t maxVertices = maxQuads * 4;
			static const uint32_t maxIndices = maxQuads * 6;
			static const uint32_t maxTextureSlots = 32;

			uint32_t QuadIndexCount = 0;

			QuadVertex* QuadVertexBase = nullptr;
			QuadVertex* QuadVertexPtr = nullptr;

			VertexArray* m_VAO;
			VertexBuffer* m_VBO;
			Shader* m_Shader;

			std::array<Texture*, maxTextureSlots> TextureSlots;
			uint32_t TextureSlotIndex = 1;

			Texture2D* m_Texture;

			glm::vec4 QoudPositionTemplate[4] = { {-0.5f, -0.5f, 0.0f, 1.0f}, {0.5f, -0.5f, 0.0f, 1.0f}, {0.5f, 0.5f, 0.0f, 1.0f}, {-0.5f, 0.5f, 0.0f, 1.0f} };

			Render2D::Statistics m_Statistics;
		};
		static Render2DCache* s_2DRenderData;
	}
}

void ArcticFox::Graphics::Render2D::Init() {
	s_2DRenderData = new Render2DCache();

	s_2DRenderData->QuadVertexBase = new QuadVertex[s_2DRenderData->maxVertices];

	s_2DRenderData->m_VAO = VertexArray::Create();
	s_2DRenderData->m_VBO = VertexBuffer::Create(sizeof(QuadVertex) * s_2DRenderData->maxVertices);
	s_2DRenderData->m_VBO->SetLayout({	{"b_Position", DataType::FLOAT_3},
										{"b_Color", DataType::FLOAT_4},
										{"b_Coords", DataType::FLOAT_2},
										{"b_TextIndex", DataType::FLOAT_1} });

	s_2DRenderData->m_VAO->AddVertexBuffer(s_2DRenderData->m_VBO);

	uint32_t* qaudIndices = new uint32_t[s_2DRenderData->maxIndices];

	uint32_t offset = 0;
	for (uint32_t i = 0; i < s_2DRenderData->maxIndices; i += 6) {
		qaudIndices[i + 0] = offset + 0;
		qaudIndices[i + 1] = offset + 1;
		qaudIndices[i + 2] = offset + 2;

		qaudIndices[i + 3] = offset + 2;
		qaudIndices[i + 4] = offset + 3;
		qaudIndices[i + 5] = offset + 0;

		offset += 4;
	}

	s_2DRenderData->m_VAO->SetIndexBuffer(IndexBuffer::Create(qaudIndices, s_2DRenderData->maxIndices));

	delete[] qaudIndices;

	std::string Vertex =
		"#version 330 core\n"
		"layout(location = 0) in vec3 b_Position;\n"
		"layout(location = 1) in vec4 b_Color;\n"
		"layout(location = 2) in vec2 b_Coords;\n"
		"layout(location = 3) in float b_TextIndex;\n"
		"uniform mat4 u_ViewPeojection;\n"
		"out vec2 p_Coords;\n"
		"out vec4 p_Color;\n"
		"out float p_TextIndex;\n"
		"void main() {\n"
		"	p_Coords = b_Coords;\n"
		"	p_Color = b_Color;\n"
		"	p_TextIndex = b_TextIndex;\n"
		"	gl_Position = u_ViewPeojection * vec4(b_Position, 1.0);\n"
		"}";

	std::string Fragment =
		"#version 330 core\n"
		"uniform vec4 u_color;\n"
		"uniform sampler2D u_texture[32];\n"
		"in vec2 p_Coords;\n"
		"in vec4 p_Color;\n"
		"in float p_TextIndex;\n"
		"out vec4 color;\n"
		"void main() {\n"
		"	color = texture(u_texture[int(p_TextIndex)], p_Coords) * p_Color;\n"
		"}";

	s_2DRenderData->m_Texture = Texture2D::Create(1, 1);
	uint32_t white = 0xfffffffff;
	s_2DRenderData->m_Texture->SetData(&white, sizeof(white));
	s_2DRenderData->TextureSlots[0] = s_2DRenderData->m_Texture;

	s_2DRenderData->m_Shader = Shader::Create("2DShader", Vertex, Fragment);

	int samplers[s_2DRenderData->maxTextureSlots];
	for (uint32_t i = 0; i < s_2DRenderData->maxTextureSlots; i++) {
		samplers[i] = i;
	}

	s_2DRenderData->m_Shader->UploadUniform("u_texture", samplers, s_2DRenderData->maxTextureSlots);

}

void ArcticFox::Graphics::Render2D::BeginScene(const OrthographicCamera & camera) {
	s_2DRenderData->m_Shader->Bind();
	s_2DRenderData->m_Shader->UploadUniform("u_ViewPeojection", camera.GetViewProjectionMatrix());
	s_2DRenderData->TextureSlotIndex = 1;
	s_2DRenderData->QuadIndexCount = 0;
	s_2DRenderData->QuadVertexPtr = s_2DRenderData->QuadVertexBase;
}

void ArcticFox::Graphics::Render2D::DrawQuad(const glm::mat4 matrix, const glm::vec4 & color) {
	if (s_2DRenderData->QuadIndexCount >= Render2DCache::maxIndices) {
		EndScene();
	}

	int TextureIndex = 0;

	s_2DRenderData->QuadVertexPtr->Position = matrix * s_2DRenderData->QoudPositionTemplate[0];
	s_2DRenderData->QuadVertexPtr->Color = color;
	s_2DRenderData->QuadVertexPtr->TexCoord = { 0.0f, 0.0f };
	s_2DRenderData->QuadVertexPtr->ImageIndex = TextureIndex;
	s_2DRenderData->QuadVertexPtr++;

	s_2DRenderData->QuadVertexPtr->Position = matrix * s_2DRenderData->QoudPositionTemplate[1];
	s_2DRenderData->QuadVertexPtr->Color = color;
	s_2DRenderData->QuadVertexPtr->TexCoord = { 1.0f, 0.0f };
	s_2DRenderData->QuadVertexPtr->ImageIndex = TextureIndex;
	s_2DRenderData->QuadVertexPtr++;

	s_2DRenderData->QuadVertexPtr->Position = matrix * s_2DRenderData->QoudPositionTemplate[2];
	s_2DRenderData->QuadVertexPtr->Color = color;
	s_2DRenderData->QuadVertexPtr->TexCoord = { 1.0f, 1.0f };
	s_2DRenderData->QuadVertexPtr->ImageIndex = TextureIndex;
	s_2DRenderData->QuadVertexPtr++;

	s_2DRenderData->QuadVertexPtr->Position = matrix * s_2DRenderData->QoudPositionTemplate[3];
	s_2DRenderData->QuadVertexPtr->Color = color;
	s_2DRenderData->QuadVertexPtr->TexCoord = { 0.0f, 1.0f };
	s_2DRenderData->QuadVertexPtr->ImageIndex = TextureIndex;
	s_2DRenderData->QuadVertexPtr++;

	s_2DRenderData->QuadIndexCount += 6;

	s_2DRenderData->m_Statistics.m_QuodCount++;
}

void ArcticFox::Graphics::Render2D::DrawQuad(const glm::vec2 & position, const glm::vec2 & size, const glm::vec4 & color) {
	if (s_2DRenderData->QuadIndexCount >= Render2DCache::maxIndices) {
		EndScene();
	}

	int TextureIndex = 0;
	glm::mat4 transform = glm::translate(glm::mat4(1.0f), glm::vec3(position.x, position.y, 0.0f)) * glm::scale(glm::mat4(1.0f), glm::vec3(size.x, size.y, 1.0f));

	s_2DRenderData->QuadVertexPtr->Position = transform * s_2DRenderData->QoudPositionTemplate[0];
	s_2DRenderData->QuadVertexPtr->Color = color;
	s_2DRenderData->QuadVertexPtr->TexCoord = { 0.0f, 0.0f };
	s_2DRenderData->QuadVertexPtr->ImageIndex = TextureIndex;
	s_2DRenderData->QuadVertexPtr++;

	s_2DRenderData->QuadVertexPtr->Position = transform * s_2DRenderData->QoudPositionTemplate[1];
	s_2DRenderData->QuadVertexPtr->Color = color;
	s_2DRenderData->QuadVertexPtr->TexCoord = { 1.0f, 0.0f };
	s_2DRenderData->QuadVertexPtr->ImageIndex = TextureIndex;
	s_2DRenderData->QuadVertexPtr++;

	s_2DRenderData->QuadVertexPtr->Position = transform * s_2DRenderData->QoudPositionTemplate[2];
	s_2DRenderData->QuadVertexPtr->Color = color;
	s_2DRenderData->QuadVertexPtr->TexCoord = { 1.0f, 1.0f };
	s_2DRenderData->QuadVertexPtr->ImageIndex = TextureIndex;
	s_2DRenderData->QuadVertexPtr++;

	s_2DRenderData->QuadVertexPtr->Position = transform * s_2DRenderData->QoudPositionTemplate[3];
	s_2DRenderData->QuadVertexPtr->Color = color;
	s_2DRenderData->QuadVertexPtr->TexCoord = { 0.0f, 1.0f };
	s_2DRenderData->QuadVertexPtr->ImageIndex = TextureIndex;
	s_2DRenderData->QuadVertexPtr++;

	s_2DRenderData->QuadIndexCount += 6;

	s_2DRenderData->m_Statistics.m_QuodCount++;
}

void ArcticFox::Graphics::Render2D::DrawQuad(const glm::vec3 & position, const glm::vec2 & size, const glm::vec4 & color) {
	if (s_2DRenderData->QuadIndexCount >= Render2DCache::maxIndices) {
		EndScene();
	}

	int TextureIndex = 0;

	glm::mat4 transform = glm::translate(glm::mat4(1.0f), glm::vec3(position.x, position.y, 0.0f)) * glm::scale(glm::mat4(1.0f), glm::vec3(size.x, size.y, 1.0f));

	s_2DRenderData->QuadVertexPtr->Position = transform * s_2DRenderData->QoudPositionTemplate[0];
	s_2DRenderData->QuadVertexPtr->Color = color;
	s_2DRenderData->QuadVertexPtr->TexCoord = { 0.0f, 0.0f };
	s_2DRenderData->QuadVertexPtr->ImageIndex = TextureIndex;
	s_2DRenderData->QuadVertexPtr++;

	s_2DRenderData->QuadVertexPtr->Position = transform * s_2DRenderData->QoudPositionTemplate[1];
	s_2DRenderData->QuadVertexPtr->Color = color;
	s_2DRenderData->QuadVertexPtr->TexCoord = { 1.0f, 0.0f };
	s_2DRenderData->QuadVertexPtr->ImageIndex = TextureIndex;
	s_2DRenderData->QuadVertexPtr++;

	s_2DRenderData->QuadVertexPtr->Position = transform * s_2DRenderData->QoudPositionTemplate[2];
	s_2DRenderData->QuadVertexPtr->Color = color;
	s_2DRenderData->QuadVertexPtr->TexCoord = { 1.0f, 1.0f };
	s_2DRenderData->QuadVertexPtr->ImageIndex = TextureIndex;
	s_2DRenderData->QuadVertexPtr++;

	s_2DRenderData->QuadVertexPtr->Position = transform * s_2DRenderData->QoudPositionTemplate[3];
	s_2DRenderData->QuadVertexPtr->Color = color;
	s_2DRenderData->QuadVertexPtr->TexCoord = { 0.0f, 1.0f };
	s_2DRenderData->QuadVertexPtr->ImageIndex = TextureIndex;
	s_2DRenderData->QuadVertexPtr++;

	s_2DRenderData->QuadIndexCount += 6;

	s_2DRenderData->m_Statistics.m_QuodCount++;
}

void ArcticFox::Graphics::Render2D::DrawQuad(const glm::vec2 & position, const glm::vec2 & size, Texture * texture) {
	if (s_2DRenderData->QuadIndexCount >= Render2DCache::maxIndices) {
		EndScene();
	}

	int TextureIndex = 0;
	for (uint32_t i = 1; i < s_2DRenderData->TextureSlotIndex; i++) {
		if (texture == s_2DRenderData->TextureSlots[i]) {
			TextureIndex = i;
			break;
		}
	}
	if (TextureIndex == 0) {
		TextureIndex = s_2DRenderData->TextureSlotIndex;
		s_2DRenderData->TextureSlots[TextureIndex] = texture;
		s_2DRenderData->TextureSlotIndex++;
	}

	glm::vec4 color(1.0f);

	glm::mat4 transform = glm::translate(glm::mat4(1.0f), glm::vec3(position.x, position.y, 0.0f)) * glm::scale(glm::mat4(1.0f), glm::vec3(size.x, size.y, 1.0f));

	s_2DRenderData->QuadVertexPtr->Position = transform * s_2DRenderData->QoudPositionTemplate[0];
	s_2DRenderData->QuadVertexPtr->Color = color;
	s_2DRenderData->QuadVertexPtr->TexCoord = { 0.0f, 0.0f };
	s_2DRenderData->QuadVertexPtr->ImageIndex = TextureIndex;
	s_2DRenderData->QuadVertexPtr++;

	s_2DRenderData->QuadVertexPtr->Position = transform * s_2DRenderData->QoudPositionTemplate[1];
	s_2DRenderData->QuadVertexPtr->Color = color;
	s_2DRenderData->QuadVertexPtr->TexCoord = { 1.0f, 0.0f };
	s_2DRenderData->QuadVertexPtr->ImageIndex = TextureIndex;
	s_2DRenderData->QuadVertexPtr++;

	s_2DRenderData->QuadVertexPtr->Position = transform * s_2DRenderData->QoudPositionTemplate[2];
	s_2DRenderData->QuadVertexPtr->Color = color;
	s_2DRenderData->QuadVertexPtr->TexCoord = { 1.0f, 1.0f };
	s_2DRenderData->QuadVertexPtr->ImageIndex = TextureIndex;
	s_2DRenderData->QuadVertexPtr++;

	s_2DRenderData->QuadVertexPtr->Position = transform * s_2DRenderData->QoudPositionTemplate[3];
	s_2DRenderData->QuadVertexPtr->Color = color;
	s_2DRenderData->QuadVertexPtr->TexCoord = { 0.0f, 1.0f };
	s_2DRenderData->QuadVertexPtr->ImageIndex = TextureIndex;
	s_2DRenderData->QuadVertexPtr++;

	s_2DRenderData->QuadIndexCount += 6;

	s_2DRenderData->m_Statistics.m_QuodCount++;
}

void ArcticFox::Graphics::Render2D::DrawQuad(const glm::vec3 & position, const glm::vec2 & size, Texture * texture) {
	if (s_2DRenderData->QuadIndexCount >= Render2DCache::maxIndices) {
		EndScene();
	}

	int TextureIndex = 0;
	for (uint32_t i = 1; i < s_2DRenderData->TextureSlotIndex; i++) {
		if (texture == s_2DRenderData->TextureSlots[i]) {
			TextureIndex = i;
			break;
		}
	}
	if (TextureIndex == 0) {
		TextureIndex = s_2DRenderData->TextureSlotIndex;
		s_2DRenderData->TextureSlots[TextureIndex] = texture;
		s_2DRenderData->TextureSlotIndex++;
	}

	glm::vec4 color(1.0f);

	glm::mat4 transform = glm::translate(glm::mat4(1.0f), glm::vec3(position.x, position.y, 0.0f)) * glm::scale(glm::mat4(1.0f), glm::vec3(size.x, size.y, 1.0f));

	s_2DRenderData->QuadVertexPtr->Position = transform * s_2DRenderData->QoudPositionTemplate[0];
	s_2DRenderData->QuadVertexPtr->Color = color;
	s_2DRenderData->QuadVertexPtr->TexCoord = { 0.0f, 0.0f };
	s_2DRenderData->QuadVertexPtr->ImageIndex = TextureIndex;
	s_2DRenderData->QuadVertexPtr++;

	s_2DRenderData->QuadVertexPtr->Position = transform * s_2DRenderData->QoudPositionTemplate[1];
	s_2DRenderData->QuadVertexPtr->Color = color;
	s_2DRenderData->QuadVertexPtr->TexCoord = { 1.0f, 0.0f };
	s_2DRenderData->QuadVertexPtr->ImageIndex = TextureIndex;
	s_2DRenderData->QuadVertexPtr++;

	s_2DRenderData->QuadVertexPtr->Position = transform * s_2DRenderData->QoudPositionTemplate[2];
	s_2DRenderData->QuadVertexPtr->Color = color;
	s_2DRenderData->QuadVertexPtr->TexCoord = { 1.0f, 1.0f };
	s_2DRenderData->QuadVertexPtr->ImageIndex = TextureIndex;
	s_2DRenderData->QuadVertexPtr++;

	s_2DRenderData->QuadVertexPtr->Position = transform * s_2DRenderData->QoudPositionTemplate[3];
	s_2DRenderData->QuadVertexPtr->Color = color;
	s_2DRenderData->QuadVertexPtr->TexCoord = { 0.0f, 1.0f };
	s_2DRenderData->QuadVertexPtr->ImageIndex = TextureIndex;
	s_2DRenderData->QuadVertexPtr++;

	s_2DRenderData->QuadIndexCount += 6;

	s_2DRenderData->m_Statistics.m_QuodCount++;
}

void ArcticFox::Graphics::Render2D::DrawQuad(const glm::vec2 & position, const glm::vec2 & size, const glm::vec4 & color, Texture * texture) {
	if (s_2DRenderData->QuadIndexCount >= Render2DCache::maxIndices) {
		EndScene();
	}

	int TextureIndex = 0;
	for (uint32_t i = 1; i < s_2DRenderData->TextureSlotIndex; i++) {
		if (texture == s_2DRenderData->TextureSlots[i]) {
			TextureIndex = i;
			break;
		}
	}
	if (TextureIndex == 0) {
		TextureIndex = s_2DRenderData->TextureSlotIndex;
		s_2DRenderData->TextureSlots[TextureIndex] = texture;
		s_2DRenderData->TextureSlotIndex++;
	}

	glm::mat4 transform = glm::translate(glm::mat4(1.0f), glm::vec3(position.x, position.y, 0.0f)) * glm::scale(glm::mat4(1.0f), glm::vec3(size.x, size.y, 1.0f));

	s_2DRenderData->QuadVertexPtr->Position = transform * s_2DRenderData->QoudPositionTemplate[0];
	s_2DRenderData->QuadVertexPtr->Color = color;
	s_2DRenderData->QuadVertexPtr->TexCoord = { 0.0f, 0.0f };
	s_2DRenderData->QuadVertexPtr->ImageIndex = TextureIndex;
	s_2DRenderData->QuadVertexPtr++;

	s_2DRenderData->QuadVertexPtr->Position = transform * s_2DRenderData->QoudPositionTemplate[1];
	s_2DRenderData->QuadVertexPtr->Color = color;
	s_2DRenderData->QuadVertexPtr->TexCoord = { 1.0f, 0.0f };
	s_2DRenderData->QuadVertexPtr->ImageIndex = TextureIndex;
	s_2DRenderData->QuadVertexPtr++;

	s_2DRenderData->QuadVertexPtr->Position = transform * s_2DRenderData->QoudPositionTemplate[2];
	s_2DRenderData->QuadVertexPtr->Color = color;
	s_2DRenderData->QuadVertexPtr->TexCoord = { 1.0f, 1.0f };
	s_2DRenderData->QuadVertexPtr->ImageIndex = TextureIndex;
	s_2DRenderData->QuadVertexPtr++;

	s_2DRenderData->QuadVertexPtr->Position = transform * s_2DRenderData->QoudPositionTemplate[3];
	s_2DRenderData->QuadVertexPtr->Color = color;
	s_2DRenderData->QuadVertexPtr->TexCoord = { 0.0f, 1.0f };
	s_2DRenderData->QuadVertexPtr->ImageIndex = TextureIndex;
	s_2DRenderData->QuadVertexPtr++;

	s_2DRenderData->QuadIndexCount += 6;

	s_2DRenderData->m_Statistics.m_QuodCount++;
}

void ArcticFox::Graphics::Render2D::DrawQuad(const glm::vec3 & position, const glm::vec2 & size, const glm::vec4 & color, Texture * texture) {
	if (s_2DRenderData->QuadIndexCount >= Render2DCache::maxIndices) {
		EndScene();
	}

	int TextureIndex = 0;
	for (uint32_t i = 1; i < s_2DRenderData->TextureSlotIndex; i++) {
		if (texture == s_2DRenderData->TextureSlots[i]) {
			TextureIndex = i;
			break;
		}
	}
	if (TextureIndex == 0) {
		TextureIndex = s_2DRenderData->TextureSlotIndex;
		s_2DRenderData->TextureSlots[TextureIndex] = texture;
		s_2DRenderData->TextureSlotIndex++;
	}

	glm::mat4 transform = glm::translate(glm::mat4(1.0f), glm::vec3(position.x, position.y, 0.0f)) * glm::scale(glm::mat4(1.0f), glm::vec3(size.x, size.y, 1.0f));

	s_2DRenderData->QuadVertexPtr->Position = transform * s_2DRenderData->QoudPositionTemplate[0];
	s_2DRenderData->QuadVertexPtr->Color = color;
	s_2DRenderData->QuadVertexPtr->TexCoord = { 0.0f, 0.0f };
	s_2DRenderData->QuadVertexPtr->ImageIndex = TextureIndex;
	s_2DRenderData->QuadVertexPtr++;

	s_2DRenderData->QuadVertexPtr->Position = transform * s_2DRenderData->QoudPositionTemplate[1];
	s_2DRenderData->QuadVertexPtr->Color = color;
	s_2DRenderData->QuadVertexPtr->TexCoord = { 1.0f, 0.0f };
	s_2DRenderData->QuadVertexPtr->ImageIndex = TextureIndex;
	s_2DRenderData->QuadVertexPtr++;

	s_2DRenderData->QuadVertexPtr->Position = transform * s_2DRenderData->QoudPositionTemplate[2];
	s_2DRenderData->QuadVertexPtr->Color = color;
	s_2DRenderData->QuadVertexPtr->TexCoord = { 1.0f, 1.0f };
	s_2DRenderData->QuadVertexPtr->ImageIndex = TextureIndex;
	s_2DRenderData->QuadVertexPtr++;

	s_2DRenderData->QuadVertexPtr->Position = transform * s_2DRenderData->QoudPositionTemplate[3];
	s_2DRenderData->QuadVertexPtr->Color = color;
	s_2DRenderData->QuadVertexPtr->TexCoord = { 0.0f, 1.0f };
	s_2DRenderData->QuadVertexPtr->ImageIndex = TextureIndex;
	s_2DRenderData->QuadVertexPtr++;

	s_2DRenderData->QuadIndexCount += 6;

	s_2DRenderData->m_Statistics.m_QuodCount++;
}

void ArcticFox::Graphics::Render2D::DrawQuad(const glm::vec3 & position, const glm::vec2 & size, const glm::vec4 & color, Texture * texture, float rotate) {
	if (s_2DRenderData->QuadIndexCount >= Render2DCache::maxIndices) {
		EndScene();
	}

	int TextureIndex = 0;
	for (uint32_t i = 1; i < s_2DRenderData->TextureSlotIndex; i++) {
		if (texture == s_2DRenderData->TextureSlots[i]) {
			TextureIndex = i;
			break;
		}
	}
	if (TextureIndex == 0) {
		TextureIndex = s_2DRenderData->TextureSlotIndex;
		s_2DRenderData->TextureSlots[TextureIndex] = texture;
		s_2DRenderData->TextureSlotIndex++;
	}

	glm::mat4 transform = glm::translate(glm::mat4(1.0f), glm::vec3(position.x, position.y, 0.0f)) * glm::rotate(glm::mat4(1.0f), glm::radians(rotate), glm::vec3(0.0f, 0.0f, 1.0f)) * glm::scale(glm::mat4(1.0f), glm::vec3(size.x, size.y, 1.0f));

	s_2DRenderData->QuadVertexPtr->Position = transform * s_2DRenderData->QoudPositionTemplate[0];
	s_2DRenderData->QuadVertexPtr->Color = color;
	s_2DRenderData->QuadVertexPtr->TexCoord = { 0.0f, 0.0f };
	s_2DRenderData->QuadVertexPtr->ImageIndex = TextureIndex;
	s_2DRenderData->QuadVertexPtr++;

	s_2DRenderData->QuadVertexPtr->Position = transform * s_2DRenderData->QoudPositionTemplate[1];
	s_2DRenderData->QuadVertexPtr->Color = color;
	s_2DRenderData->QuadVertexPtr->TexCoord = { 1.0f, 0.0f };
	s_2DRenderData->QuadVertexPtr->ImageIndex = TextureIndex;
	s_2DRenderData->QuadVertexPtr++;

	s_2DRenderData->QuadVertexPtr->Position = transform * s_2DRenderData->QoudPositionTemplate[2];
	s_2DRenderData->QuadVertexPtr->Color = color;
	s_2DRenderData->QuadVertexPtr->TexCoord = { 1.0f, 1.0f };
	s_2DRenderData->QuadVertexPtr->ImageIndex = TextureIndex;
	s_2DRenderData->QuadVertexPtr++;

	s_2DRenderData->QuadVertexPtr->Position = transform * s_2DRenderData->QoudPositionTemplate[3];
	s_2DRenderData->QuadVertexPtr->Color = color;
	s_2DRenderData->QuadVertexPtr->TexCoord = { 0.0f, 1.0f };
	s_2DRenderData->QuadVertexPtr->ImageIndex = TextureIndex;
	s_2DRenderData->QuadVertexPtr++;

	s_2DRenderData->QuadIndexCount += 6;

	s_2DRenderData->m_Statistics.m_QuodCount++;
}


void ArcticFox::Graphics::Render2D::Flush() {
	//Cast array begin and end pointers to one byte size value pointer and subtract. Result is bytes between two points in array.
	uint32_t bufferSize = (uint8_t*)s_2DRenderData->QuadVertexPtr - (uint8_t*)s_2DRenderData->QuadVertexBase;
	s_2DRenderData->m_VBO->SetData(s_2DRenderData->QuadVertexBase, bufferSize);

	s_2DRenderData->m_VAO->Bind();
	s_2DRenderData->m_Shader->Bind();
	s_2DRenderData->m_Texture->Bind(0);
	for (uint32_t i = 0; i < s_2DRenderData->TextureSlotIndex; i++) {
		s_2DRenderData->TextureSlots[i]->Bind(i);
	}

	RenderCommand::DrawIndexed(s_2DRenderData->m_VAO, s_2DRenderData->QuadIndexCount);
	s_2DRenderData->m_Statistics.m_DrawCalls++;
}

void ArcticFox::Graphics::Render2D::EndScene() {
	Flush();

	s_2DRenderData->QuadVertexPtr = s_2DRenderData->QuadVertexBase;
	s_2DRenderData->TextureSlotIndex = 1;
	s_2DRenderData->QuadIndexCount = 0;
}

void ArcticFox::Graphics::Render2D::ShutDown() {
	delete[] s_2DRenderData->QuadVertexBase;
	delete s_2DRenderData->m_Shader;
	delete s_2DRenderData->m_VAO->GetIndexBuffer();
	delete s_2DRenderData->m_VBO;
	delete s_2DRenderData->m_VAO;
	delete s_2DRenderData;
}

void ArcticFox::Graphics::Render2D::ResetStats() {
	s_2DRenderData->m_Statistics.m_DrawCalls = 0;
	s_2DRenderData->m_Statistics.m_QuodCount = 0;
}

ArcticFox::Graphics::Render2D::Statistics ArcticFox::Graphics::Render2D::GetStats() {
	return s_2DRenderData->m_Statistics;
}
