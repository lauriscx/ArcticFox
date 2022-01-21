#pragma once
#include "../Buffer.h"

namespace Graphics {
	namespace OpenGL {
		class OpenGLVertexBuffer : public VertexBuffer {
		public:
			OpenGLVertexBuffer(void* data, int size);

			virtual void SetLayout(const BufferLayout& layout) override;

			virtual const BufferLayout& GetLayout() override;

			virtual void Bind() override;
			virtual void Unbind() override;

			~OpenGLVertexBuffer();

		private:
			unsigned int m_VBO;
			BufferLayout m_Layout;
		};

		class OpenGLIndexBuffer : public IndexBuffer {
		public:
			OpenGLIndexBuffer(void* data, unsigned int count);

			virtual void Bind() override;
			virtual void Unbind() override;

			virtual unsigned int getCount() const override;

			~OpenGLIndexBuffer();
		private:
			unsigned int m_IBO;

			unsigned int m_Count;
		};

		class OpenGLVertexArray : public VertexArray {
		public:
			OpenGLVertexArray();

			virtual void AddVertexBuffer(VertexBuffer* buffer) override;
			virtual void SetIndexBuffer(IndexBuffer* buffer) override;

			virtual std::vector<VertexBuffer*> GetVertexBuffers() override;
			virtual const IndexBuffer* GetIndexBuffer() override;

			virtual void Bind() override;
			virtual void Unbind() override;

			~OpenGLVertexArray();
		private:
			unsigned int m_VAO;

			IndexBuffer* m_IndexBuffer;
			std::vector<VertexBuffer*> m_VertexBuffers;
		};
	}
}