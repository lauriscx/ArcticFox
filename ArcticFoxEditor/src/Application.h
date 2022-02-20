#pragma once

#include "Engine/Core/Application.h"

/*#include "Engine/Core/Modules/Render/Renderer.h"
#include "Engine/Core/Modules/Render/Mesh.h"*/
#include "Engine/Core/Modules/Render/Shader.h"
#include "Engine/Core/Modules/Render/Buffer.h"
#include "Engine/Core/Modules/Render/Camera.h"
#include "Engine/Core/Modules/Render/Texture.h"

#include "Engine/Core/Modules/OrthographicCameraController.h"
#include "Engine/Core/Modules/Render/FrameBuffer.h"
#include "Engine/Scene.h"
#include "Engine/Core/ECS/Entity.h"
#include <AppFrame.h>
#include "Module/Editor/Panels/SceneHierarchyPanel.h"
#include "Module/Editor/Panels/ContentBrowserPanel.h"

/*#include "Application/Modules/Render/Mesh.h"
#include "Application/Modules/Render/Renderer.h"*/

namespace Editor {
	class Application : public ArcticFox::Application {
	public:
		Application(AppFrame::AppConfig* config);

		virtual void Run() override;
		virtual void OnEarlyUpdate() override;
		virtual void OnUpdate() override;
		virtual void OnLateUpdate() override;
		virtual bool OnInput(const AppFrame::InputData& input) override;
		virtual bool OnEvent(AppFrame::BasicEvent & event) override;
		virtual void Stop() override;

		virtual ~Application();
	private:

		ArcticFox::Graphics::OrthographicCameraController m_Controller;

		ArcticFox::Graphics::ShaderLibrary m_ShaderLibrary;

		ArcticFox::Graphics::Texture* m_Texture;
		ArcticFox::Graphics::Texture* m_Texture2;

		ArcticFox::Graphics::FrameBuffer* FBO;

		int m_GuizmosType = -1;

		glm::vec2 m_vieportSize;
		glm::vec3 CamPos = {0.0f, 0.0f, 0.0f};

		glm::vec2 m_ViewPortBound[2];

		ArcticFox::Scene m_Scene;
		SceneHierarchyPanel m_SceneHierarchyPanel;
		ContentBrowserPanel m_ContentBrowserPanel;
		ArcticFox::Graphics::EditorCamera m_Editor;
	};
}