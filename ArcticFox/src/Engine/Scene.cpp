#include "Scene.h"
#include "Core/ECS/Components.h"
#include "Engine/Core/Modules/Render/GraphicsModule.h"
#include "Engine/Core/ECS/Entity.h"

ArcticFox::Scene::Scene() { }

ArcticFox::Entity ArcticFox::Scene::CreateEntity(std::string name) {
	Entity entity = { m_Registry.create(), this };
	entity.AddComponent<TransformComponent>();
	auto& tag = entity.AddComponent<TagComponent>();
	tag.m_Tag = name;
	return entity;
}

void ArcticFox::Scene::Update(float deltaTime) {
	auto group = m_Registry.group<TransformComponent>(entt::get<SpriteRenderComponent>);
	for (auto entity : group) {
		auto&[transform, sprite] = group.get<TransformComponent, SpriteRenderComponent>(entity);
		Graphics::Render2D::DrawQuad(transform, sprite.m_Color);
	}
}

ArcticFox::Scene::~Scene() {}