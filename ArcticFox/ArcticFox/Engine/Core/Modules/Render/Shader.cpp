#include "OpenGL/OpenGLShader.h"
#include "RendererAPI.h"


#include "Engine/Core/Resource/ResourceShader.h"

Graphics::Shader::Shader() {}

Graphics::Shader * Graphics::Shader::Create(const std::string& name, const std::string& vertex, const std::string& fragment) {
	switch (RendererAPI::GetAPI()) {
		case RendererAPI::API::None:		return nullptr;
		case RendererAPI::API::OpenGL:		return new OpenGL::OpenGLShader(name, vertex, fragment);
		case RendererAPI::API::Directx9:	return nullptr;
		case RendererAPI::API::Directx10:	return nullptr;
		case RendererAPI::API::Vulkan:		return nullptr;
		case RendererAPI::API::Metal:		return nullptr;
		default: return nullptr;
	}
}

Graphics::Shader::~Shader() {}


void Graphics::ShaderLibrary::Add(Shader * shader) {
	auto& name = shader->GetName();
	m_Shader[name] = shader;
}
Graphics::Shader * Graphics::ShaderLibrary::Load(const std::string & name, const std::filesystem::path & pathVer, const std::filesystem::path & pathFrag) {
	Graphics::RecourceShader* vertex = AppFrame::ResourceManager::GetInstance()->GetResource<Graphics::RecourceShader>(pathVer);
	Graphics::RecourceShader* fragment = AppFrame::ResourceManager::GetInstance()->GetResource<Graphics::RecourceShader>(pathFrag);

	Graphics::Shader* Shader = Graphics::Shader::Create(name, vertex->Get(), fragment->Get());
	Add(Shader);

	AppFrame::ResourceManager::GetInstance()->ReleaseResource(pathVer);
	AppFrame::ResourceManager::GetInstance()->ReleaseResource(pathFrag);
	return Shader;
}
Graphics::Shader * Graphics::ShaderLibrary::Load(const std::filesystem::path & pathVer, const std::filesystem::path & pathFrag) {
	Graphics::RecourceShader* vertex = AppFrame::ResourceManager::GetInstance()->GetResource<Graphics::RecourceShader>(pathVer);
	Graphics::RecourceShader* fragment = AppFrame::ResourceManager::GetInstance()->GetResource<Graphics::RecourceShader>(pathFrag);

	Graphics::Shader* Shader = Graphics::Shader::Create(pathVer.stem().string(), vertex->Get(), fragment->Get());
	Add(Shader);

	AppFrame::ResourceManager::GetInstance()->ReleaseResource(pathVer);
	AppFrame::ResourceManager::GetInstance()->ReleaseResource(pathFrag);
	return Shader;
}
Graphics::Shader * Graphics::ShaderLibrary::Get(const std::string & name) {
	return m_Shader[name];
}
bool Graphics::ShaderLibrary::Exists(const std::string & name) const {
	return m_Shader.find(name) != m_Shader.end();
}