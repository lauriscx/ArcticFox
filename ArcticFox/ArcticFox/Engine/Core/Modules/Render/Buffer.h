#pragma once
#include "BufferLayout.h"

namespace Graphics {
	class VertexBuffer {
	public:
		VertexBuffer();

		static VertexBuffer* Create(void* data, size_t size);

		virtual void SetLayout(const BufferLayout& layout) = 0;

		virtual const BufferLayout& GetLayout() = 0;

		virtual void Bind() = 0;
		virtual void Unbind() = 0;

		virtual ~VertexBuffer();
	};

	class IndexBuffer {
	public:
		IndexBuffer();

		static IndexBuffer* Create(void* data,  unsigned int count);

		virtual void Bind() = 0;
		virtual void Unbind() = 0;

		virtual unsigned int getCount() const = 0;

		virtual ~IndexBuffer();
	};

	class VertexArray {
	public:
		VertexArray();

		static VertexArray* Create();

		virtual void AddVertexBuffer(VertexBuffer* buffer) = 0;
		virtual void SetIndexBuffer(IndexBuffer* buffer) = 0;

		virtual std::vector<VertexBuffer*> GetVertexBuffers() = 0;
		virtual const IndexBuffer* GetIndexBuffer() = 0;

		virtual void Bind() = 0;
		virtual void Unbind() = 0;

		virtual ~VertexArray();
	};
}