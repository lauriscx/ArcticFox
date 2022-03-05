#include "Texture.h"
#include "RendererAPI.h"
#include "OpenGL/OpenGLTexture.h"

std::shared_ptr<ArcticFox::Graphics::Texture2D> ArcticFox::Graphics::Texture2D::Create(uint32_t width, uint32_t height) {
	switch (RendererAPI::GetAPI()) {
	case RendererAPI::API::None:		return nullptr;
	case RendererAPI::API::OpenGL:		return std::make_shared<OpenGL::OpenGLTexture2D>(width, height);
	case RendererAPI::API::Directx9:	return nullptr;
	case RendererAPI::API::Directx10:	return nullptr;
	case RendererAPI::API::Vulkan:		return nullptr;
	case RendererAPI::API::Metal:		return nullptr;
	default: return nullptr;
	}

	return nullptr;
}

std::shared_ptr<ArcticFox::Graphics::Texture2D> ArcticFox::Graphics::Texture2D::Create(AppFrame::ResourceTexture* texture) {
	switch (RendererAPI::GetAPI()) {
	case RendererAPI::API::None:		return nullptr;
	case RendererAPI::API::OpenGL:		return std::make_shared<OpenGL::OpenGLTexture2D>(texture);
	case RendererAPI::API::Directx9:	return nullptr;
	case RendererAPI::API::Directx10:	return nullptr;
	case RendererAPI::API::Vulkan:		return nullptr;
	case RendererAPI::API::Metal:		return nullptr;
	default: return nullptr;
	}

	return nullptr;
}
