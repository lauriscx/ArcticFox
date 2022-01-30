#pragma once
#include <stdint.h>

namespace ArcticFox {
	namespace Graphics {
		struct FrameBufferSpec {
			uint32_t Width, Height;
			uint32_t Samples = 1;

			bool SwapChainTarget = false;
		};

		class FrameBuffer {
		public:
			virtual FrameBufferSpec& GetSpecs() = 0;
			virtual const FrameBufferSpec& GetSpecs() const = 0;

			virtual void Bind() = 0;
			virtual void Unbind() = 0;

			virtual void Resize(uint32_t x, uint32_t y) = 0;

			virtual uint32_t GetColorAttachment0() const = 0;
			virtual uint32_t GetDepthAttachment() const = 0;

			static FrameBuffer* Create(const FrameBufferSpec& spec);
		};
	}
}