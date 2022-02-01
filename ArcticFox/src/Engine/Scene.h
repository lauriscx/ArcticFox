#pragma once
#include "entt.hpp"
#include <AppFrame.h>

namespace ArcticFox {
	class Entity;
	class Scene : public AppFrame::EventHandler {
	public:
		Scene();

		Entity CreateEntity(std::string name);

		void Update(float deltaTime);

		// Inherited via EventHandler
		virtual bool OnEvent(AppFrame::BasicEvent & event) override;

		void OnVieportResize(uint32_t width, uint32_t height);

		inline entt::registry& GetRegistry() { return m_Registry; }

		~Scene();
	private:
		uint32_t m_ViewPortWidth = 0, m_ViewPortHeight = 0;

		entt::registry m_Registry;
		friend class Entity;
	};
}