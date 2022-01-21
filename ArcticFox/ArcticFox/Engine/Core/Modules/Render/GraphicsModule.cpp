#include "GraphicsModule.h"
#include "Engine/Core/Application.h"
#include "Engine/Core/Modules/Render/OpenGL/OpenGLContext.h"
//#include "Application/Modules/Render/OpenGL/OpenGLContext.h"*/
#include "Renderer.h"

GraphicsModule::GraphicsModule()
{
}

void GraphicsModule::OnStart() {
	m_GraphicsContext = new Graphics::OpenGL::OpenGLContext();
	m_GraphicsContext->Init();

	float positions[3*3*4] = { 
							-0.5f, -0.5f, 0.0f,1.0f, 0.1f, 0.5f, 1.0,
							0.5f, -0.5f, 0.0f, 1.0f, 0.1f, 0.5f, 1.0,
							0.0f, 0.5f, 0.0f,  1.0f, 0.1f, 0.5f, 1.0
						};

	unsigned int indice[3] = {0, 1, 2};

	Graphics::RendererAPI::SetAPI(Graphics::RendererAPI::API::OpenGL);
	VAO = Graphics::VertexArray::Create();
	VBO = Graphics::VertexBuffer::Create(positions, sizeof(positions));
	VBO->SetLayout({ {"a_Position", Graphics::DataType::FLOAT_3, false}, {"a_Color", Graphics::DataType::FLOAT_4, false} });
	IBO = Graphics::IndexBuffer::Create(indice, sizeof(indice));
	VAO->AddVertexBuffer(VBO);
	VAO->SetIndexBuffer(IBO);

	m_Shader = Graphics::Shader::Create();
}

void GraphicsModule::OnEarlyUpdate(float deltaTime) {
	Graphics::RenderCommand::SetClearColor({ 0.1f, 0.5f, 0.3f, 1.0f });
	Graphics::RenderCommand::Clear();
}

void GraphicsModule::OnUpdate(float deltaTime) {
	Graphics::Renderer::BeginScene();
	Graphics::Renderer::Submit(VAO);
	Graphics::Renderer::EndScene();
}

void GraphicsModule::OnLateUpdate(float deltaTime) {

}

void GraphicsModule::OnAppInput(int x, int y, int action, int key)
{
}

void GraphicsModule::OnStop()
{
}

GraphicsModule::~GraphicsModule()
{
}
