#include "Application.h"

/* Engine API */
#include "Core/Modules/Render/GraphicsModule.h"

Application::Application(AppFrame::AppConfig* config) : AppFrame::Application(config) {
	 SubscribeToEvent(AppFrame::WindowCloses::Type());
	 SubscribeToEvent(AppFrame::WindowResize::Type());
	 SubscribeToEvent(AppFrame::Log::Type());//Used for Console module.
	 SubscribeToEvent(AppFrame::InputScroll::Type());//Used for Console module.
	 SubscribeToEvent(AppFrame::WindowMinimized::Type());//Used for Console module.
	 SubscribeToEvent(AppFrame::WindowMaximized::Type());//Used for Console module.

	 AppFrame::PhysicalMountPoint * PhysicalSystem = new AppFrame::PhysicalMountPoint();
	 PhysicalSystem->SetMountPoint("C:/Users/Kosmosas/Desktop/Application/");
	 AppFrame::VFS::GetInstance()->Mount(PhysicalSystem);
}

void Application::Run() {
	m_Close = false;

	AddModule<AppFrame::ModuleWindow>(new AppFrame::ModuleWindow());
	AddModule<AppFrame::ModuleConsole>(new AppFrame::ModuleConsole());
	//AddModule<AppFrame::SoundModule>(new AppFrame::SoundModule());
	AddModule<GraphicsModule>(new GraphicsModule());
	AddModule<AppFrame::ModuleIMGUI>(new AppFrame::ModuleIMGUI());

	AppFrame::Application::Run();

	editor.OnStart();
}

void Application::OnEarlyUpdate() {
	AppFrame::Application::OnEarlyUpdate();
	editor.OnEarlyUpdate(0);
}
void Application::OnUpdate() {
	AppFrame::Application::OnUpdate();
	editor.OnUpdate(0);
}
void Application::OnLateUpdate() {
	AppFrame::Application::OnLateUpdate();
	editor.OnLateUpdate(0);
}

bool Application::OnEvent(AppFrame::BasicEvent & event) {
	AppFrame::Application::OnEvent(event);
	if (AppFrame::WindowCloses* data = AppFrame::WindowCloses::Match(&event)) {
		m_Close = true;
		return true;
	}
	if (AppFrame::WindowResize* data = AppFrame::WindowResize::Match(&event)) {
		return true;
	}
}
bool Application::Close() {
	return m_Close;
}
void Application::Stop() {
	AppFrame::Application::Stop();

	AppFrame::PhysicalMountPoint * PhysicalSystem = static_cast<AppFrame::PhysicalMountPoint*>(AppFrame::VFS::GetInstance()->GetMount("C:/Users/Kosmosas/Desktop/Application/"));
	AppFrame::VFS::GetInstance()->Unmount("C:/Users/Kosmosas/Desktop/Application/");
	delete PhysicalSystem;

	for (auto it = m_Modules.begin(); it != m_Modules.end(); it++) {
		delete it->second;
	}
	m_EarlyUpdate.clear();
	m_MiddleUpdate.clear();
	m_Modules.clear();
}

Application::~Application() {
}