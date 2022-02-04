#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/quaternion.hpp>
#include <string>
#include "Engine/Core/Modules/Render/Camera.h"

namespace ArcticFox {
	struct CameraComponent {//Appear problem then component are added after scene init because came then don't have set aspect ratio.
		Graphics::SceneCamera m_Camera;
		bool Primary = false;
		bool FixedAspectRatio = false;

		CameraComponent() = default;
		CameraComponent(const CameraComponent&) = default;
	};


	struct TransformComponent {
		glm::vec3 Position	= {0.0f, 0.0f, 0.0f };
		glm::vec3 Rotation	= {0.0f, 0.0f, 0.0f };
		glm::vec3 Scale		= {1.0f, 1.0f, 1.0f };

		TransformComponent() = default;
		TransformComponent(const TransformComponent&) = default;
		TransformComponent(const glm::vec3 & position) : Position(position) { }

		glm::mat4 GetTranformation() const {
			glm::mat4 rotation = glm::toMat4(glm::quat(Rotation));
			return glm::translate(glm::mat4(1.0f), Position) *
			rotation *
			/*glm::rotate(glm::mat4(1.0f), Rotation.x, { 1.0f, 0.0f, 0.0f }) *
			glm::rotate(glm::mat4(1.0f), Rotation.y, { 0.0f, 1.0f, 0.0f }) *
			glm::rotate(glm::mat4(1.0f), Rotation.z, { 0.0f, 0.0f, 1.0f }) **/
			glm::scale(glm::mat4(1.0f), Scale); }
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