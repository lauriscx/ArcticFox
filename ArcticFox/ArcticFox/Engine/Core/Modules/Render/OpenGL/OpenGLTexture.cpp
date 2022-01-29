#include "OpenGLTexture.h"
#include "Glad/glad.h"

Graphics::OpenGL::OpenGLTexture2D::OpenGLTexture2D(uint32_t width, uint32_t height) : m_Width(width), m_Height(height) {
	auto ParseInternalFormat = [](int channels) {
		switch (channels) {
		case 1:	return GL_R8;
		case 2:	return GL_RG8;
		case 3:	return GL_RGB8;
		case 4:	return GL_RGBA8;
		default: return GL_RGB8;
		}
		return GL_RGB8;
	};
	auto ParseFormat = [](int channels) {
		switch (channels) {
		case 1:	return GL_R;
		case 2:	return GL_RG;
		case 3:	return GL_RGB;
		case 4:	return GL_RGBA;
		default: return GL_RGB;
		}
		return GL_RGB;
	};

	m_InternalFormat = ParseInternalFormat(4);
	m_DataFormat = ParseFormat(4);

	glGenTextures(1, &m_Texture);
	glBindTexture(GL_TEXTURE_2D, m_Texture);
	glTextureStorage2D(m_Texture, 1, m_InternalFormat, m_Width, m_Height);

	glTextureParameteri(m_Texture, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTextureParameteri(m_Texture, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	glTextureParameteri(m_Texture, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTextureParameteri(m_Texture, GL_TEXTURE_WRAP_T, GL_REPEAT);
}

Graphics::OpenGL::OpenGLTexture2D::OpenGLTexture2D(AppFrame::ResourceTexture* texture) {

	auto ParseInternalFormat = [](int channels) {
		switch (channels) {
			case 1:	return GL_R8;
			case 2:	return GL_RG8;
			case 3:	return GL_RGB8;
			case 4:	return GL_RGBA8;
			default: return GL_RGB8;
		}
		return GL_RGB8;
	};
	auto ParseFormat = [](int channels) {
		switch (channels) {
			case 1:	return GL_R;
			case 2:	return GL_RG;
			case 3:	return GL_RGB;
			case 4:	return GL_RGBA;
			default: return GL_RGB;
		}
		return GL_RGB;
	};
	m_InternalFormat = ParseInternalFormat(texture->GetChannels());
	m_DataFormat = ParseFormat(texture->GetChannels());

	glGenTextures(1, &m_Texture);
	glBindTexture(GL_TEXTURE_2D, m_Texture);
	glTextureStorage2D(m_Texture, 1, m_InternalFormat, texture->GetWidth(), texture->GetHeight());

	glTextureParameteri(m_Texture, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTextureParameteri(m_Texture, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	glTextureParameteri(m_Texture, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTextureParameteri(m_Texture, GL_TEXTURE_WRAP_T, GL_REPEAT);

	m_Width = texture->GetWidth();
	m_Height = texture->GetHeight();
	glTextureSubImage2D(m_Texture, 0, 0, 0, texture->GetWidth(), texture->GetHeight(), m_DataFormat, GL_UNSIGNED_BYTE, texture->Get());
}

int Graphics::OpenGL::OpenGLTexture2D::GetWidth() const {
	return m_Width;
}

int Graphics::OpenGL::OpenGLTexture2D::GetHeight() const {
	return m_Height;
}

void Graphics::OpenGL::OpenGLTexture2D::SetData(void * data, uint32_t size) {
	glTextureSubImage2D(m_Texture, 0, 0, 0, m_Width, m_Height, m_DataFormat, GL_UNSIGNED_BYTE, data);
}

void Graphics::OpenGL::OpenGLTexture2D::Bind(uint32_t slot) const {
	//glBindTexture(GL_TEXTURE0, m_Texture);
	glBindTextureUnit(slot, m_Texture);
}

void Graphics::OpenGL::OpenGLTexture2D::Unbind() const {
	glBindTexture(GL_TEXTURE0, 0);
}

uint32_t Graphics::OpenGL::OpenGLTexture2D::ID() {
	return m_Texture;
}

Graphics::OpenGL::OpenGLTexture2D::~OpenGLTexture2D() {
	glDeleteTextures(1, &m_Texture);
}