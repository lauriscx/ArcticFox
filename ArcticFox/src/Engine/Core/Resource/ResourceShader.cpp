#include "ResourceShader.h"
#include "Core/FileSystem/VFS/VFS.h"
#include "Core/FileSystem/File.h"
#include <iostream>
#include "Core/XML/XML.h"
#include "Core/ResourceManager/ResourceManager.h"

ArcticFox::Graphics::RecourceShader::RecourceShader() { }

const char* ArcticFox::Graphics::RecourceShader::Get() {
	return m_Resource.c_str();
}

bool ArcticFox::Graphics::RecourceShader::IsAvailable() {
	return m_Resource != "";
}

bool ArcticFox::Graphics::RecourceShader::Load(std::filesystem::path file) {
	AppFrame::Resource::Load(file);

	std::shared_ptr<AppFrame::File> _file = AppFrame::VFS::GetInstance()->ReadFile(file);
	if (_file && _file->IsDataAvailable()) {
		m_Resource = _file->GetData();
		//delete _file;//It will erease all allocated memory inside(mean data which is char*).
		return true;
	}
	return false;
}

size_t ArcticFox::Graphics::RecourceShader::GetMemoryUsage() {
	return sizeof(this) + sizeof(m_Resource);//Probably not correct.
}

ArcticFox::Graphics::RecourceShader::~RecourceShader() {
	//delete m_Resource;
	AppFrame::Resource::~Resource();
	if (!m_File.empty()) {
		AppFrame::ResourceManager::GetInstance()->ReleaseResource<RecourceShader>(this);
	}
}