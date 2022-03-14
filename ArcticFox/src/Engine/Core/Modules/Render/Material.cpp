#include "Material.h"

ArcticFox::Graphics::Material::Material() {}

void ArcticFox::Graphics::Material::LoadShader(std::filesystem::path verpath, std::filesystem::path fragpath) {
	vertex = AppFrame::ResourceManager::GetInstance()->GetResource<Graphics::RecourceShader>(verpath);
	fragment = AppFrame::ResourceManager::GetInstance()->GetResource<Graphics::RecourceShader>(fragpath);
	m_Shader = Shader::Create("Material", vertex.Get(), fragment.Get(), true);
}

void ArcticFox::Graphics::Material::AddTexture(uint32_t slot, const std::shared_ptr<Texture2D>& texture) {
	for (uint32_t i = 0; i < m_Shader->GetTextureSlots().size(); i++) {
		if (m_Shader->GetTextureSlots()[i].second == slot) {
			m_Textures[texture] = std::make_pair(m_Shader->GetTextureSlots()[i].first, m_Shader->GetTextureSlots()[i].second);
		}
	}
}

ArcticFox::Graphics::Material::~Material() {}