#include "Scene.h"
#include "Core/ECS/Components.h"
#include "Engine/Core/Modules/Render/GraphicsModule.h"
#include "Engine/Core/ECS/Entity.h"
#include "Engine/Core/Modules/Render/Camera.h"

ArcticFox::Scene::Scene() {
	//SubscribeToEvent(AppFrame::WindowResize::Type());
	//SubscribeToEvent(AppFrame::WindowResize::Type());
}

ArcticFox::Entity ArcticFox::Scene::CreateEntity(std::string name) {
	Entity entity = { m_Registry.create(), this };
	entity.AddComponent<TransformComponent>();
	auto& tag = entity.AddComponent<TagComponent>();
	tag.m_Tag = name;
	return entity;
}

void ArcticFox::Scene::DestroyEntity(Entity entity) {
	m_Registry.destroy(entity);
}

void ArcticFox::Scene::OnUpdateRuntime(float deltaTime) {
	//Scripts

	//Physics

	//Render 2D
	Graphics::Camera* mainCamera = nullptr;
	glm::mat4 mainCameraTransform = glm::mat4(1.0f);
	{
		auto view = m_Registry.view<TransformComponent, CameraComponent>();
		for (auto entity : view) {
			auto&[transform, camera] = view.get<TransformComponent, CameraComponent>(entity);

			if (camera.Primary) {
				mainCamera = &camera.m_Camera;
				mainCameraTransform = transform.GetTranformation();
				break;
			}
		}
	}

	{
		if (mainCamera) {
			ArcticFox::Graphics::Render2D::BeginScene(*mainCamera, mainCameraTransform);
			auto group = m_Registry.group<TransformComponent>(entt::get<SpriteRenderComponent>);
			for (auto entity : group) {
				auto&[transform, sprite] = group.get<TransformComponent, SpriteRenderComponent>(entity);
				Graphics::Render2D::DrawQuad(transform.GetTranformation(), sprite.m_Color);
			}
			ArcticFox::Graphics::Render2D::EndScene();
		}
	}


	//Render 3D
}

void ArcticFox::Scene::OnUpdateEditor(float deltaTime, ArcticFox::Graphics::EditorCamera & camera) {
	ArcticFox::Graphics::Render2D::BeginScene(camera);
	auto group = m_Registry.group<TransformComponent>(entt::get<SpriteRenderComponent>);
	for (auto entity : group) {
		auto&[transform, sprite] = group.get<TransformComponent, SpriteRenderComponent>(entity);
		//Graphics::Render2D::DrawQuad(transform.GetTranformation(), sprite.m_Color);
		Graphics::Render2D::DrawSprite(transform.GetTranformation(), sprite, (int)entity);
	}
	ArcticFox::Graphics::Render2D::EndScene();
}


bool ArcticFox::Scene::OnEvent(AppFrame::BasicEvent & event) {
	if (auto resize = AppFrame::WindowResize::Match(&event)) {
		OnVieportResize(resize->GetX(), resize->GetY());
		//resize.
	}
	return false;
}


void ArcticFox::Scene::OnVieportResize(uint32_t width, uint32_t height) {
	m_ViewPortWidth = width;
	m_ViewPortHeight = height;

	auto view = m_Registry.view<CameraComponent>();
	for (auto entity : view) {
		auto& cameraComp = view.get<CameraComponent>(entity);
		if (!cameraComp.FixedAspectRatio) {
			cameraComp.m_Camera.SetViewPortSize(m_ViewPortWidth, m_ViewPortHeight);
		}
	}

}

void ArcticFox::Scene::UpdateVieportResize() {
	auto view = m_Registry.view<CameraComponent>();
	for (auto entity : view) {
		auto& cameraComp = view.get<CameraComponent>(entity);
		if (!cameraComp.FixedAspectRatio) {
			cameraComp.m_Camera.SetViewPortSize(m_ViewPortWidth, m_ViewPortHeight);
		}
	}
}

ArcticFox::Entity ArcticFox::Scene::GetPrimaryCamera() {
	auto view = m_Registry.view<CameraComponent>();
	for (auto entity : view) {
		auto& cameraComp = view.get<CameraComponent>(entity);
		if (cameraComp.Primary) {
			return Entity{ entity, this };
		}
	}

	return {};
}

ArcticFox::Scene::~Scene() {}