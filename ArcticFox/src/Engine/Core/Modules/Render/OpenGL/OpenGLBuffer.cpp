#include "OpenGLBuffer.h"

#include "Glad/glad.h"

ArcticFox::Graphics::OpenGL::OpenGLVertexBuffer::OpenGLVertexBuffer(uint32_t size) {
	glGenBuffers(1, &m_VBO);

	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
	glBufferData(GL_ARRAY_BUFFER, size, nullptr, GL_DYNAMIC_DRAW);
}
ArcticFox::Graphics::OpenGL::OpenGLVertexBuffer::OpenGLVertexBuffer(void* data, uint32_t size) {
	glGenBuffers(1, &m_VBO);

	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
	glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
}
void ArcticFox::Graphics::OpenGL::OpenGLVertexBuffer::SetLayout(const BufferLayout& layout) {
	m_Layout = layout;
}
const ArcticFox::Graphics::BufferLayout& ArcticFox::Graphics::OpenGL::OpenGLVertexBuffer::GetLayout() {
	return m_Layout; 
}
void ArcticFox::Graphics::OpenGL::OpenGLVertexBuffer::SetData(void * data, uint32_t size) {
	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
	glBufferSubData(GL_ARRAY_BUFFER, 0, size, data);
}
void ArcticFox::Graphics::OpenGL::OpenGLVertexBuffer::Bind() {
	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
}
void ArcticFox::Graphics::OpenGL::OpenGLVertexBuffer::Unbind() {
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}
ArcticFox::Graphics::OpenGL::OpenGLVertexBuffer::~OpenGLVertexBuffer() {
	glDeleteBuffers(1, &m_VBO);
}

ArcticFox::Graphics::OpenGL::OpenGLIndexBuffer::OpenGLIndexBuffer(void* data, uint32_t count) : m_Count(count) {
	glGenBuffers(1, &m_IBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(uint32_t), data, GL_STATIC_DRAW);
}
void ArcticFox::Graphics::OpenGL::OpenGLIndexBuffer::Bind() {
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IBO);
}
void ArcticFox::Graphics::OpenGL::OpenGLIndexBuffer::Unbind() {
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}
uint32_t ArcticFox::Graphics::OpenGL::OpenGLIndexBuffer::getCount() const {
	return m_Count;
}
ArcticFox::Graphics::OpenGL::OpenGLIndexBuffer::~OpenGLIndexBuffer() {
	glDeleteBuffers(1, &m_IBO);
}

ArcticFox::Graphics::OpenGL::OpenGLVertexArray::OpenGLVertexArray() {
	glGenVertexArrays(1, &m_VAO);
}
void ArcticFox::Graphics::OpenGL::OpenGLVertexArray::AddVertexBuffer(VertexBuffer* buffer) {
	auto ParseDataType = [](DataType type) {
		switch (type) {
		case Graphics::DataType::NONE:		return GL_FLOAT;
		case Graphics::DataType::FLOAT_1:	return GL_FLOAT;
		case Graphics::DataType::FLOAT_2:	return GL_FLOAT;
		case Graphics::DataType::FLOAT_3:	return GL_FLOAT;
		case Graphics::DataType::FLOAT_4:	return GL_FLOAT;
		case Graphics::DataType::FLOAT_9:	return GL_FLOAT;
		case Graphics::DataType::FLOAT_16:	return GL_FLOAT;
		case Graphics::DataType::UINT_1:	return GL_UNSIGNED_INT;
		case Graphics::DataType::UINT_2:	return GL_UNSIGNED_INT;
		case Graphics::DataType::UINT_3:	return GL_UNSIGNED_INT;
		case Graphics::DataType::UINT_4:	return GL_UNSIGNED_INT;
		case Graphics::DataType::UINT_9:	return GL_UNSIGNED_INT;
		case Graphics::DataType::UINT_16:	return GL_UNSIGNED_INT;
		case Graphics::DataType::INT_1:		return GL_INT;
		case Graphics::DataType::INT_2:		return GL_INT;
		case Graphics::DataType::INT_3:		return GL_INT;
		case Graphics::DataType::INT_4:		return GL_INT;
		case Graphics::DataType::INT_9:		return GL_INT;
		case Graphics::DataType::INT_16:	return GL_INT;
		case Graphics::DataType::BOOL_1:	return GL_BOOL;
		case Graphics::DataType::BOOL_2:	return GL_BOOL;
		case Graphics::DataType::BOOL_3:	return GL_BOOL;
		case Graphics::DataType::BOOL_4:	return GL_BOOL;
		case Graphics::DataType::BOOL_9:	return GL_BOOL;
		case Graphics::DataType::BOOL_16:	return GL_BOOL;
		case Graphics::DataType::COUNT:		return GL_FLOAT;
		default: return GL_FLOAT;
		}
		return GL_FLOAT;
	};
	
	glBindVertexArray(m_VAO);
	
	buffer->Bind();
	const auto& layout = buffer->GetLayout();
	for (int i = 0; i < layout.GetElements().size(); i++) {

		BufferElement element = layout.GetElements()[i];
		switch (element.m_Type) {
			case Graphics::DataType::FLOAT_1: {
				glEnableVertexAttribArray(i);
				glVertexAttribPointer(i, element.m_Components, (GLenum)ParseDataType(element.m_Type), element.m_Normalized ? GL_TRUE : GL_FALSE, layout.GetStride(), (const void*)element.m_Offset);
				break;
			}
			case Graphics::DataType::FLOAT_2: {
				glEnableVertexAttribArray(i);
				glVertexAttribPointer(i, element.m_Components, (GLenum)ParseDataType(element.m_Type), element.m_Normalized ? GL_TRUE : GL_FALSE, layout.GetStride(), (const void*)element.m_Offset);
				break;
			}
			case Graphics::DataType::FLOAT_3: {
				glEnableVertexAttribArray(i);
				glVertexAttribPointer(i, element.m_Components, (GLenum)ParseDataType(element.m_Type), element.m_Normalized ? GL_TRUE : GL_FALSE, layout.GetStride(), (const void*)element.m_Offset);
				break;
			}
			case Graphics::DataType::FLOAT_4: {
				glEnableVertexAttribArray(i);
				glVertexAttribPointer(i, element.m_Components, (GLenum)ParseDataType(element.m_Type), element.m_Normalized ? GL_TRUE : GL_FALSE, layout.GetStride(), (const void*)element.m_Offset);
				break;
			}
			case Graphics::DataType::FLOAT_9: {}
			case Graphics::DataType::FLOAT_16: {}
			case Graphics::DataType::UINT_1: {}
			case Graphics::DataType::UINT_2: {}
			case Graphics::DataType::UINT_3: {}
			case Graphics::DataType::UINT_4: {}
			case Graphics::DataType::UINT_9: {}
			case Graphics::DataType::UINT_16: {}
			case Graphics::DataType::INT_1: {
				glEnableVertexAttribArray(i);
				glVertexAttribIPointer(i, element.m_Components, (GLenum)ParseDataType(element.m_Type), layout.GetStride(), (const void*)element.m_Offset);
				break;
			}
			case Graphics::DataType::INT_2: {
				glEnableVertexAttribArray(i);
				glVertexAttribIPointer(i, element.m_Components, (GLenum)ParseDataType(element.m_Type), layout.GetStride(), (const void*)element.m_Offset);
				break;
			}
			case Graphics::DataType::INT_3: {
				glEnableVertexAttribArray(i);
				glVertexAttribIPointer(i, element.m_Components, (GLenum)ParseDataType(element.m_Type), layout.GetStride(), (const void*)element.m_Offset);
				break;
			}
			case Graphics::DataType::INT_4: {
				glEnableVertexAttribArray(i);
				glVertexAttribIPointer(i, element.m_Components, (GLenum)ParseDataType(element.m_Type), layout.GetStride(), (const void*)element.m_Offset);
				break;
			}
			case Graphics::DataType::INT_9: {}
			case Graphics::DataType::INT_16: {}
			case Graphics::DataType::BOOL_1: {}
			case Graphics::DataType::BOOL_2: {}
			case Graphics::DataType::BOOL_3: {}
			case Graphics::DataType::BOOL_4: {}
			case Graphics::DataType::BOOL_9: {}
			case Graphics::DataType::BOOL_16: {}
		}
	
	}
	m_VertexBuffers.push_back(buffer);
	
	

	/*glBindVertexArray(m_VAO);
	
	auto ParseDataType = [](DataType type) {
		switch (type) {
			case Graphics::DataType::NONE:		return GL_FLOAT;
			case Graphics::DataType::FLOAT_1:	return GL_FLOAT;
			case Graphics::DataType::FLOAT_2:	return GL_FLOAT;
			case Graphics::DataType::FLOAT_3:	return GL_FLOAT;
			case Graphics::DataType::FLOAT_4:	return GL_FLOAT;
			case Graphics::DataType::FLOAT_9:	return GL_FLOAT;
			case Graphics::DataType::FLOAT_16:	return GL_FLOAT;
			case Graphics::DataType::UINT_1:	return GL_UNSIGNED_INT;
			case Graphics::DataType::UINT_2:	return GL_UNSIGNED_INT;
			case Graphics::DataType::UINT_3:	return GL_UNSIGNED_INT;
			case Graphics::DataType::UINT_4:	return GL_UNSIGNED_INT;
			case Graphics::DataType::UINT_9:	return GL_UNSIGNED_INT;
			case Graphics::DataType::UINT_16:	return GL_UNSIGNED_INT;
			case Graphics::DataType::INT_1:		return GL_INT;
			case Graphics::DataType::INT_2:		return GL_INT;
			case Graphics::DataType::INT_3:		return GL_INT;
			case Graphics::DataType::INT_4:		return GL_INT;
			case Graphics::DataType::INT_9:		return GL_INT;
			case Graphics::DataType::INT_16:	return GL_INT;
			case Graphics::DataType::BOOL_1:	return GL_BOOL;
			case Graphics::DataType::BOOL_2:	return GL_BOOL;
			case Graphics::DataType::BOOL_3:	return GL_BOOL;
			case Graphics::DataType::BOOL_4:	return GL_BOOL;
			case Graphics::DataType::BOOL_9:	return GL_BOOL;
			case Graphics::DataType::BOOL_16:	return GL_BOOL;
			case Graphics::DataType::COUNT:		return GL_FLOAT;
			default: return GL_FLOAT;
		}
		return GL_FLOAT;
	};
	
	buffer->Bind();
	const auto& layout = buffer->GetLayout();
	for (int i = 0; i < layout.GetElements().size(); i++) {
		BufferElement element = layout.GetElements()[i];
		glEnableVertexAttribArray(i);
		glVertexAttribPointer(i, element.m_Components, (GLenum)ParseDataType(element.m_Type), element.m_Normalized ? GL_TRUE : GL_FALSE, layout.GetStride(), (const void*)element.m_Offset);
	}
	m_VertexBuffers.push_back(buffer);*/
}
void ArcticFox::Graphics::OpenGL::OpenGLVertexArray::SetIndexBuffer(IndexBuffer * buffer) {
	glBindVertexArray(m_VAO);
	buffer->Bind();
	m_IndexBuffer = buffer;
}
std::vector<ArcticFox::Graphics::VertexBuffer*> ArcticFox::Graphics::OpenGL::OpenGLVertexArray::GetVertexBuffers() {
	return m_VertexBuffers;
}
const ArcticFox::Graphics::IndexBuffer * ArcticFox::Graphics::OpenGL::OpenGLVertexArray::GetIndexBuffer() {
	return m_IndexBuffer;
}
void ArcticFox::Graphics::OpenGL::OpenGLVertexArray::Bind() {
	glBindVertexArray(m_VAO);
}
void ArcticFox::Graphics::OpenGL::OpenGLVertexArray::Unbind() {
	glBindVertexArray(m_VAO);
}
ArcticFox::Graphics::OpenGL::OpenGLVertexArray::~OpenGLVertexArray() {
	glDeleteVertexArrays(1, &m_VAO);
}

ArcticFox::Graphics::OpenGL::OpenGLUniformBuffer::OpenGLUniformBuffer(uint32_t size, uint32_t binding) {
	glCreateBuffers(1, &m_UFO);
	glNamedBufferData(m_UFO, size, nullptr, GL_DYNAMIC_DRAW);
	glBindBufferBase(GL_UNIFORM_BUFFER, binding, m_UFO);
}
void ArcticFox::Graphics::OpenGL::OpenGLUniformBuffer::SetData(void * data, uint32_t size, uint32_t offset) {
	glNamedBufferSubData(m_UFO, offset, size, data);
}
ArcticFox::Graphics::OpenGL::OpenGLUniformBuffer::~OpenGLUniformBuffer() {
	glDeleteBuffers(1, &m_UFO);
}
