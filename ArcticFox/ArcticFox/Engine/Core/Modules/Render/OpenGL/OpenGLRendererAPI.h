#pragma once

#include "../RendererAPI.h"

namespace Graphics {
	namespace OpenGL {
		class OpenGLRendererAPI : public RendererAPI {
		public:
			OpenGLRendererAPI();
			
			virtual void Init() override;

			virtual void SetViewPort(glm::vec4& size) override;

			// Inherited via RendererAPI
			virtual void SetClearColor(glm::vec4 & color) override;

			virtual void Clear() override;

			virtual void DrawIndexed(VertexArray * vertexArray) override;
			
			~OpenGLRendererAPI();


		};
	}
}