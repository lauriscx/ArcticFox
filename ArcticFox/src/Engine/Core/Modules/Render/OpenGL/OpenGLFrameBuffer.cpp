#include "OpenGLFrameBuffer.h"
#include "Glad/glad.h"

namespace ArcticFox::Graphics::OpenGL {
	static const uint32_t s_MaxFramebufferSize = 8192;

	static uint32_t TextureTarget(bool multisampled) {
		return multisampled ? GL_TEXTURE_2D_MULTISAMPLE : GL_TEXTURE_2D;
	}

	static void BindTexture(bool multisampled, uint32_t id) {
		glBindTexture(TextureTarget(multisampled), id);
	}

	static void CreateTextures(bool multisampled, uint32_t count, uint32_t* outID) {
		glCreateTextures(TextureTarget(multisampled), count, outID);
	}

	static bool IsDepthFormat(FramebufferTextureFormat format) {
		switch (format) {
			case FramebufferTextureFormat::DEPTH24STENCIL8:  return true;
			default: return false;
		}
	}
	static GLenum TextureFormat(FramebufferTextureFormat format) {
		switch (format) {
		case FramebufferTextureFormat::RGBA8:  return GL_RGBA8;
		case FramebufferTextureFormat::RED_INTIGER:  return GL_RED_INTEGER;
		default: return false;
		}
	}
	/*static GLenum TextureDataType(FramebufferTextureFormat format) {
		switch (format) {
		case FramebufferTextureFormat::RGBA8:  return GL_UNSIGNED_BYTE;
		case FramebufferTextureFormat::RED_INTIGER:  return GL_RED_INTEGER;
		default: return false;
		}
	}*/

	static void AttachColorTexture(uint32_t id, int samples, GLenum interbalFormat, GLenum format, uint32_t width, uint32_t height, int index) {
		bool multisampled = samples > 1;
		if (multisampled) {
			glTexImage2DMultisample(GL_TEXTURE_2D_MULTISAMPLE, samples, interbalFormat, width, height, GL_FALSE);
		} else {
			glTexImage2D(GL_TEXTURE_2D, 0, interbalFormat, width, height, 0, format, GL_UNSIGNED_BYTE, nullptr);
			
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

		}

		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + index, TextureTarget(multisampled), id, 0);
	}

	static void AttachDepthTexture(uint32_t id, int samples, GLenum attachmentType, GLenum format, uint32_t width, uint32_t height) {
		bool multisampled = samples > 1;
		if (multisampled) {
			glTexImage2DMultisample(GL_TEXTURE_2D_MULTISAMPLE, samples, format, width, height, GL_FALSE);
		}
		else {
			glTexStorage2D(GL_TEXTURE_2D, 1, format, width, height);

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

		}

		glFramebufferTexture2D(GL_FRAMEBUFFER, attachmentType, TextureTarget(multisampled), id, 0);
	}
}

ArcticFox::Graphics::OpenGL::OpenGLFrameBuffer::OpenGLFrameBuffer(const FrameBufferSpec & spec) : m_Specs(spec) {
	for (auto attachment : spec.Attachemtns.Attachments) {
		if (!IsDepthFormat(attachment.m_format)) {
			m_ColarAttachmentSpecification.push_back(attachment);
		} else {
			m_DepthAttachmentSpecification = attachment;
		}
	}

	Invalidate();
}

ArcticFox::Graphics::FrameBufferSpec & ArcticFox::Graphics::OpenGL::OpenGLFrameBuffer::GetSpecs() {
	return m_Specs;
}

const ArcticFox::Graphics::FrameBufferSpec & ArcticFox::Graphics::OpenGL::OpenGLFrameBuffer::GetSpecs() const {
	return m_Specs;
}

void ArcticFox::Graphics::OpenGL::OpenGLFrameBuffer::Bind() {
	glViewport(0, 0, m_Specs.Width, m_Specs.Height);
	glBindFramebuffer(GL_FRAMEBUFFER, m_FrameBuffer);
}
void ArcticFox::Graphics::OpenGL::OpenGLFrameBuffer::Unbind() {
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void ArcticFox::Graphics::OpenGL::OpenGLFrameBuffer::Resize(uint32_t x, uint32_t y) {
	m_Specs.Width = x;
	m_Specs.Height = y;
	Invalidate();
}

int ArcticFox::Graphics::OpenGL::OpenGLFrameBuffer::ReadPixel(uint32_t attachmentID, uint32_t x, uint32_t y) {
	//glBindFramebuffer(GL_FRAMEBUFFER, m_FrameBuffer);
	glReadBuffer(GL_COLOR_ATTACHMENT0 + attachmentID);
	int pixelData;
	glReadPixels(x, y, 1, 1, TextureFormat(m_ColarAttachmentSpecification[attachmentID].m_format), GL_INT, &pixelData);
	//glBindFramebuffer(GL_FRAMEBUFFER, 0);
	return pixelData;
}

void ArcticFox::Graphics::OpenGL::OpenGLFrameBuffer::ClearColorAttachemnt(uint32_t id, int value) {
	auto& spec = m_ColarAttachmentSpecification[id];
	
	//glClearTexImage(m_ColorAttachments[id], 0, GL_RED_INTEGER, GL_INT, value);
	glClearTexImage(m_ColorAttachments[id], 0, TextureFormat(spec.m_format), GL_INT, &value);
}

ArcticFox::Graphics::OpenGL::OpenGLFrameBuffer::~OpenGLFrameBuffer() {
	glDeleteFramebuffers(1, &m_FrameBuffer);
	glDeleteTextures(m_ColorAttachments.size(), m_ColorAttachments.data());
	glDeleteTextures(1, &m_DepthAttachment);

	m_ColorAttachments.clear();
	m_DepthAttachment = 0;
}

void ArcticFox::Graphics::OpenGL::OpenGLFrameBuffer::Invalidate() {
	if (m_FrameBuffer) {
		glDeleteFramebuffers(1, &m_FrameBuffer);
		glDeleteTextures(m_ColorAttachments.size(), m_ColorAttachments.data());
		glDeleteTextures(1, &m_DepthAttachment);

		m_ColorAttachments.clear();
		m_DepthAttachment = 0;
	}
	glCreateFramebuffers(1, &m_FrameBuffer);
	glBindFramebuffer(GL_FRAMEBUFFER, m_FrameBuffer);

	bool mulsample = m_Specs.Samples > 1;

	if (m_ColarAttachmentSpecification.size()) {
		m_ColorAttachments.resize(m_ColarAttachmentSpecification.size());
		CreateTextures(mulsample, m_ColorAttachments.size(), m_ColorAttachments.data());

		for (size_t i = 0; i < m_ColorAttachments.size(); i++)
		{
			BindTexture(mulsample, m_ColorAttachments[i]);
			switch (m_ColarAttachmentSpecification[i].m_format) {
			case FramebufferTextureFormat::RGBA8: AttachColorTexture(m_ColorAttachments[i], m_Specs.Samples, GL_RGBA8, GL_RGBA, m_Specs.Width, m_Specs.Height, i); break;
			case FramebufferTextureFormat::RED_INTIGER: AttachColorTexture(m_ColorAttachments[i], m_Specs.Samples, GL_R32I, GL_RED_INTEGER, m_Specs.Width, m_Specs.Height, i); break;
			default:
				break;
			}
		}
	}

	if (m_DepthAttachmentSpecification.m_format != FramebufferTextureFormat::None) {
		CreateTextures(mulsample, 1, &m_DepthAttachment);
		BindTexture(mulsample, m_DepthAttachment);
		switch (m_DepthAttachmentSpecification.m_format) {
		case FramebufferTextureFormat::DEPTH24STENCIL8: { 
			AttachDepthTexture(m_DepthAttachment, m_Specs.Samples, GL_DEPTH_STENCIL_ATTACHMENT, GL_DEPTH24_STENCIL8, m_Specs.Width, m_Specs.Height);
			break;
		}
		default:
			break;
		}
	}

	if (m_ColorAttachments.size() > 1) {
		GLenum buffers[6] = { GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1, GL_COLOR_ATTACHMENT2, GL_COLOR_ATTACHMENT3, GL_COLOR_ATTACHMENT4, GL_COLOR_ATTACHMENT5 };
		glDrawBuffers(m_ColorAttachments.size(), buffers);
	} else if(m_ColorAttachments.empty()) {
		glDrawBuffer(GL_NONE);
	}


	/*glViewport(0, 0, m_Specs.Width, m_Specs.Height); 

	glCreateTextures(GL_TEXTURE_2D, 1, &m_ColorAttachments[0]);
	glBindTexture(GL_TEXTURE_2D, m_ColorAttachments[0]);
	//glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, m_Specs.Width, m_Specs.Height, 0, GL_RGBA,  GL_UNSIGNED_BYTE, nullptr);
	glTexStorage2D(GL_TEXTURE_2D, 1, GL_RGBA8, m_Specs.Width, m_Specs.Height);
	glTextureParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTextureParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_ColorAttachments[0], 0);


	glCreateTextures(GL_TEXTURE_2D, 1, &m_DepthAttachment);
	glBindTexture(GL_TEXTURE_2D, m_DepthAttachment);
	glTexStorage2D(GL_TEXTURE_2D, 1, GL_DEPTH24_STENCIL8, m_Specs.Width, m_Specs.Height);
	//glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH24_STENCIL8, m_Specs.Width, m_Specs.Height, 0, GL_DEPTH_STENCIL, GL_UNSIGNED_INT_24_8, nullptr);

	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_TEXTURE_2D, m_DepthAttachment, 0);*/

	bool completed = glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE;

	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}