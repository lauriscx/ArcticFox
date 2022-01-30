#include "GraphicsModule.h"
#include "Core/Application.h"
#include "Core/Modules/Render/OpenGL/OpenGLContext.h"
//#include "Application/Modules/Render/OpenGL/OpenGLContext.h"*/
#include "Renderer.h"
#include <glm/gtc/matrix_transform.hpp>
#include "OpenGL/Glad/glad.h"

#include "Core/Resource/ResourceShader.h"
#include "Render2D.h"



GraphicsModule::GraphicsModule()/* : m_Camera(-1.0f, 1.0f, -1.0f, 1.0f),*/ : m_Controller(800.0f/600.0f) {}
glm::vec3 mPos(0, 0, 0);
glm::vec3 mPosT(0, 0, 0);
glm::vec3 mRotT(0, 0, 0);
glm::vec3 mScaT(1, 1, 1);

void GraphicsModule::OnStart() {
	x = 0;
	y = 0;
	m_GraphicsContext = new Graphics::OpenGL::OpenGLContext();
	m_GraphicsContext->Init();

	float positions[5*4] = { 
							-0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
							 0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
							 0.5f,  0.5f, 0.0f, 1.0f, 1.0f,
							-0.5f,  0.5f, 0.0f, 0.0f, 1.0f
						};

	unsigned int indice[6] = {0, 1, 2, 2, 3, 0};


	Graphics::RendererAPI::SetAPI(Graphics::RendererAPI::API::OpenGL);

	AppFrame::ResourceTexture* texture2 = AppFrame::ResourceManager::GetInstance()->GetResource<AppFrame::ResourceTexture>(std::filesystem::path("AirBallon.jpg"));
	AppFrame::ResourceTexture* texture = AppFrame::ResourceManager::GetInstance()->GetResource<AppFrame::ResourceTexture>(std::filesystem::path("test.png"));
	
	m_Texture = Graphics::Texture2D::Create(texture);
	m_Texture2 = Graphics::Texture2D::Create(texture2);
	
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
	Graphics::FrameBufferSpec specs;

	specs.Width = 1280;
	specs.Height = 720;

	FBO = Graphics::FrameBuffer::Create(specs);

	Graphics::Renderer::Init();

}

void GraphicsModule::OnEarlyUpdate(float deltaTime) {
	Graphics::RenderCommand::SetClearColor({ 0.1f, 0.5f, 0.3f, 1.0f });
	Graphics::RenderCommand::Clear();
}

void GraphicsModule::OnUpdate(float deltaTime) {
	m_Controller.OnUpdate(deltaTime);

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
	FBO->Bind();
	Graphics::RenderCommand::SetClearColor({ 0.1f, 0.5f, 0.3f, 1.0f });
	Graphics::RenderCommand::Clear();
	
	Graphics::Render2D::ResetStats();
	Graphics::Render2D::BeginScene(m_Controller.GetCamera());
	Graphics::Render2D::DrawQuad({ 0.0f, 0.0f }, { 1.0f, 1.0f }, { 1.0f, 0.0f, 0.0f, 1.0f });
	Graphics::Render2D::DrawQuad({ 1.0f, 1.0f }, { 0.5f, 0.5f }, m_Texture);
	Graphics::Render2D::DrawQuad({ -1.0f, -1.0f, 0.0f}, { 0.5f, 0.5f }, { 1.0f, 0.0f, 0.0f, 1.0f }, m_Texture2, rotation);

	for (float i = 0; i < x; i++) {
		for (float a = 0; a < y; a++) {
			Graphics::Render2D::DrawQuad({ i, a }, { 0.5f, 0.5f }, m_Texture);
		}
	}

	Graphics::Render2D::EndScene();
	FBO->Unbind();
	auto stats = Graphics::Render2D::GetStats();
	rotation += 0.1f;
	ImGui::Begin("Render stats");
	uint32_t coloroAttachment = FBO->GetColorAttachment0();
	ImGui::Image((void*)coloroAttachment, ImVec2{ 320.0f, 180.0f }, { 0, 1 }, { 1, 0 });

	uint32_t DepthAttachment = FBO->GetDepthAttachment();
	//ImGui::Image((void*)DepthAttachment, ImVec2{ 320.0f, 180.0f }, { 0, 1 }, { 1, 0 });
	ImGui::Text("Draw calls %d", stats.m_DrawCalls);
	ImGui::Text("Quad count %d", stats.m_QuodCount);
	ImGui::Text("Vertex count %d", stats.GetTotalVertexCount());
	ImGui::Text("Index count %d", stats.GetTotalIndexCount());
	ImGui::SliderFloat("X", &x, 1.0f, 100.0f);
	ImGui::SliderFloat("Y", &y, 1.0f, 100.0f);
	ImGui::End();
}

void GraphicsModule::OnLateUpdate(float deltaTime) {

}

void GraphicsModule::OnAppInput(int x, int y, int action, int key) {
	m_Controller.OnInput(x, y, action, key);
}

void GraphicsModule::OnAppEvent(AppFrame::BasicEvent * event) {
	m_Controller.OnEvent(event);
	if (auto resize = AppFrame::WindowResize::Match(event)) {
		static_cast<Application*>(m_Context)->GetModule<AppFrame::ModuleConsole>()->Info("GraphicModule", "Resize");
		Graphics::Renderer::SetViewPort({0, 0, resize->GetX(), resize->GetY() });
	}
	if (auto resize = AppFrame::WindowMinimized::Match(event)) {
		static_cast<Application*>(m_Context)->GetModule<AppFrame::ModuleConsole>()->Info("GraphicModule", "Minimized");
	}
	if (auto resize = AppFrame::WindowMaximized::Match(event)) {
		static_cast<Application*>(m_Context)->GetModule<AppFrame::ModuleConsole>()->Info("GraphicModule", "Maximize");
	}
}

void GraphicsModule::OnStop() {
	Graphics::Render2D::ShutDown();
}

GraphicsModule::~GraphicsModule()
{
}
