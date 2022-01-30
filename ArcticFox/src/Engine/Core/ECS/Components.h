#pragma once

#include <glm/glm.hpp>
#include <string>
#include "Engine/Core/Modules/Render/Camera.h"

namespace ArcticFox {
	struct CameraComponent {
		Graphics::Camera m_Camera;

		CameraComponent() = default;
		CameraComponent(const CameraComponent&) = default;
		CameraComponent(const Graphics::Camera & camera) : m_Camera(camera) {}
	};


	struct TransformComponent {
		glm::mat4 m_Transform = glm::mat4(1.0f);

		TransformComponent() = default;
		TransformComponent(const TransformComponent&) = default;
		TransformComponent(const glm::mat4 & transform) : m_Transform(transform) {}
		operator glm::mat4& () { return m_Transform; }
		operator const glm::mat4& () const { return m_Transform; }
	};

	struct SpriteRenderComponent {
		glm::vec4 m_Color = glm::vec4(1.0f);

		SpriteRenderComponent() = default;
		SpriteRenderComponent(const SpriteRenderComponent&) = default;
		SpriteRenderComponent(const glm::vec4 & color) : m_Color(color) {}
	};

	struct TagComponent {
		std::string m_Tag;

		TagComponent() = default;
		TagComponent(const TagComponent&) = default;
		TagComponent(const std::string& tag) : m_Tag(tag) {}
	};
}