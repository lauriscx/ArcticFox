#pragma once
#include "../Buffer.h"

namespace ArcticFox {
	namespace Graphics {
		namespace OpenGL {
			class OpenGLVertexBuffer : public VertexBuffer {
			public:
				OpenGLVertexBuffer(uint32_t size);
				OpenGLVertexBuffer(void* data, uint32_t size);

				virtual void SetLayout(const BufferLayout& layout) override;

				virtual const BufferLayout& GetLayout() override;

				virtual void SetData(void* data, uint32_t size) override;

				virtual void Bind() override;
				virtual void Unbind() override;

				~OpenGLVertexBuffer();

			private:
				uint32_t m_VBO;
				BufferLayout m_Layout;
			};

			class OpenGLIndexBuffer : public IndexBuffer {
			public:
				OpenGLIndexBuffer(void* data, uint32_t count);

				virtual void Bind() override;
				virtual void Unbind() override;

				virtual uint32_t getCount() const override;

				~OpenGLIndexBuffer();
			private:
				uint32_t m_IBO;

				uint32_t m_Count;
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
				uint32_t m_VAO;

				IndexBuffer* m_IndexBuffer;
				std::vector<VertexBuffer*> m_VertexBuffers;
			};

			class OpenGLUniformBuffer : public UniformBuffer {
			public:
				OpenGLUniformBuffer(uint32_t size, uint32_t binding);

				void SetData(void* data, uint32_t size, uint32_t offset) override;

				virtual ~OpenGLUniformBuffer();
			private:
				uint32_t m_UFO;
			};
		}
	}
}