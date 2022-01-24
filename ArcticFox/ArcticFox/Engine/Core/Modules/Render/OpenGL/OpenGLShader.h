#pragma once
#include "../Shader.h"

namespace Graphics {
	namespace OpenGL {
		class OpenGLShader : public Shader {
		public:
			OpenGLShader(const std::string& name, const std::string& vertex, const std::string& fragment);
			~OpenGLShader();

			virtual const std::string& GetName() const override;

			virtual void Bind() override;
			virtual void Unbind() override;

			virtual void UploadUniform(const std::string& name, const glm::mat4& matrix) override;
			virtual void UploadUniform(const std::string& name, int value) override;

		private:
			unsigned int m_VertexShader;
			unsigned int m_FragmentShader;
			unsigned int m_Shader;
			std::string m_Name;
		};
	}
}