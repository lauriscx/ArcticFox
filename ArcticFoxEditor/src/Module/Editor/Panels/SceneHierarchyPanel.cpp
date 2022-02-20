#include "SceneHierarchyPanel.h"
#include "Engine/Scene.h"
#include "Engine/Core/ECS/Components.h"
#include "entt.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "Engine/Core/Modules/Render/Camera.h"
#include "Engine/SceneSerializer.h"

Editor::SceneHierarchyPanel::SceneHierarchyPanel(ArcticFox::Scene * scene) : m_Scene(scene) {
	
}

void Editor::SceneHierarchyPanel::SetContext(ArcticFox::Scene * scene) {
	m_Scene = scene;
}

ArcticFox::Entity Editor::SceneHierarchyPanel::GetSelectedEntity() const {
	return m_SelectionContext;
}

void Editor::SceneHierarchyPanel::OnImGuiRender() {
	if (ImGui::BeginMainMenuBar())
	{
		if (ImGui::BeginMenu("File"))
		{
			if (ImGui::MenuItem("New"))
			{
				//Do something
			}
			if (ImGui::MenuItem("Save As...", "Ctrl+Shift+S")) {
				ArcticFox::SceneSerializer serializer(m_Scene);
				//serializer.Serialize("Test.scene");
				std::string path = AppFrame::Device::SaveFile("Arctic Fox Scene file (*.scene)\0*.scene\0");
				serializer.Serialize(path);
			}
			if (ImGui::MenuItem("Open", "Ctrl+O")) {
				m_Scene->GetRegistry().clear();
				m_SelectionContext = {};

				ArcticFox::SceneSerializer serializer(m_Scene);
				//serializer.Serialize("Test.scene");
				std::string path = AppFrame::Device::OpenFile("Arctic Fox Scene file (*.scene)\0*.scene\0");
				serializer.Derialize(path);

				m_Scene->UpdateVieportResize();
			}
			ImGui::EndMenu();
		}

		ImGui::EndMainMenuBar();
	}

	ImGui::Begin("Scene hierarchy");

	m_Scene->GetRegistry().each([&](auto entityID) {
		DrawEntityNode({ entityID, m_Scene });
	});

	if (ImGui::IsMouseDown(0) && ImGui::IsWindowHovered()) {
		m_SelectionContext = {};
	}

	if (ImGui::BeginPopupContextWindow(0, 1, false)) {
		if (ImGui::MenuItem("Create empty entity")) {
			m_Scene->CreateEntity("Entity");
		}
		ImGui::EndPopup();
	}

	ImGui::End();

	ImGui::Begin("Properties");
	if (m_SelectionContext) {
		DrawComponents(m_SelectionContext);
		if (ImGui::Button("Add component")) {
			ImGui::OpenPopup("AddComponent");
		}
		if (ImGui::BeginPopup("AddComponent")) {
			if (ImGui::MenuItem("Camera")) {
				m_SelectionContext.AddComponent<ArcticFox::CameraComponent>();
				ImGui::CloseCurrentPopup();
			}
			/*if (ImGui::MenuItem("Transform")) {
				m_SelectionContext.AddComponent<ArcticFox::TransformComponent>();
				ImGui::CloseCurrentPopup();
			}*/
			if (ImGui::MenuItem("Sprete renderer")) {
				m_SelectionContext.AddComponent<ArcticFox::SpriteRenderComponent>();
				ImGui::CloseCurrentPopup();
			}
			ImGui::EndPopup();
		}
	}
	ImGui::End();
}

void Editor::SceneHierarchyPanel::DrawEntityNode(ArcticFox::Entity entity) {
	auto& name = entity.GetComponent<ArcticFox::TagComponent>().m_Tag;

	ImGuiTreeNodeFlags flags = ((m_SelectionContext == entity) ? ImGuiTreeNodeFlags_Selected : 0) | ImGuiTreeNodeFlags_OpenOnArrow;
	bool opened = ImGui::TreeNodeEx((void*)(uint64_t)(uint32_t)entity, flags, name.c_str());
	if (ImGui::IsItemClicked()) {
		m_SelectionContext = entity;
	}
	bool entityDeleted = false;
	if (ImGui::BeginPopupContextItem()) {
		if (ImGui::MenuItem("Delete entity")) {
			entityDeleted = true;
		}
		ImGui::EndPopup();
	}

	if (opened) {
		ImGui::TreePop();
	}
	if (entityDeleted) {
		m_Scene->DestroyEntity(entity);
		if (m_SelectionContext == entity) {
			m_SelectionContext = {};
		}
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

	const ImGuiTreeNodeFlags treeNodeFlags = ImGuiTreeNodeFlags_DefaultOpen | ImGuiTreeNodeFlags_AllowItemOverlap;

	if (entity.HasComponent<ArcticFox::TransformComponent>()) {
		ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2{ 4, 4 });
		bool open = ImGui::TreeNodeEx((void*)typeid(ArcticFox::TransformComponent).hash_code(), treeNodeFlags, "Transform");
		ImGui::SameLine(ImGui::GetWindowWidth() - 25.0f);
		if (ImGui::Button("...", ImVec2{ 30, 30 })) {
			ImGui::OpenPopup("ComponentSettings");
		}
		ImGui::PopStyleVar();
		bool RemoveComponent = false;
		if (ImGui::BeginPopup("ComponentSettings")) {
			if (ImGui::MenuItem("Remove component")) {
				RemoveComponent = true;
			}
			ImGui::EndPopup();
		}
		if (open) {
			auto& transformCom = entity.GetComponent<ArcticFox::TransformComponent>();
			if (ImGui::DragFloat3("Position", glm::value_ptr(transformCom.Position), 0.25f)) {

			}
			glm::vec3 rotation = glm::degrees(transformCom.Rotation);
			if (ImGui::DragFloat3("Rotation", glm::value_ptr(rotation), 0.25f)) {
				transformCom.Rotation = glm::radians(rotation);
			}
			if (ImGui::DragFloat3("Scale", glm::value_ptr(transformCom.Scale), 0.25f)) {

			}

			ImGui::TreePop();
		}
		if (RemoveComponent)
			entity.RemoveComponent<ArcticFox::TransformComponent>();
	}
	if (entity.HasComponent<ArcticFox::SpriteRenderComponent>()) {
		ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2{ 4, 4 });
		bool open = ImGui::TreeNodeEx((void*)typeid(ArcticFox::SpriteRenderComponent).hash_code(), treeNodeFlags, "Sprite renderer");
		ImGui::SameLine(ImGui::GetWindowWidth() - 25.0f);
		if (ImGui::Button("...", ImVec2{ 30, 30 })) {
			ImGui::OpenPopup("ComponentSettings");
		}
		ImGui::PopStyleVar();
		bool RemoveComponent = false;
		if (ImGui::BeginPopup("ComponentSettings")) {
			if (ImGui::MenuItem("Remove component")) {
				RemoveComponent = true;
			}
			ImGui::EndPopup();
		}
		if (open) {
			auto& color = entity.GetComponent<ArcticFox::SpriteRenderComponent>().m_Color;
			if (ImGui::ColorEdit4("Color", glm::value_ptr(color))) {

			}
			ImGui::TreePop();
		}
		if (RemoveComponent)
			entity.RemoveComponent<ArcticFox::SpriteRenderComponent>();
	}

	if (entity.HasComponent<ArcticFox::CameraComponent>()) {
		ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2{ 4, 4 });
		bool open = ImGui::TreeNodeEx((void*)typeid(ArcticFox::CameraComponent).hash_code(), treeNodeFlags, "Camera");

		ImGui::SameLine(ImGui::GetWindowWidth() - 25.0f);
		if (ImGui::Button("...", ImVec2{ 30, 30 })) {
			ImGui::OpenPopup("ComponentSettings");
		}
		ImGui::PopStyleVar();
		bool RemoveComponent = false;
		if (ImGui::BeginPopup("ComponentSettings")) {
			if (ImGui::MenuItem("Remove component")) {
				RemoveComponent = true;
			}
			ImGui::EndPopup();
		}

		if (open) {
			auto& camera = entity.GetComponent<ArcticFox::CameraComponent>().m_Camera;

			const char* projectionTypesString[] = { "Perspective", "Orthographic" };
			const char* currentProjectionTypeStr = projectionTypesString[(uint32_t)camera.GetProjectionType()];
			if (ImGui::BeginCombo("Projection", currentProjectionTypeStr)) {

				for (uint32_t i = 0; i < 2; i++) {
					bool isSelected = currentProjectionTypeStr == projectionTypesString[i];
					if (ImGui::Selectable(projectionTypesString[i], isSelected)) {
						currentProjectionTypeStr = projectionTypesString[i];
						camera.SetProjectionType((ArcticFox::Graphics::SceneCamera::ProjectionType)i);
					}
					if (isSelected) {
						ImGui::SetItemDefaultFocus();
					}
				}

				ImGui::EndCombo();
			}

			if (camera.GetProjectionType() == ArcticFox::Graphics::SceneCamera::ProjectionType::Perspective) {
				float PerspFOV = glm::degrees(camera.GetPerspectiveFOV());
				if (ImGui::DragFloat("Vertical FOV", &PerspFOV)) {
					camera.SetPerspectiveFOV(glm::radians(PerspFOV));
				}
				float PerspNear = camera.GetPerspectiveNearClipt();
				if (ImGui::DragFloat("Near", &PerspNear)) {
					camera.SetPerspectiveNearClip(PerspNear);
				}
				float PerspFar = camera.GetPerspectiveFarClipt();
				if (ImGui::DragFloat("Far", &PerspFar)) {
					camera.SetPerspectiveFarClip(PerspFar);
				}
			}

			if (camera.GetProjectionType() == ArcticFox::Graphics::SceneCamera::ProjectionType::Orthographic) {
				float orthoSize = camera.GetOrthoGraphicSize();
				if (ImGui::DragFloat("Size", &orthoSize)) {
					camera.SetOrthoGraphicSize(orthoSize);
				}
				float orthoNear = camera.GetOrthoNearClipt();
				if (ImGui::DragFloat("Near", &orthoNear)) {
					camera.SetOrthographicNearClip(orthoNear);
				}
				float orthoFar = camera.GetOrthoFarClipt();
				if (ImGui::DragFloat("Far", &orthoFar)) {
					camera.SetOrthographicFarClip(orthoFar);
				}
			}

			ImGui::TreePop();
		}
		if (RemoveComponent)
			entity.RemoveComponent<ArcticFox::CameraComponent>();
	}
}