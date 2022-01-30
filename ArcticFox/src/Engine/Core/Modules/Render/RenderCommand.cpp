#include "RenderCommand.h"
#include "OpenGL/OpenGLRendererAPI.h"

namespace ArcticFox {
	namespace Graphics {
		RendererAPI* RenderCommand::s_RendererAPI = new OpenGL::OpenGLRendererAPI();
	}
}