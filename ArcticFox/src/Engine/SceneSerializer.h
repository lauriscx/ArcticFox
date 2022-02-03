#pragma once
#include <filesystem>

namespace ArcticFox {
	class Scene;
	class SceneSerializer {
	public:
		SceneSerializer(Scene* scene);

		void Serialize(const std::filesystem::path& path);
		void SerializeRuntime(const std::filesystem::path& path);

		bool Derialize(const std::filesystem::path& path);
		bool DerializeRuntime(const std::filesystem::path& path);
	private:
		Scene* m_Scene;
	};
}