#include "RenderCommand.h"
#include "OpenGL/OpenGLRendererAPI.h"

namespace Graphics {
	RendererAPI* RenderCommand::s_RendererAPI = new OpenGL::OpenGLRendererAPI();
}