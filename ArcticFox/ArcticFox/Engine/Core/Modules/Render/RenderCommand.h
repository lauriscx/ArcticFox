#pragma once
#include "RendererAPI.h"

namespace Graphics {
	class RenderCommand {
	public:
		inline static void Init() {
			s_RendererAPI->Init();
		}

		inline static void SetClearColor(glm::vec4 color) {
			s_RendererAPI->SetClearColor(color);
		}
		inline static void SetViewPort(glm::vec4 size) {
			s_RendererAPI->SetViewPort(size);
		}
		inline static void Clear() {
			s_RendererAPI->Clear();
		}

		inline static void DrawIndexed(Graphics::VertexArray* vertexArray, uint32_t count = 0) {
			s_RendererAPI->DrawIndexed(vertexArray, count);
		}

	private:
		static RendererAPI* s_RendererAPI;
	};
}