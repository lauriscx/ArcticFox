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

				virtual uint32_t GetColorAttachment0() const override;
				virtual uint32_t GetDepthAttachment() const override;

				virtual ~OpenGLFrameBuffer();

				void Invalidate();
			private:
				FrameBufferSpec m_Specs;
				uint32_t m_FrameBuffer = 0;
				uint32_t m_ColorAttachment0 = 0;
				uint32_t m_DepthAttachment0 = 0;
			};
		}
	}
}