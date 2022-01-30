#include "OpenGLFrameBuffer.h"
#include "Glad/glad.h"

ArcticFox::Graphics::OpenGL::OpenGLFrameBuffer::OpenGLFrameBuffer(const FrameBufferSpec & spec) : m_Specs(spec) {
	Invalidate();
}

ArcticFox::Graphics::FrameBufferSpec & ArcticFox::Graphics::OpenGL::OpenGLFrameBuffer::GetSpecs() {
	return m_Specs;
}

const ArcticFox::Graphics::FrameBufferSpec & ArcticFox::Graphics::OpenGL::OpenGLFrameBuffer::GetSpecs() const {
	return m_Specs;
}

void ArcticFox::Graphics::OpenGL::OpenGLFrameBuffer::Bind() {
	glBindFramebuffer(GL_FRAMEBUFFER, m_FrameBuffer);
}
void ArcticFox::Graphics::OpenGL::OpenGLFrameBuffer::Unbind() {
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

uint32_t ArcticFox::Graphics::OpenGL::OpenGLFrameBuffer::GetColorAttachment0() const {
	return m_ColorAttachment0;
}

uint32_t ArcticFox::Graphics::OpenGL::OpenGLFrameBuffer::GetDepthAttachment() const {
	return m_DepthAttachment0;
}

ArcticFox::Graphics::OpenGL::OpenGLFrameBuffer::~OpenGLFrameBuffer() {
	//glDeleteFramebuffers(1, &m_FrameBuffer);
}

void ArcticFox::Graphics::OpenGL::OpenGLFrameBuffer::Invalidate() {
	glCreateFramebuffers(1, &m_FrameBuffer);
	glBindFramebuffer(GL_FRAMEBUFFER, m_FrameBuffer);

	glViewport(0, 0, m_Specs.Width, m_Specs.Height);

	glCreateTextures(GL_TEXTURE_2D, 1, &m_ColorAttachment0);
	glBindTexture(GL_TEXTURE_2D, m_ColorAttachment0);
	//glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, m_Specs.Width, m_Specs.Height, 0, GL_RGBA,  GL_UNSIGNED_BYTE, nullptr);
	glTexStorage2D(GL_TEXTURE_2D, 1, GL_RGBA8, m_Specs.Width, m_Specs.Height);
	glTextureParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTextureParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_ColorAttachment0, 0);


	glCreateTextures(GL_TEXTURE_2D, 1, &m_DepthAttachment0);
	glBindTexture(GL_TEXTURE_2D, m_DepthAttachment0);
	glTexStorage2D(GL_TEXTURE_2D, 1, GL_DEPTH24_STENCIL8, m_Specs.Width, m_Specs.Height);
	//glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH24_STENCIL8, m_Specs.Width, m_Specs.Height, 0, GL_DEPTH_STENCIL, GL_UNSIGNED_INT_24_8, nullptr);

	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_TEXTURE_2D, m_DepthAttachment0, 0);

	bool completed = glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE;

	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}