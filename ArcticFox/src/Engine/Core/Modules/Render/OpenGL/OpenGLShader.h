#pragma once
#include "../Shader.h"
#include "Glad/glad.h"

namespace ArcticFox {
	namespace Graphics {
		namespace OpenGL {
			class OpenGLShader : public Shader {
			public:
				OpenGLShader(const std::string& name, const std::string& vertex, const std::string& fragment, bool spirv = false);
				~OpenGLShader();

				virtual const std::string& GetName() const override;

				virtual void Bind() override;
				virtual void Unbind() override;

				virtual void UploadUniform(const std::string& name, const glm::mat4& matrix) override;
				virtual void UploadUniform(const std::string& name, const glm::vec4& vector) override;
				virtual void UploadUniform(const std::string& name, const glm::vec3& vector) override;
				virtual void UploadUniform(const std::string& name, const glm::vec2& vector) override;
				virtual void UploadUniform(const std::string& name, int value) override;
				virtual void UploadUniform(const std::string& name, int* value, uint32_t count) override;

			private:
				unsigned int m_VertexShader;
				unsigned int m_FragmentShader;
				unsigned int m_Shader;
				std::string m_Name;

				//SPIR-V implementation
			private:
				std::unordered_map<GLenum, std::vector<uint32_t>> CompileVulkanBinaries(const std::unordered_map<GLenum, std::string>& shadersSourceCode);
				std::unordered_map<GLenum, std::vector<uint32_t>> CompileOpenGLBinaries(const std::unordered_map<GLenum, std::vector<uint32_t>>& shadersSourceCode);
				void CreateShaderProgram(std::unordered_map<GLenum, std::vector<uint32_t>> openglBinary);
				void CreateShaderProgram(const std::unordered_map<GLenum, std::string>& shadersSourceCode);
			};
		}
	}
}