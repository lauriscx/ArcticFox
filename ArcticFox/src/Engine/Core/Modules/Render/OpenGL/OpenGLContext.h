#pragma once
#include "../GraphicsContext.h"

namespace ArcticFox {
	namespace Graphics {
		namespace OpenGL {
			class OpenGLContext : public GraphicsContext {
			public:
				OpenGLContext();
				virtual void Init() override;
				virtual void SwapBuffer() override;
				~OpenGLContext();

			};
		}
	}
}