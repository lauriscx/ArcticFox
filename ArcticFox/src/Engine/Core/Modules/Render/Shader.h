#pragma once
#include <glm/glm.hpp>
#include <string>
#include <unordered_map>
#include <filesystem>

namespace ArcticFox {
	namespace Graphics {
		class Shader {
		public:
			Shader();

			static Shader* Create(const std::string& name, const std::string& vertex, const std::string& fragment);

			virtual const std::string& GetName() const = 0;

			virtual void Bind() = 0;
			virtual void Unbind() = 0;

			virtual void UploadUniform(const std::string& name, const glm::mat4& matrix) = 0;
			virtual void UploadUniform(const std::string& name, const glm::vec4& vector) = 0;
			virtual void UploadUniform(const std::string& name, const glm::vec3& vector) = 0;
			virtual void UploadUniform(const std::string& name, const glm::vec2& vector) = 0;
			virtual void UploadUniform(const std::string& name, int value) = 0;
			virtual void UploadUniform(const std::string& name, int* value, uint32_t count) = 0;

			~Shader();
		};

		class ShaderLibrary {
		public:
			void Add(Shader* shader);
			Shader* Load(const std::string& name, const std::filesystem::path & pathVer, const std::filesystem::path & pathFrag);
			Shader* Load(const std::filesystem::path & pathVer, const std::filesystem::path & pathFrag);
			Shader* Get(const std::string& name);
			bool Exists(const std::string& name) const;
		private:
			std::unordered_map<std::string, Shader*> m_Shader;
		};
	}
}