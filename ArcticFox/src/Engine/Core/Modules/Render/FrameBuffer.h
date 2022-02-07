#pragma once
#include <stdint.h>
#include <vector>

namespace ArcticFox {
	namespace Graphics {
		enum class FramebufferTextureFormat {
			None = 0,

			RED_INTIGER,

			RGBA8,

			DEPTH24STENCIL8,

			Depth = DEPTH24STENCIL8

		};

		struct FramebufferTextureSpecification {
			FramebufferTextureSpecification() = default;
			FramebufferTextureSpecification(FramebufferTextureFormat format) : m_format(format) {}
			FramebufferTextureFormat m_format = FramebufferTextureFormat::None;
			//filtering and wrapping
		};

		struct FramebufferAttachmentSpecification {
			FramebufferAttachmentSpecification() = default;
			FramebufferAttachmentSpecification(std::initializer_list<FramebufferTextureSpecification> attachments) : Attachments(attachments) {}
			std::vector<FramebufferTextureSpecification> Attachments;
		};

		struct FrameBufferSpec {
			uint32_t Width, Height;
			uint32_t Samples = 1;
			FramebufferAttachmentSpecification Attachemtns;

			bool SwapChainTarget = false;
		};

		class FrameBuffer {
		public:
			virtual FrameBufferSpec& GetSpecs() = 0;
			virtual const FrameBufferSpec& GetSpecs() const = 0;

			virtual void Bind() = 0;
			virtual void Unbind() = 0;

			virtual void Resize(uint32_t x, uint32_t y) = 0;

			virtual int ReadPixel(uint32_t attachmentID, uint32_t x, uint32_t y) = 0;
			virtual void ClearColorAttachemnt(uint32_t id, int value) = 0;

			virtual uint32_t GetColorAttachment(uint32_t index = 0) const = 0;
			virtual uint32_t GetDepthAttachment() const = 0;

			static FrameBuffer* Create(const FrameBufferSpec& spec);

			virtual ~FrameBuffer();
		};
	}
}