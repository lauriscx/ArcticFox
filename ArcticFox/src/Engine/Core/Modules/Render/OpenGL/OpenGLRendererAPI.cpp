#include "OpenGLRendererAPI.h"
#include "Glad/glad.h"


ArcticFox::Graphics::OpenGL::OpenGLRendererAPI::OpenGLRendererAPI() {}

void ArcticFox::Graphics::OpenGL::OpenGLRendererAPI::Init() {
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glEnable(GL_DEPTH_TEST);
}

void ArcticFox::Graphics::OpenGL::OpenGLRendererAPI::SetViewPort(glm::vec4 & size) {
	glViewport(size.x, size.y, size.z, size.w);
}

void ArcticFox::Graphics::OpenGL::OpenGLRendererAPI::SetClearColor(glm::vec4 & color) {
	glClearColor(color.r, color.g, color.b, color.a);
}
void ArcticFox::Graphics::OpenGL::OpenGLRendererAPI::Clear() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
}
void ArcticFox::Graphics::OpenGL::OpenGLRendererAPI::DrawIndexed(VertexArray * vertexArray, uint32_t count) {
	glDrawElements(GL_TRIANGLES, count ? count : vertexArray->GetIndexBuffer()->getCount(), GL_UNSIGNED_INT, 0);
	//glDrawArrays(GL_TRIANGLES, 0, count ? count : vertexArray->GetIndexBuffer()->getCount());
}

ArcticFox::Graphics::OpenGL::OpenGLRendererAPI::~OpenGLRendererAPI() {}