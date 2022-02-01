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

		template<typename T>
		void RemoveComponent() { m_Scene->m_Registry.remove<T>(m_EntityID); };

		operator bool() const { return m_EntityID != entt::null; }
		operator uint32_t() const { return (uint32_t)m_EntityID; }
		bool operator==(const Entity& other) const { return other.m_EntityID == m_EntityID && other.m_Scene == m_Scene; }
		bool operator!=(const Entity& other) const { return !(*this==other); }
		operator entt::entity() const { return m_EntityID; }


	private:
		entt::entity m_EntityID { entt::null };
		Scene* m_Scene;
	};
}