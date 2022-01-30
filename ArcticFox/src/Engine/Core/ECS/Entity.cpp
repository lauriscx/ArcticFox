#include "Entity.h"
#include "Engine/Scene.h"

ArcticFox::Entity::Entity(entt::entity entity, Scene * Scene) : m_EntityID(entity), m_Scene(Scene) { }