#include "OpenGLContext.h"
#include "Glad/glad.h"

ArcticFox::Graphics::OpenGL::OpenGLContext::OpenGLContext() {
}

void ArcticFox::Graphics::OpenGL::OpenGLContext::Init() {
	gladLoadGL();

	glGetString(GL_VENDOR);
	glGetString(GL_RENDERER);
	glGetString(GL_VERSION);

	/*unsigned int shader = glCreateShader(GL_VERTEX_SHADER);

	unsigned int buffer = 0;
	glGenBuffers(1, &buffer);
	glBindBuffer(GL_VERTEX_ARRAY, buffer);*/
}

void ArcticFox::Graphics::OpenGL::OpenGLContext::SwapBuffer() {

}

ArcticFox::Graphics::OpenGL::OpenGLContext::~OpenGLContext() {
	/*glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
	glClearColor(1, 0, 1, 1);*/
}
