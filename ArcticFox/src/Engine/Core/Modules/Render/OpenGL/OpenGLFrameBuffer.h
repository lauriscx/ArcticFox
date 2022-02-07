#pragma once
#include "../FrameBuffer.h"

namespace ArcticFox {
	namespace Graphics {
		namespace OpenGL {
			class OpenGLFrameBuffer : public FrameBuffer {
			public:
				OpenGLFrameBuffer(const FrameBufferSpec & spec);

				virtual FrameBufferSpec& GetSpecs() override;
				virtual const FrameBufferSpec& GetSpecs() const override;

				virtual void Bind() override;
				virtual void Unbind() override;

				virtual void Resize(uint32_t x, uint32_t y) override;

				virtual int ReadPixel(uint32_t attachmentID, uint32_t x, uint32_t y) override;
				virtual void ClearColorAttachemnt(uint32_t id, int value) override;

				virtual uint32_t GetColorAttachment(uint32_t index = 0) const override { return m_ColorAttachments[index]; };
				virtual uint32_t GetDepthAttachment() const override { return m_DepthAttachment; };

				virtual ~OpenGLFrameBuffer();

				void Invalidate();
			private:
				FrameBufferSpec m_Specs;
				uint32_t m_FrameBuffer = 0;
				std::vector <uint32_t> m_ColorAttachments;
				uint32_t m_DepthAttachment = 0;

				std::vector<FramebufferTextureSpecification> m_ColarAttachmentSpecification;
				FramebufferTextureSpecification m_DepthAttachmentSpecification;
			};
		}
	}
}