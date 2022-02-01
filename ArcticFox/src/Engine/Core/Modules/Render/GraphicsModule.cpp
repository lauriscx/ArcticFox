#include "GraphicsModule.h"
#include "Engine/Core/Application.h"
#include "Engine/Core/Modules/Render/OpenGL/OpenGLContext.h"
#include "Renderer.h"
#include <glm/gtc/matrix_transform.hpp>
#include "OpenGL/Glad/glad.h"

#include "Engine/Core/Resource/ResourceShader.h"
#include "Render2D.h"

ArcticFox::GraphicsModule::GraphicsModule() {}

void ArcticFox::GraphicsModule::OnStart() {
	m_GraphicsContext = new Graphics::OpenGL::OpenGLContext();
	m_GraphicsContext->Init();

	Graphics::RendererAPI::SetAPI(Graphics::RendererAPI::API::OpenGL);
	Graphics::Renderer::Init();
}

void ArcticFox::GraphicsModule::OnEarlyUpdate(float deltaTime) {
	Graphics::RenderCommand::SetClearColor({ 0.0f, 0.0f, 0.0f, 1.0f });
	Graphics::RenderCommand::Clear();
}

void ArcticFox::GraphicsModule::OnUpdate(float deltaTime) {

}

void ArcticFox::GraphicsModule::OnLateUpdate(float deltaTime) {

}

void ArcticFox::GraphicsModule::OnAppInput(const AppFrame::InputData& input) {
}

void ArcticFox::GraphicsModule::OnAppEvent(AppFrame::BasicEvent * event) {
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

void ArcticFox::GraphicsModule::OnStop() {
	Graphics::Render2D::ShutDown();
}

ArcticFox::GraphicsModule::~GraphicsModule()
{
}
