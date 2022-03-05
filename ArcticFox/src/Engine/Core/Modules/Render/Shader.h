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

			static std::shared_ptr<Shader> Create(const std::string& name, const std::string& vertex, const std::string& fragment, bool spirv = false);

			virtual const std::string& GetName() const = 0;

			virtual void Bind() = 0;
			virtual void Unbind() = 0;

			virtual void UploadUniform(const std::string& name, const glm::mat4& matrix) = 0;
			virtual void UploadUniform(const std::string& name, const glm::vec4& vector) = 0;
			virtual void UploadUniform(const std::string& name, const glm::vec3& vector) = 0;
			virtual void UploadUniform(const std::string& name, const glm::vec2& vector) = 0;
			virtual void UploadUniform(const std::string& name, int value) = 0;
			virtual void UploadUniform(const std::string& name, int* value, uint32_t count) = 0;

			virtual std::vector<std::pair<std::string, uint32_t>> GetTextureSlots() = 0;

			~Shader();
		};

		class ShaderLibrary {
		public:
			void Add(std::shared_ptr<Shader> shader);
			std::shared_ptr<Shader> Load(const std::string& name, const std::filesystem::path & pathVer, const std::filesystem::path & pathFrag);
			std::shared_ptr<Shader> Load(const std::filesystem::path & pathVer, const std::filesystem::path & pathFrag);
			std::shared_ptr<Shader> Get(const std::string& name);
			bool Exists(const std::string& name) const;
		private:
			std::unordered_map<std::string, std::shared_ptr<Shader>> m_Shader;
		};
	}
}