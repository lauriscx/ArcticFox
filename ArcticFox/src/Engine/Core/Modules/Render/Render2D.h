#pragma once
#include "Camera.h"
#include "Texture.h"

namespace ArcticFox {
	struct SpriteRenderComponent;
	namespace Graphics {
		class Render2D {
		public:
			static void Init();

			static void BeginScene(const Camera& camera, const glm::mat4& transform);
			static void BeginScene(const EditorCamera& camera);
			static void BeginScene(const OrthographicCamera& camera);

			static void DrawQuad(const glm::mat4 matrix, const glm::vec4& color);

			static void DrawQuad(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color);
			static void DrawQuad(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color);
			static void DrawQuad(const glm::vec2& position, const glm::vec2& size, std::shared_ptr<Texture> texture);
			static void DrawQuad(const glm::vec3& position, const glm::vec2& size, std::shared_ptr<Texture> texture);
			static void DrawQuad(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color, std::shared_ptr<Texture> texture);
			static void DrawQuad(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color, std::shared_ptr<Texture> texture);

			static void DrawQuad(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color, std::shared_ptr<Texture> texture, float rotate);

			static void DrawSprite(const glm::mat4 matrix, SpriteRenderComponent& src, int entityID = -1);

			static void Flush();

			static void EndScene();

			static void ShutDown();

			struct Statistics {
				uint32_t m_DrawCalls = 0;
				uint32_t m_QuodCount = 0;

				uint32_t GetTotalVertexCount() { return m_QuodCount * 4; };
				uint32_t GetTotalIndexCount() { return m_QuodCount * 6; };
			};

			static void ResetStats();
			static Statistics GetStats();
		};
	}
}