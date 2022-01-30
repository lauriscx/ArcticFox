#pragma once
#include <stdint.h>
#include "entt.hpp"

namespace ArcticFox {
	class Scene;
	class Entity {
	public:
		Entity() = default;
		Entity(entt::entity entity, Scene* Scene);

		template<typename T>
		bool HasComponent() { return m_Scene->m_Registry.has<T>(m_EntityID); };

		template<typename T, typename... Args>
		T& AddComponent(Args&&... args) { return m_Scene->m_Registry.emplace<T>(m_EntityID, std::forward<Args>(args)...); };

		template<typename T>
		T& GetComponent() { return m_Scene->m_Registry.get<T>(m_EntityID); };

	private:
		entt::entity m_EntityID{0};
		Scene* m_Scene;
	};
}