#include "Application.h"

/* Engine API */

ArcticFox::Application::Application(AppFrame::AppConfig* config) : AppFrame::Application(config) {
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

void ArcticFox::Application::Run() {
	m_Close = false;
	AppFrame::Application::Run();
}

void ArcticFox::Application::OnEarlyUpdate() {
	AppFrame::Application::OnEarlyUpdate();
}
void ArcticFox::Application::OnUpdate() {
	AppFrame::Application::OnUpdate();
}
void ArcticFox::Application::OnLateUpdate() {
	AppFrame::Application::OnLateUpdate();
}

bool ArcticFox::Application::OnEvent(AppFrame::BasicEvent & event) {
	AppFrame::Application::OnEvent(event);
	if (AppFrame::WindowCloses* data = AppFrame::WindowCloses::Match(&event)) {
		m_Close = true;
		return true;
	}
	if (AppFrame::WindowResize* data = AppFrame::WindowResize::Match(&event)) {
		return true;
	}
}
bool ArcticFox::Application::Close() {
	return m_Close;
}
void ArcticFox::Application::Stop() {
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

ArcticFox::Application::~Application() {
}