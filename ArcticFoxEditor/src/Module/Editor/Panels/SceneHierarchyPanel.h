#pragma once
#include <AppFrame.h>
#include "Engine/Core/ECS/Entity.h"

namespace ArcticFox {
	class Scene;
};

namespace Editor {
	class SceneHierarchyPanel {
	public:
		SceneHierarchyPanel() = default;
		SceneHierarchyPanel(ArcticFox::Scene* scene);

		void SetContext(ArcticFox::Scene* scene);
		void SetHoveredEntity(ArcticFox::Entity entity) { m_HoveredEntity = entity; };
		void SetSelectedEntity(ArcticFox::Entity entity) { m_SelectionContext = entity; };

		ArcticFox::Entity GetSelectedEntity() const;
		ArcticFox::Entity GetHoveredEntity() const { return m_HoveredEntity; };

		void OnImGuiRender();
	private:
		void DrawEntityNode(ArcticFox::Entity entity);
		void DrawComponents(ArcticFox::Entity entity);

	private:
		ArcticFox::Scene* m_Scene;
		ArcticFox::Entity m_SelectionContext;
		ArcticFox::Entity m_HoveredEntity;
	};
}