#pragma once
#include <glm/glm.hpp>
#include <string>

namespace Graphics {
	class Shader {
	public:
		Shader();

		static Shader* Create();

		virtual void Bind() = 0;
		virtual void Unbind() = 0;

		virtual void UploadUniform(const std::string& name, const glm::mat4& matrix) = 0;
		virtual void UploadUniform(const std::string& name, int value) = 0;

		~Shader();

	private:

	};
}