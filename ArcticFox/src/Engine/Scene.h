#pragma once
#include "entt.hpp"

namespace ArcticFox {
	class Entity;
	class Scene {
	public:
		Scene();

		Entity CreateEntity(std::string name);

		void Update(float deltaTime);

		~Scene();
	private:
		entt::registry m_Registry;
		friend class Entity;
	};
}