#pragma once
#include "BufferLayout.h"

namespace ArcticFox {
	namespace Graphics {
		class VertexBuffer {
		public:
			VertexBuffer();

			static VertexBuffer* Create(uint32_t size);
			static VertexBuffer* Create(void* data, uint32_t size);

			virtual void SetLayout(const BufferLayout& layout) = 0;

			virtual const BufferLayout& GetLayout() = 0;

			virtual void SetData(void* data, uint32_t size) = 0;

			virtual void Bind() = 0;
			virtual void Unbind() = 0;

			virtual ~VertexBuffer();
		};

		class IndexBuffer {
		public:
			IndexBuffer();

			static IndexBuffer* Create(void* data, uint32_t count);

			virtual void Bind() = 0;
			virtual void Unbind() = 0;

			virtual uint32_t getCount() const = 0;

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
		
		class UniformBuffer {
		public:

			static UniformBuffer* Create(uint32_t size, uint32_t binding);

			virtual void SetData(void* data, uint32_t size, uint32_t offset) = 0;

			virtual ~UniformBuffer();
		};
	}
}