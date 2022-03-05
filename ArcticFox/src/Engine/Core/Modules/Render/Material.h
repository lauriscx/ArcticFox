#pragma once
#include <AppFrame.h>
#include "Engine/Core/Modules/Render/Buffer.h"
#include "Engine/Core/Modules/Render/Shader.h"
#include "Engine/Core/Modules/Render/Texture.h"

namespace ArcticFox {
	namespace Graphics {
		class Material {
		public:
			Material();

			void LoadShader(std::filesystem::path verpath, std::filesystem::path fragpath);

			void AddTexture(uint32_t slot, const std::shared_ptr<Texture2D>& texture);

			inline std::shared_ptr<Shader> GetShader() { return m_Shader; }
			inline std::map<std::shared_ptr<Texture2D>, std::pair<std::string, uint32_t>> GetTextures() { return m_Textures; }

			~Material();
		private:
			std::shared_ptr<Shader> m_Shader;
			std::map<std::shared_ptr<Texture2D>, std::pair<std::string, uint32_t>> m_Textures;
		};
	}
}