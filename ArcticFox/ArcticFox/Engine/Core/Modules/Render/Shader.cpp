#include "OpenGL/OpenGLShader.h"
#include "RendererAPI.h"

Graphics::Shader::Shader() {}

Graphics::Shader * Graphics::Shader::Create() {
	switch (RendererAPI::GetAPI()) {
		case RendererAPI::API::None:		return nullptr;
		case RendererAPI::API::OpenGL:		return new OpenGL::OpenGLShader();
		case RendererAPI::API::Directx9:	return nullptr;
		case RendererAPI::API::Directx10:	return nullptr;
		case RendererAPI::API::Vulkan:		return nullptr;
		case RendererAPI::API::Metal:		return nullptr;
		default: return nullptr;
	}
}

Graphics::Shader::~Shader() {}