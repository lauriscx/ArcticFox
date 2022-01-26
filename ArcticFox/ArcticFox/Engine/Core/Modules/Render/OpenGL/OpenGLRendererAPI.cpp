#include "OpenGLRendererAPI.h"
#include "Glad/glad.h"


Graphics::OpenGL::OpenGLRendererAPI::OpenGLRendererAPI() {}

void Graphics::OpenGL::OpenGLRendererAPI::Init() {
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glEnable(GL_DEPTH_TEST);
}

void Graphics::OpenGL::OpenGLRendererAPI::SetViewPort(glm::vec4 & size) {
	glViewport(size.x, size.y, size.z, size.w);
}

void Graphics::OpenGL::OpenGLRendererAPI::SetClearColor(glm::vec4 & color) {
	glClearColor(color.r, color.g, color.b, color.a);
}
void Graphics::OpenGL::OpenGLRendererAPI::Clear() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
}
void Graphics::OpenGL::OpenGLRendererAPI::DrawIndexed(VertexArray * vertexArray) {
	//glDrawArrays(GL_TRIANGLES, 0, 3);
	glDrawElements(GL_TRIANGLES, vertexArray->GetIndexBuffer()->getCount(), GL_UNSIGNED_INT, 0);
}

Graphics::OpenGL::OpenGLRendererAPI::~OpenGLRendererAPI() {}