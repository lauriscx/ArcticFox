#include <AppFrame.h>
#include "Application.h"
#include "Module/Editor/Editor.h"

#include "Engine/Core/Modules/Render/GraphicsModule.h"
#include "Engine/Core/ECS/Components.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/glm.hpp>

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

	x = 0;
	y = 0;

	AppFrame::ResourceTexture* texture2 = AppFrame::ResourceManager::GetInstance()->GetResource<AppFrame::ResourceTexture>(std::filesystem::path("AirBallon.jpg"));
	AppFrame::ResourceTexture* texture = AppFrame::ResourceManager::GetInstance()->GetResource<AppFrame::ResourceTexture>(std::filesystem::path("test.png"));

	m_Texture = ArcticFox::Graphics::Texture2D::Create(texture);
	m_Texture2 = ArcticFox::Graphics::Texture2D::Create(texture2);

	/*VAO = Graphics::VertexArray::Create();
	VBO = Graphics::VertexBuffer::Create(positions, sizeof(positions));
	VBO->SetLayout({ {"a_Position", Graphics::DataType::FLOAT_3, false}, {"textCoords", Graphics::DataType::FLOAT_2, false} });
	IBO = Graphics::IndexBuffer::Create(indice, sizeof(indice));
	VAO->AddVertexBuffer(VBO);
	VAO->SetIndexBuffer(IBO);*/

	//Graphics::RecourceShader* vertex = AppFrame::ResourceManager::GetInstance()->GetResource<Graphics::RecourceShader>(std::filesystem::path("Shaders/BaseVertex.glsl"));
	//Graphics::RecourceShader* fragment = AppFrame::ResourceManager::GetInstance()->GetResource<Graphics::RecourceShader>(std::filesystem::path("Shaders/BaseFragment.glsl"));
	//std::string name("BaseShader");
	//m_ShaderLibrary.Load(/*name, */std::filesystem::path("Shaders/BaseVertex.glsl"), std::filesystem::path("Shaders/BaseFragment.glsl"));
	ArcticFox::Graphics::FrameBufferSpec specs;

	specs.Width = 1280;
	specs.Height = 720;

	FBO = ArcticFox::Graphics::FrameBuffer::Create(specs);


	entity = m_Scene.CreateEntity("Square");

	entity.AddComponent<ArcticFox::SpriteRenderComponent>(glm::vec4(1.0f, 0.0f, 0.0f, 1.0f));
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
		auto resize = AppFrame::WindowResize(vieportSize.x, vieportSize.y);
		m_Controller.OnEvent(&resize);
	}
	FBO->Bind();

	ArcticFox::Graphics::RenderCommand::SetClearColor({ 0.0f, 0.0f, 0.0f, 1.0f });
	ArcticFox::Graphics::RenderCommand::Clear();

	ArcticFox::Graphics::Render2D::ResetStats();
	ArcticFox::Graphics::Render2D::BeginScene(m_Controller.GetCamera());
	m_Scene.Update(0);
	ArcticFox::Graphics::Render2D::EndScene();
	
	FBO->Unbind();
	
	auto stats = ArcticFox::Graphics::Render2D::GetStats();
	rotation += 0.1f;

	uint32_t coloroAttachment = FBO->GetColorAttachment0();
	ImGui::Image((void*)coloroAttachment, vieportSize, { 0, 1 }, { 1, 0 });
	ImGui::End();

	//auto& entityColor = m_Scene.m_Registry.get<ArcticFox::SpriteRenderComponent>()
	auto& compoenent = entity.GetComponent<ArcticFox::SpriteRenderComponent>();
	
	ImGui::Begin("Render stats");
	uint32_t DepthAttachment = FBO->GetDepthAttachment();
	//ImGui::Image((void*)DepthAttachment, ImVec2{ 320.0f, 180.0f }, { 0, 1 }, { 1, 0 });
	ImGui::Text("Draw calls %d", stats.m_DrawCalls);
	ImGui::Text("Quad count %d", stats.m_QuodCount);
	ImGui::Text("Vertex count %d", stats.GetTotalVertexCount());
	ImGui::Text("Index count %d", stats.GetTotalIndexCount());
	ImGui::SliderFloat("X", &x, 1.0f, 100.0f);
	ImGui::SliderFloat("Y", &y, 1.0f, 100.0f);
	ImGui::SliderFloat3("Color", &compoenent.m_Color.r, 0.0f, 1.0f);
	ImGui::End();
	ImGui::PopStyleVar();
}
bool Editor::Application::OnInput(int x, int y, int action, int key) {
	m_Controller.OnInput(x, y, action, key);
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