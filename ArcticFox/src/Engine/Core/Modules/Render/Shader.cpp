#include "OpenGL/OpenGLShader.h"
#include "RendererAPI.h"

#include "Engine/Core/Resource/ResourceShader.h"

ArcticFox::Graphics::Shader::Shader() {}

std::shared_ptr<ArcticFox::Graphics::Shader> ArcticFox::Graphics::Shader::Create(const std::string& name, const std::string& vertex, const std::string& fragment, bool spirv) {
	switch (RendererAPI::GetAPI()) {
		case RendererAPI::API::None:		return nullptr;
		case RendererAPI::API::OpenGL:		return std::make_shared<OpenGL::OpenGLShader>(name, vertex, fragment, spirv);
		case RendererAPI::API::Directx9:	return nullptr;
		case RendererAPI::API::Directx10:	return nullptr;
		case RendererAPI::API::Vulkan:		return nullptr;
		case RendererAPI::API::Metal:		return nullptr;
		default: return nullptr;
	}
}

ArcticFox::Graphics::Shader::~Shader() {}


void ArcticFox::Graphics::ShaderLibrary::Add(std::shared_ptr<Shader> shader) {
	auto& name = shader->GetName();
	m_Shader[name] = shader;
}
std::shared_ptr<ArcticFox::Graphics::Shader> ArcticFox::Graphics::ShaderLibrary::Load(const std::string & name, const std::filesystem::path & pathVer, const std::filesystem::path & pathFrag) {
	Graphics::RecourceShader vertex = AppFrame::ResourceManager::GetInstance()->GetResource<Graphics::RecourceShader>(pathVer);
	Graphics::RecourceShader fragment = AppFrame::ResourceManager::GetInstance()->GetResource<Graphics::RecourceShader>(pathFrag);

	std::shared_ptr<Shader> Shader = Graphics::Shader::Create(name, vertex.Get(), fragment.Get());
	Add(Shader);

	return Shader;
}
std::shared_ptr<ArcticFox::Graphics::Shader> ArcticFox::Graphics::ShaderLibrary::Load(const std::filesystem::path & pathVer, const std::filesystem::path & pathFrag) {
	Graphics::RecourceShader vertex = AppFrame::ResourceManager::GetInstance()->GetResource<Graphics::RecourceShader>(pathVer);
	Graphics::RecourceShader fragment = AppFrame::ResourceManager::GetInstance()->GetResource<Graphics::RecourceShader>(pathFrag);

	std::shared_ptr<Shader> Shader = Graphics::Shader::Create(pathVer.stem().string(), vertex.Get(), fragment.Get());
	Add(Shader);

	return Shader;
}
std::shared_ptr<ArcticFox::Graphics::Shader> ArcticFox::Graphics::ShaderLibrary::Get(const std::string & name) {
	return m_Shader[name];
}
bool ArcticFox::Graphics::ShaderLibrary::Exists(const std::string & name) const {
	return m_Shader.find(name) != m_Shader.end();
}