#include "Application.h"
#include "Module/Editor/Editor.h"
#include "Engine/Core/Modules/Render/GraphicsModule.h"

Editor::Application::Application(AppFrame::AppConfig* config) : ArcticFox::Application(config) { }

void Editor::Application::Run() {
	AddModule<AppFrame::ModuleWindow>(new AppFrame::ModuleWindow());
	AddModule<AppFrame::ModuleConsole>(new AppFrame::ModuleConsole());
	//AddModule<AppFrame::SoundModule>(new AppFrame::SoundModule());
	AddModule<ArcticFox::GraphicsModule>(new ArcticFox::GraphicsModule());
	AddModule<AppFrame::ModuleIMGUI>(new AppFrame::ModuleIMGUI());
	AddModule<Editor>(new Editor());
	ArcticFox::Application::Run();
}

void Editor::Application::OnEarlyUpdate() {
	ArcticFox::Application::OnEarlyUpdate();
}
void Editor::Application::OnUpdate() {
	ArcticFox::Application::OnUpdate();
}
void Editor::Application::OnLateUpdate() {
	ArcticFox::Application::OnLateUpdate();
}

bool Editor::Application::OnEvent(AppFrame::BasicEvent & event) {
	return ArcticFox::Application::OnEvent(event);
}
void Editor::Application::Stop() {
	ArcticFox::Application::Stop();
}

Editor::Application::~Application() {
}