#include "ResourceShader.h"
#include "Core/FileSystem/VFS/VFS.h"
#include "Core/FileSystem/File.h"
#include <iostream>
#include "Core/XML/XML.h"


Graphics::RecourceShader::RecourceShader() { }

const char* Graphics::RecourceShader::Get() {
	return m_Resource.c_str();
}

bool Graphics::RecourceShader::IsAvailable() {
	return m_Resource != "";
}

bool Graphics::RecourceShader::Load(std::filesystem::path file) {
	AppFrame::File* _file = AppFrame::VFS::GetInstance()->ReadFile(file);
	if (_file && _file->IsDataAvailable()) {
		m_Resource = _file->GetData();
		delete _file;//It will erease all allocated memory inside(mean data which is char*).
		return true;
	}
	return false;
}

size_t Graphics::RecourceShader::GetMemoryUsage() {
	return sizeof(this) + sizeof(m_Resource);//Probably not correct.
}

Graphics::RecourceShader::~RecourceShader() {
	//delete m_Resource;
}