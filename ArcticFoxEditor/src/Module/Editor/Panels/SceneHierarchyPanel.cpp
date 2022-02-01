#include "SceneHierarchyPanel.h"
#include "Engine/Scene.h"
#include "Engine/Core/ECS/Components.h"
#include "entt.hpp"
#include "glm/gtc/type_ptr.hpp"

Editor::SceneHierarchyPanel::SceneHierarchyPanel(ArcticFox::Scene * scene) : m_Scene(scene) {
	
}

void Editor::SceneHierarchyPanel::SetContext(ArcticFox::Scene * scene) {
	m_Scene = scene;
}

void Editor::SceneHierarchyPanel::OnImGuiRender() {
	ImGui::Begin("Scene hierarchy");

	m_Scene->GetRegistry().each([&](auto entityID) {
		DrawEntityNode({ entityID, m_Scene });
	});

	if (ImGui::IsMouseDown(0) && ImGui::IsWindowHovered()) {
		m_SelectionContext = {};
	}

	ImGui::End();

	ImGui::Begin("Properties");
	if(m_SelectionContext)
		DrawComponents(m_SelectionContext);
	ImGui::End();
}

void Editor::SceneHierarchyPanel::DrawEntityNode(ArcticFox::Entity entity) {
	auto& name = entity.GetComponent<ArcticFox::TagComponent>().m_Tag;

	ImGuiTreeNodeFlags flags = ((m_SelectionContext == entity) ? ImGuiTreeNodeFlags_Selected : 0) | ImGuiTreeNodeFlags_OpenOnArrow;
	bool opened = ImGui::TreeNodeEx((void*)(uint64_t)(uint32_t)entity, flags, name.c_str());
	if (ImGui::IsItemClicked()) {
		m_SelectionContext = entity;
	}
	if (opened) {

		ImGui::TreePop();
	}

}

void Editor::SceneHierarchyPanel::DrawComponents(ArcticFox::Entity entity) {
	if (entity.HasComponent<ArcticFox::TagComponent>()) {
		auto& name = entity.GetComponent<ArcticFox::TagComponent>().m_Tag;

		char buffer[256];
		memset(buffer, 0, sizeof(buffer));
		strcpy_s(buffer, sizeof(buffer), name.c_str());
		if (ImGui::InputText("Tag", buffer, sizeof(buffer))) {
			name = std::string(buffer);
		}
	}

	if (entity.HasComponent<ArcticFox::TransformComponent>()) {

		if (ImGui::TreeNodeEx((void*)typeid(ArcticFox::TransformComponent).hash_code(), ImGuiTreeNodeFlags_DefaultOpen, "Transform")) {

			auto& transform = entity.GetComponent<ArcticFox::TransformComponent>().m_Transform;
			if (ImGui::DragFloat3("Position", glm::value_ptr(transform[3]), 0.25f)) {

			}
			/*if (ImGui::DragFloat3("Scale", glm::value_ptr(transform[]), 0.5f)) {

			}*/

			ImGui::TreePop();
		}
	}
}