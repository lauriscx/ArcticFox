#include <AppFrame.h>
#include "Application.h"
#include "Module/Editor/Editor.h"

#include "Engine/Core/Modules/Render/GraphicsModule.h"
#include "Engine/Core/ECS/Components.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

Editor::Application::Application(AppFrame::AppConfig* config) : ArcticFox::Application(config), m_Controller(800.0f / 600.0f), m_vieportSize(0, 0) { }
glm::vec3 mPos(0, 0, 0);
glm::vec3 mPosT(0, 0, 0);
glm::vec3 mRotT(0, 0, 0);
glm::vec3 mScaT(1, 1, 1);
void Editor::Application::Run() {
	AddModule<AppFrame::ModuleWindow>(new AppFrame::ModuleWindow());
	AddModule<AppFrame::ModuleConsole>(new AppFrame::ModuleConsole());
	//AddModule<AppFrame::SoundModule>(new AppFrame::SoundModule());
	AddModule<ArcticFox::GraphicsModule>(new ArcticFox::GraphicsModule());
	AddModule<AppFrame::ModuleIMGUI>(new AppFrame::ModuleIMGUI());
	AddModule<Editor>(new Editor());

	ArcticFox::Application::Run();

	ArcticFox::Graphics::FrameBufferSpec specs;
	specs.Width = 1280;
	specs.Height = 720;

	FBO = ArcticFox::Graphics::FrameBuffer::Create(specs);

	m_SceneHierarchyPanel.SetContext(&m_Scene);
}

void Editor::Application::OnEarlyUpdate() {
	ArcticFox::Application::OnEarlyUpdate();
}
void Editor::Application::OnUpdate() {
	ArcticFox::Application::OnUpdate();
	m_Controller.OnUpdate(0);

	ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
	ImGui::Begin("ViewPort");
	ImVec2 vieportSize = ImGui::GetContentRegionAvail();
	if (glm::vec2(vieportSize.x, vieportSize.y) != m_vieportSize) {
		m_vieportSize = { vieportSize.x, vieportSize.y };
		FBO->Resize(vieportSize.x, vieportSize.y);
		m_Scene.OnVieportResize(vieportSize.x * 2, vieportSize.y * 2);
		auto resize = AppFrame::WindowResize(vieportSize.x, vieportSize.y);
		m_Controller.OnEvent(&resize);
	}
	FBO->Bind();

	ArcticFox::Graphics::RenderCommand::SetClearColor({ 0.0f, 0.0f, 0.0f, 1.0f });
	ArcticFox::Graphics::RenderCommand::Clear();
	ArcticFox::Graphics::Render2D::ResetStats();

	m_Scene.OnUpdateRuntime(0);

	FBO->Unbind();
	
	auto stats = ArcticFox::Graphics::Render2D::GetStats();

	uint32_t coloroAttachment = FBO->GetColorAttachment0();
	ImGui::Image((void*)coloroAttachment, vieportSize, { 0, 1 }, { 1, 0 });
	
	if (AppFrame::InputManager::GetInstance()->IsKeyPressed(AppFrame::Key::KEY_T)) {
		m_GuizmosType = ImGuizmo::OPERATION::TRANSLATE;
	} else if (AppFrame::InputManager::GetInstance()->IsKeyPressed(AppFrame::Key::KEY_R)) {
		m_GuizmosType = ImGuizmo::OPERATION::ROTATE;
	} else if (AppFrame::InputManager::GetInstance()->IsKeyPressed(AppFrame::Key::KEY_S)) {
		m_GuizmosType = ImGuizmo::OPERATION::SCALE;
	} else if (AppFrame::InputManager::GetInstance()->IsKeyPressed(AppFrame::Key::KEY_ESCAPE)) {
		m_GuizmosType = -1;
	}

	ArcticFox::Entity entity = m_SceneHierarchyPanel.GetSelectedEntity();
	if (entity && m_GuizmosType != -1) {
		ImGuizmo::SetOrthographic(false);
		ImGuizmo::SetDrawlist();
		ImGuizmo::SetRect(ImGui::GetWindowPos().x, ImGui::GetWindowPos().y, ImGui::GetWindowWidth(), ImGui::GetWindowHeight());

		ArcticFox::Entity& cameraEnti = m_Scene.GetPrimaryCamera();
		const auto& camera = cameraEnti.GetComponent<ArcticFox::CameraComponent>().m_Camera;
		const glm::mat4& projectio = camera.GetProjectionMatrix();
		glm::mat4 cameraView = glm::inverse(cameraEnti.GetComponent<ArcticFox::TransformComponent>().GetTranformation());

		auto& tc = entity.GetComponent<ArcticFox::TransformComponent>();
		glm::mat4 transform = tc.GetTranformation();

		bool snap = AppFrame::InputManager::GetInstance()->IsKeyPressed(AppFrame::Key::KEY_LEFT_CONTROL);
		float snapValue = 0.5f;
		if (m_GuizmosType == ImGuizmo::OPERATION::ROTATE) {
			snapValue = 45.0f;
		}

		float snapValues[3] = { snapValue, snapValue, snapValue };

		ImGuizmo::Manipulate(glm::value_ptr(cameraView), glm::value_ptr(projectio), ImGuizmo::OPERATION(m_GuizmosType), ImGuizmo::LOCAL, glm::value_ptr(transform), 0, snap ? snapValues : nullptr);

		if (ImGuizmo::IsUsing()) {
			glm::vec3 Position;
			glm::vec3 Rotation;
			glm::vec3 Scale;

			ImGui::ModifiedDecomposeTransform(transform, Position, Rotation, Scale);

			tc.Position = Position;
			tc.Rotation += Rotation - tc.Rotation;
			tc.Scale = Scale;
		}
	}
	ImGui::End();
	
	m_SceneHierarchyPanel.OnImGuiRender();

	ImGui::PopStyleVar();
}
bool Editor::Application::OnInput(const AppFrame::InputData& input) {
	return true;
}
void Editor::Application::OnLateUpdate() {
	ArcticFox::Application::OnLateUpdate();
}

bool Editor::Application::OnEvent(AppFrame::BasicEvent & event) {
	m_Controller.OnEvent(&event);
	return ArcticFox::Application::OnEvent(event);
}
void Editor::Application::Stop() {
	ArcticFox::Application::Stop();
}

Editor::Application::~Application() { }