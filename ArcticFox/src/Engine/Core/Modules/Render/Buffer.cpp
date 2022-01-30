#include "OpenGL/OpenGLBuffer.h"
#include "RendererAPI.h"

ArcticFox::Graphics::VertexBuffer::VertexBuffer() {}
ArcticFox::Graphics::VertexBuffer * ArcticFox::Graphics::VertexBuffer::Create(void * data, uint32_t size) {
	switch (RendererAPI::GetAPI()) {
		case RendererAPI::API::None:		return nullptr;
		case RendererAPI::API::OpenGL:		return new OpenGL::OpenGLVertexBuffer(data, size);
		case RendererAPI::API::Directx9:	return nullptr;
		case RendererAPI::API::Directx10:	return nullptr;
		case RendererAPI::API::Vulkan:		return nullptr;
		case RendererAPI::API::Metal:		return nullptr;
		default: return nullptr;
	}

	return nullptr;
}
ArcticFox::Graphics::VertexBuffer * ArcticFox::Graphics::VertexBuffer::Create(uint32_t size) {
	switch (RendererAPI::GetAPI()) {
	case RendererAPI::API::None:		return nullptr;
	case RendererAPI::API::OpenGL:		return new OpenGL::OpenGLVertexBuffer(size);
	case RendererAPI::API::Directx9:	return nullptr;
	case RendererAPI::API::Directx10:	return nullptr;
	case RendererAPI::API::Vulkan:		return nullptr;
	case RendererAPI::API::Metal:		return nullptr;
	default: return nullptr;
	}

	return nullptr;
}
ArcticFox::Graphics::VertexBuffer::~VertexBuffer() {}

ArcticFox::Graphics::IndexBuffer::IndexBuffer() {}
ArcticFox::Graphics::IndexBuffer * ArcticFox::Graphics::IndexBuffer::Create(void * data, uint32_t count) {
	switch (RendererAPI::GetAPI()) {
		case RendererAPI::API::None:		return nullptr;
		case RendererAPI::API::OpenGL:		return new OpenGL::OpenGLIndexBuffer(data, count);
		case RendererAPI::API::Directx9:	return nullptr;
		case RendererAPI::API::Directx10:	return nullptr;
		case RendererAPI::API::Vulkan:		return nullptr;
		case RendererAPI::API::Metal:		return nullptr;
		default: return nullptr;
	}

	return nullptr;
}
ArcticFox::Graphics::IndexBuffer::~IndexBuffer() {}

ArcticFox::Graphics::VertexArray::VertexArray() {}
ArcticFox::Graphics::VertexArray * ArcticFox::Graphics::VertexArray::Create() {
	switch (RendererAPI::GetAPI()) {
	case RendererAPI::API::None:		return nullptr;
	case RendererAPI::API::OpenGL:		return new OpenGL::OpenGLVertexArray();
	case RendererAPI::API::Directx9:	return nullptr;
	case RendererAPI::API::Directx10:	return nullptr;
	case RendererAPI::API::Vulkan:		return nullptr;
	case RendererAPI::API::Metal:		return nullptr;
	default: return nullptr;
	}

	return nullptr;
}
ArcticFox::Graphics::VertexArray::~VertexArray() {}