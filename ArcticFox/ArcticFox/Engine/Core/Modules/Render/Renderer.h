#pragma once
#include "RenderCommand.h"

namespace Graphics {
	class Renderer {
	public:
		static void BeginScene();

		static void Submit(Graphics::VertexArray* vertexArray);

		static void EndScene();
	};

}