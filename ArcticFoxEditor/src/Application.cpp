#include <AppFrame.h>
#include "Application.h"
#include "Module/Editor/Editor.h"
#include "Engine/Core/Modules/Render/GraphicsModule.h"
#include <glm/gtc/matrix_transform.hpp>

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
}

void Editor::Application::OnEarlyUpdate() {
	//GetModule<AppFrame::ModuleConsole>()->Info("TEST", std::to_string(GetFPSLimit()).c_str());
	//GetModule<AppFrame::ModuleConsole>()->Info("TEST", GetApplicationName().c_str());
	ArcticFox::Application::OnEarlyUpdate();
}
void Editor::Application::OnUpdate() {
	ArcticFox::Application::OnUpdate();
	m_Controller.OnUpdate(0);

	/*ImGui::Begin("Camera controls");
	ImGui::SliderFloat3("Position", &mPos[0], -2, 2, "%f%", 1.0f);
	ImGui::SliderFloat("Rotation", &rot, -2, 2, "%f%", 1.0f);
	ImGui::End();

	ImGui::Begin("Transform controls");
	ImGui::SliderFloat3("Position", &mPosT[0], -2, 2, "%f%", 1.0f);
	ImGui::SliderFloat3("Rotation", &mRotT[0], -2, 2, "%f%", 1.0f);
	ImGui::SliderFloat3("Scale", &mScaT[0], -2, 2, "%f%", 1.0f);
	ImGui::End();
	*/
	//m_Camera.SetPosition(mPos);
	//m_Camera.SetRotation(rot);

	glm::mat4 tansform = glm::translate(glm::mat4(1.0f), mPosT) *
		glm::rotate(glm::mat4(1.0f), mRotT.z, glm::vec3(0.0f, 0.0f, 1.0f)) * glm::rotate(glm::mat4(1.0f), mRotT.y, glm::vec3(0.0f, 1.0f, 0.0f)) *
		glm::rotate(glm::mat4(1.0f), mRotT.x, glm::vec3(1.0f, 0.0f, 0.0f)) * glm::scale(glm::mat4(1.0f), mScaT);

	//Graphics::Renderer::BeginScene(m_Camera);
	/*Graphics::Renderer::BeginScene(m_Controller.GetCamera());
	m_Texture->Bind(0);
	Graphics::Renderer::Submit(VAO, m_ShaderLibrary.Get("BaseVertex"));
	Graphics::Renderer::EndScene();*/
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
	ArcticFox::Graphics::Render2D::DrawQuad({ 0.0f, 0.0f }, { 1.0f, 1.0f }, { 1.0f, 0.0f, 0.0f, 1.0f });
	ArcticFox::Graphics::Render2D::DrawQuad({ 1.0f, 1.0f }, { 0.5f, 0.5f }, m_Texture);
	ArcticFox::Graphics::Render2D::DrawQuad({ -1.0f, -1.0f, 0.0f }, { 0.5f, 0.5f }, { 1.0f, 0.0f, 0.0f, 1.0f }, m_Texture2, rotation);

	for (float i = 0; i < x; i++) {
		for (float a = 0; a < y; a++) {
			ArcticFox::Graphics::Render2D::DrawQuad({ i, a }, { 0.5f, 0.5f }, m_Texture);
		}
	}

	ArcticFox::Graphics::Render2D::EndScene();
	FBO->Unbind();
	auto stats = ArcticFox::Graphics::Render2D::GetStats();
	rotation += 0.1f;


	uint32_t coloroAttachment = FBO->GetColorAttachment0();
	ImGui::Image((void*)coloroAttachment, vieportSize, { 0, 1 }, { 1, 0 });
	ImGui::End();

	ImGui::Begin("Render stats");
	uint32_t DepthAttachment = FBO->GetDepthAttachment();
	//ImGui::Image((void*)DepthAttachment, ImVec2{ 320.0f, 180.0f }, { 0, 1 }, { 1, 0 });
	ImGui::Text("Draw calls %d", stats.m_DrawCalls);
	ImGui::Text("Quad count %d", stats.m_QuodCount);
	ImGui::Text("Vertex count %d", stats.GetTotalVertexCount());
	ImGui::Text("Index count %d", stats.GetTotalIndexCount());
	ImGui::SliderFloat("X", &x, 1.0f, 100.0f);
	ImGui::SliderFloat("Y", &y, 1.0f, 100.0f);
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