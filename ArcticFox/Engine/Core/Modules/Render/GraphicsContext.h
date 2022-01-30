#pragma once

namespace Graphics {
	class GraphicsContext {
	public:
		GraphicsContext() {}
		virtual void Init() = 0;
		virtual void SwapBuffer() = 0;

		~GraphicsContext() {}
	};
}