#pragma once
#include "Application/Resources/ResourceTexture.h"

namespace ArcticFox {
	namespace Graphics {
		class Texture {
		public:
			virtual int GetWidth() const = 0;
			virtual int GetHeight() const = 0;

			virtual void SetData(void* data, uint32_t size) = 0;

			virtual void Bind(uint32_t slot = 0) const = 0;
			virtual void Unbind() const = 0;

			virtual uint32_t ID() = 0;

			virtual ~Texture() = default;
		};

		class Texture2D : public Texture {
		public:
			static Texture2D* Create(uint32_t width, uint32_t height);
			static Texture2D* Create(AppFrame::ResourceTexture* texture);

			virtual ~Texture2D() = default;
		};
	}
}