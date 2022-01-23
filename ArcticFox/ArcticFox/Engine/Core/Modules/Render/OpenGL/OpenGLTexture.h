#pragma once
#include "../Texture.h"

namespace Graphics {
	namespace OpenGL {
		class OpenGLTexture2D : public Texture2D {
		public:
			OpenGLTexture2D(AppFrame::ResourceTexture* texture);

			virtual int GetWidth() const override;
			virtual int GetHeight() const override;
			virtual void Bind(unsigned int slot = 0) const override;
			virtual void Unbind() const override;

			virtual ~OpenGLTexture2D();

		private:
			int m_Width;
			int m_Height;

			unsigned int m_Texture;
		};
	}
}