#include "FrameBuffer.h"
#include "RendererAPI.h"
#include "OpenGL/OpenGLFrameBuffer.h"

Graphics::FrameBuffer * Graphics::FrameBuffer::Create(const FrameBufferSpec & spec) {
	switch (RendererAPI::GetAPI()) {
	case RendererAPI::API::None:		return nullptr;
	case RendererAPI::API::OpenGL:		return new OpenGL::OpenGLFrameBuffer(spec);
	case RendererAPI::API::Directx9:	return nullptr;
	case RendererAPI::API::Directx10:	return nullptr;
	case RendererAPI::API::Vulkan:		return nullptr;
	case RendererAPI::API::Metal:		return nullptr;
	default: return nullptr;
	}

	return nullptr;
}
