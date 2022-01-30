#pragma once
#include <AppFrame.h>
#include "Core/ResourceManager/Resource.h"

namespace Graphics {
	class RecourceShader : public AppFrame::Resource {
	public:
		RecourceShader();

		const char* Get();

		virtual bool IsAvailable() override;
		virtual bool Load(std::filesystem::path file) override;

		virtual size_t GetMemoryUsage() override;

		~RecourceShader();
	private:
		std::string m_Resource;
	};
}