#pragma once
#include <glm/glm.hpp>
#include "Buffer.h"

namespace Graphics {
	class RendererAPI {
	public:
		enum class API {
			None = 0,
			OpenGL = 1,
			Directx9 = 2,
			Directx10 = 3,
			Vulkan = 4,
			Metal = 5
		};
	public:
		virtual void Init() = 0;

		virtual void SetClearColor(glm::vec4& color) = 0;
		virtual void SetViewPort(glm::vec4& size) = 0;
		virtual void Clear() = 0;
		virtual void DrawIndexed(VertexArray* vertexArray) = 0;


		static inline void SetAPI(API api) { s_API = api; };
		inline static API GetAPI() { return s_API; }
	private:
		static API s_API;
	};

}