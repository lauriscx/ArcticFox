#pragma once
#include "Camera.h"
#include "Texture.h"

namespace Graphics {
	class Render2D {
	public:
		static void Init();

		static void BeginScene(const OrthographicCamera& camera);

		static void DrawQuad(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color);
		static void DrawQuad(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color);
		static void DrawQuad(const glm::vec2& position, const glm::vec2& size, Texture* texture);
		static void DrawQuad(const glm::vec3& position, const glm::vec2& size, Texture* texture);
		static void DrawQuad(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color, Texture* texture);
		static void DrawQuad(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color, Texture* texture);
		
		static void EndScene();
		
		static void ShutDown();
	};
}