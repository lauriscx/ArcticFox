#include "OpenGL/OpenGLBuffer.h"
#include "RendererAPI.h"

Graphics::VertexBuffer::VertexBuffer() {}
Graphics::VertexBuffer * Graphics::VertexBuffer::Create(void * data, uint32_t size) {
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
Graphics::VertexBuffer * Graphics::VertexBuffer::Create(uint32_t size) {
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
Graphics::VertexBuffer::~VertexBuffer() {}

Graphics::IndexBuffer::IndexBuffer() {}
Graphics::IndexBuffer * Graphics::IndexBuffer::Create(void * data, uint32_t count) {
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
Graphics::IndexBuffer::~IndexBuffer() {}

Graphics::VertexArray::VertexArray() {}
Graphics::VertexArray * Graphics::VertexArray::Create() {
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
Graphics::VertexArray::~VertexArray() {}