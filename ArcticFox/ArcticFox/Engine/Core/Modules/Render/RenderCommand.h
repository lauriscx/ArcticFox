#pragma once
#include "RendererAPI.h"

namespace Graphics {
	class RenderCommand {
	public:
		inline static void SetClearColor(glm::vec4 color) {
			s_RendererAPI->SetClearColor(color);
		}
		inline static void Clear() {
			s_RendererAPI->Clear();
		}

		inline static void DrawIndexed(Graphics::VertexArray* vertexArray) {
			s_RendererAPI->DrawIndexed(vertexArray);
		}

	private:
		static RendererAPI* s_RendererAPI;
	};
}