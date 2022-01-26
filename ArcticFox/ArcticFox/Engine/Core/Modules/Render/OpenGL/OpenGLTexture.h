#pragma once
#include "../Texture.h"
#include "Glad/glad.h"

namespace Graphics {
	namespace OpenGL {
		class OpenGLTexture2D : public Texture2D {
		public:
			OpenGLTexture2D(uint32_t width, uint32_t height);
			OpenGLTexture2D(AppFrame::ResourceTexture* texture);

			virtual int GetWidth() const override;
			virtual int GetHeight() const override;

			virtual void SetData(void* data, uint32_t size) override;

			virtual void Bind(unsigned int slot = 0) const override;
			virtual void Unbind() const override;

			virtual ~OpenGLTexture2D();

		private:
			uint32_t m_Width;
			uint32_t m_Height;

			uint32_t m_Texture;

			GLenum m_InternalFormat, m_DataFormat;
		};
	}
}