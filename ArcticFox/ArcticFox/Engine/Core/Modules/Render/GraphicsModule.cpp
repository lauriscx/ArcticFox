#include "GraphicsModule.h"
#include "Engine/Core/Application.h"
#include "Engine/Core/Modules/Render/OpenGL/OpenGLContext.h"
//#include "Application/Modules/Render/OpenGL/OpenGLContext.h"*/
#include "Renderer.h"
#include <glm/gtc/matrix_transform.hpp>
#include "OpenGL/Glad/glad.h"

#include "Engine/Core/Resource/ResourceShader.h"

GraphicsModule::GraphicsModule() : m_Camera(-1.0f, 1.0f, -1.0f, 1.0f) {}
glm::vec3 mPos(0, 0, 0);
glm::vec3 mPosT(0, 0, 0);
glm::vec3 mRotT(0, 0, 0);
glm::vec3 mScaT(1, 1, 1);
float rot = 0;

void GraphicsModule::OnStart() {
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

	//AppFrame::ResourceTexture* texture = AppFrame::ResourceManager::GetInstance()->GetResource<AppFrame::ResourceTexture>(std::filesystem::path("AirBallon.jpg"));
	AppFrame::ResourceTexture* texture = AppFrame::ResourceManager::GetInstance()->GetResource<AppFrame::ResourceTexture>(std::filesystem::path("test.png"));
	
	m_Texture = Graphics::Texture2D::Create(texture);
	
	VAO = Graphics::VertexArray::Create();
	VBO = Graphics::VertexBuffer::Create(positions, sizeof(positions));
	VBO->SetLayout({ {"a_Position", Graphics::DataType::FLOAT_3, false}, {"textCoords", Graphics::DataType::FLOAT_2, false} });
	IBO = Graphics::IndexBuffer::Create(indice, sizeof(indice));
	VAO->AddVertexBuffer(VBO);
	VAO->SetIndexBuffer(IBO);

	//Graphics::RecourceShader* vertex = AppFrame::ResourceManager::GetInstance()->GetResource<Graphics::RecourceShader>(std::filesystem::path("Shaders/BaseVertex.glsl"));
	//Graphics::RecourceShader* fragment = AppFrame::ResourceManager::GetInstance()->GetResource<Graphics::RecourceShader>(std::filesystem::path("Shaders/BaseFragment.glsl"));
	//std::string name("BaseShader");
	m_ShaderLibrary.Load(/*name, */std::filesystem::path("Shaders/BaseVertex.glsl"), std::filesystem::path("Shaders/BaseFragment.glsl"));


	Graphics::RenderCommand::Init();
}

void GraphicsModule::OnEarlyUpdate(float deltaTime) {
	Graphics::RenderCommand::SetClearColor({ 0.1f, 0.5f, 0.3f, 1.0f });
	Graphics::RenderCommand::Clear();
}

void GraphicsModule::OnUpdate(float deltaTime) {


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
	m_Camera.SetPosition(mPos);
	m_Camera.SetRotation(rot);

	glm::mat4 tansform = glm::translate(glm::mat4(1.0f), mPosT) *
		glm::rotate(glm::mat4(1.0f), mRotT.z, glm::vec3(0.0f, 0.0f, 1.0f)) * glm::rotate(glm::mat4(1.0f), mRotT.y, glm::vec3(0.0f, 1.0f, 0.0f)) *
		glm::rotate(glm::mat4(1.0f), mRotT.x, glm::vec3(1.0f, 0.0f, 0.0f)) * glm::scale(glm::mat4(1.0f), mScaT);

	Graphics::Renderer::BeginScene(m_Camera);
	m_Texture->Bind(0);
	Graphics::Renderer::Submit(VAO, m_ShaderLibrary.Get("BaseVertex"));
	Graphics::Renderer::EndScene();
}

void GraphicsModule::OnLateUpdate(float deltaTime) {

}

void GraphicsModule::OnAppInput(int x, int y, int action, int key)
{
}

void GraphicsModule::OnAppEvent(AppFrame::BasicEvent * event) {
	if (auto resize = AppFrame::WindowResize::Match(event)) {
		glViewport(0, 0, resize->GetX(), resize->GetY());
	}
}

void GraphicsModule::OnStop()
{
}

GraphicsModule::~GraphicsModule()
{
}
