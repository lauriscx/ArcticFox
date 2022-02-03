#include "SceneSerializer.h"
#include <AppFrame.h>
#include "Engine/Scene.h"
#include "Engine/Core/ECS/Entity.h"
#include "Engine/Core/ECS/Components.h"
#include <string>
#include "yaml-cpp/yaml.h"

ArcticFox::SceneSerializer::SceneSerializer(Scene * scene) : m_Scene(scene) {}

namespace YAML {
	template<>
	struct convert<glm::vec3> {
		static Node encode(const glm::vec3& rhs) {
			Node node;
			node.push_back(rhs.x);
			node.push_back(rhs.y);
			node.push_back(rhs.z);
		}

		static bool decode(const Node& node, glm::vec3& rhs) {
			if (!node.IsSequence() || node.size() != 3)
				return false;

			rhs.x = node[0].as<float>();
			rhs.y = node[1].as<float>();
			rhs.z = node[2].as<float>();
			return true;
		}
	};

	template<>
	struct convert<glm::vec4> {
		static Node encode(const glm::vec4& rhs) {
			Node node;
			node.push_back(rhs.x);
			node.push_back(rhs.y);
			node.push_back(rhs.z);
			node.push_back(rhs.w);
		}

		static bool decode(const Node& node, glm::vec4& rhs) {
			if (!node.IsSequence() || node.size() != 4)
				return false;

			rhs.x = node[0].as<float>();
			rhs.y = node[1].as<float>();
			rhs.z = node[2].as<float>();
			rhs.w = node[3].as<float>();
			return true;
		}
	};
}

namespace ArcticFox {
	YAML::Emitter& operator<<(YAML::Emitter& out, const glm::vec3& v) {
		out << YAML::Flow;
		out << YAML::BeginSeq << v.x << v.y << v.z << YAML::EndSeq;
		return out;
	}

	YAML::Emitter& operator<<(YAML::Emitter& out, const glm::vec4& v) {
		out << YAML::Flow;
		out << YAML::BeginSeq << v.x << v.y << v.z << v.w << YAML::EndSeq;
		return out;
	}
}


static void SerializeEntity(YAML::Emitter& out, ArcticFox::Entity entity) {
	using namespace ArcticFox;
	out << YAML::BeginMap;
	out << YAML::Key << "Entity" << YAML::Value << (uint32_t)entity;

	if (entity.HasComponent<TagComponent>()) {
		out << YAML::Key << "TagComponent";
		out << YAML::BeginMap;
		out << YAML::Key << "Tag" << YAML::Value << entity.GetComponent<TagComponent>().m_Tag.c_str();
		out << YAML::EndMap;
	}

	if (entity.HasComponent<CameraComponent>()) {
		auto& component = entity.GetComponent<CameraComponent>();
		auto& camera = component.m_Camera;
		out << YAML::Key << "CameraComponent";
		out << YAML::BeginMap;

		out << YAML::Key << "Camera" << YAML::Value;
		out << YAML::BeginMap;

		out << YAML::Key << "ProjectionType" << YAML::Value << (uint32_t)camera.GetProjectionType();
		out << YAML::Key << "PerspectiveFOV" << YAML::Value << camera.GetPerspectiveFOV();
		out << YAML::Key << "PerspectiveNear" << YAML::Value << camera.GetPerspectiveNearClipt();
		out << YAML::Key << "PerspectiveFar" << YAML::Value << camera.GetPerspectiveFarClipt();
		out << YAML::Key << "OrthographicSize" << YAML::Value << camera.GetOrthoGraphicSize();
		out << YAML::Key << "OrthographicNear" << YAML::Value << camera.GetOrthoNearClipt();
		out << YAML::Key << "OrthographicFar" << YAML::Value << camera.GetOrthoFarClipt();

		out << YAML::EndMap;

		out << YAML::Key << "Primary" << YAML::Value << component.Primary;
		out << YAML::Key << "FixedAspectRatio" << YAML::Value << component.FixedAspectRatio;

		out << YAML::EndMap;
	}

	if (entity.HasComponent<TransformComponent>()) {
		out << YAML::Key << "TransformComponent";
		out << YAML::BeginMap;
		out << YAML::Key << "Position" << YAML::Value << entity.GetComponent<TransformComponent>().Position;
		out << YAML::Key << "Rotation" << YAML::Value << entity.GetComponent<TransformComponent>().Rotation;
		out << YAML::Key << "Scale" << YAML::Value << entity.GetComponent<TransformComponent>().Scale;
		out << YAML::EndMap;
	}
	if (entity.HasComponent<SpriteRenderComponent>()) {
		out << YAML::Key << "SpriteRenderComponent";
		out << YAML::BeginMap;
		out << YAML::Key << "Color" << YAML::Value << entity.GetComponent<SpriteRenderComponent>().m_Color;
		out << YAML::EndMap;
	}

	out << YAML::EndMap;

}

void ArcticFox::SceneSerializer::Serialize(const std::filesystem::path & path) {
	if (path.empty()) {
		return;
	}

	YAML::Emitter out;
	out << YAML::BeginMap;
	out << YAML::Key << "Scene" << YAML::Value << "Name";
	out << YAML::Key << "Entities" << YAML::BeginSeq;

	m_Scene->GetRegistry().each([&](auto entityID) {


		Entity entity = { entityID, m_Scene };
		if (!entity) {
			return;
		}
		SerializeEntity(out, entity);
	});

	out << YAML::EndSeq;
	out << YAML::EndMap;

	//AppFrame::PhysicalMountPoint * PhysicalSystem = (AppFrame::PhysicalMountPoint*)AppFrame::VFS::GetInstance()->GetMount("C:/Users/Kosmosas/Desktop/Application/");
	//PhysicalSystem->WriteFile(path, (char*)out.c_str(), (size_t)out.size());

	std::ofstream fout(path);
	fout << out.c_str();


}

void ArcticFox::SceneSerializer::SerializeRuntime(const std::filesystem::path & path){}

bool ArcticFox::SceneSerializer::Derialize(const std::filesystem::path & path) {
	/*AppFrame::PhysicalMountPoint * PhysicalSystem = (AppFrame::PhysicalMountPoint*)AppFrame::VFS::GetInstance()->GetMount("C:/Users/Kosmosas/Desktop/Application/");
	wchar_t* mountDir = L"C:/Users/Kosmosas/Desktop/Application/";
	if (wcscmp(path.wstring().c_str(), mountDir) == 0) {
		return false;
	}

	std::filesystem::path _path = path.relative_path();
	if (_path.empty()) return {};
	std::filesystem::path newPath = _path.lexically_relative(*_path.begin());
	
	auto file = PhysicalSystem->ReadFile(newPath);
	std::fstream fstr(path);
	std::stringstream strStream;
	strStream = file.getData();
	YAML::Node data = YAML::Load(strStream);*/
	if (path.empty()) {
		return false;
	}

	YAML::Node data = YAML::LoadFile(path.u8string());
	if (!data["Scene"]) {
		//delete file;
		return false;
	}
	std::string sceneName = data["Scene"].as<std::string>();

	auto entities = data["Entities"];
	if (entities) {
		for (auto entity : entities) {
			uint64_t uuid = entity["Entity"].as<uint64_t>();

			std::string name;

			if (auto component = entity["TagComponent"]) {
				name = component["Tag"].as<std::string>();
			}
			Entity deserializedEntity = m_Scene->CreateEntity(/*uuid,*/ name.c_str());


			if (auto component = entity["CameraComponent"]) {
				auto& cc = deserializedEntity.AddComponent<CameraComponent>();
				auto& camera = component["Camera"];

				//cc.m_Camera.SetProjectionType((ArcticFox::Graphics::SceneCamera::ProjectionType)camera["ProjectionType"].as<int>());

				cc.m_Camera.SetPerspectiveFOV(camera["PerspectiveFOV"].as<float>());
				cc.m_Camera.SetPerspectiveNearClip(camera["PerspectiveNear"].as<float>());
				cc.m_Camera.SetPerspectiveFarClip(camera["PerspectiveFar"].as<float>());

				cc.m_Camera.SetOrthoGraphicSize(camera["OrthographicSize"].as<float>());
				cc.m_Camera.SetOrthographicNearClip(camera["OrthographicNear"].as<float>());
				cc.m_Camera.SetOrthographicFarClip(camera["OrthographicFar"].as<float>());

				cc.m_Camera.SetViewPortSize(100, 100);

				cc.Primary = component["Primary"].as<bool>();
				cc.FixedAspectRatio = component["FixedAspectRatio"].as<bool>();

			}
			if (auto component = entity["TransformComponent"]) {
				auto& tc = deserializedEntity.GetComponent<TransformComponent>();
				tc.Position = component["Position"].as<glm::vec3>();
				tc.Rotation = component["Rotation"].as<glm::vec3>();
				tc.Scale = component["Scale"].as<glm::vec3>();

			}
			if (auto component = entity["SpriteRenderComponent"]) {
				auto& Sc = deserializedEntity.AddComponent<SpriteRenderComponent>();
				Sc.m_Color = component["Color"].as<glm::vec4>();
			}

		}
		return true;
	}

	return false;
}

bool ArcticFox::SceneSerializer::DerializeRuntime(const std::filesystem::path & path) {
	return false;
}