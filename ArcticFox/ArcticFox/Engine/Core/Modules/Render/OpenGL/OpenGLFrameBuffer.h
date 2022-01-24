#pragma once
#include "../FrameBuffer.h"

namespace Graphics {
	namespace OpenGL {
		class OpenGLFrameBuffer : public FrameBuffer {
		public:
			virtual ~OpenGLFrameBuffer();
		};
	}
}