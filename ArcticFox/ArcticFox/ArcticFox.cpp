#include <AppFrame.h>

class Application : public AppFrame::Application {
public:
	Application() {
		SubscribeToEvent(AppFrame::WindowCloses::Type());
		SubscribeToEvent(AppFrame::WindowResize::Type());
		SubscribeToEvent(AppFrame::Log::Type());//Used for Console module.
	}

	void Run() override;
	bool OnEvent(AppFrame::BasicEvent & event) override;
	bool Close() {
		return m_Close;
	}
	void Stop() override;

	~Application() {
	}
private:
	bool m_Close;
};

void Application::Run() {
	m_Close = false;

	AppFrame::PhysicalMountPoint * PhysicalSystem = new AppFrame::PhysicalMountPoint();
	PhysicalSystem->SetMountPoint("C:/Users/Kosmosas/Desktop/Application/");
	AppFrame::VFS::GetInstance()->Mount(PhysicalSystem);

	AddModule<AppFrame::ModuleWindow>(new AppFrame::ModuleWindow());
	AddModule<AppFrame::ModuleConsole>(new AppFrame::ModuleConsole());
	AddModule<AppFrame::SoundModule>(new AppFrame::SoundModule());
	AddModule<AppFrame::ModuleIMGUI>(new AppFrame::ModuleIMGUI());


	std::cout << "Run" << std::endl;
	AppFrame::Application::Run();
}
bool Application::OnEvent(AppFrame::BasicEvent & event) {
	if (AppFrame::WindowCloses* data = AppFrame::WindowCloses::Match(&event)) {
		m_Close = true;
		return true;
	}
	if (AppFrame::WindowResize* data = AppFrame::WindowResize::Match(&event)) {
		return true;
	}
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
	m_LateUpdate.clear();
	m_Modules.clear();
}


int main() {
	std::cout << "Start with memory " << m_MemoryAllocated << std::endl;
	{
		Application * aap = new Application();
		Application::SetInstance(aap);
		AppFrame::AppConfig config;
		aap->SetConfig(&config);
		aap->Run();
		int a = 0;
		while (!aap->Close()) {
			aap->OnEarlyUpdate();
			aap->OnUpdate();
			aap->OnLateUpdate();
			if (a > 90000) {
				break;
			}
			a++;
		}
		aap->Stop();
		delete aap;
	}
	std::cout << "---Left with memory " << m_MemoryAllocated - m_MemoryRelease << std::endl;
	std::cout << "---Left with memory current " << m_MemoryCurrentMemory << std::endl;
	std::cout << "---Ended with memory " << m_MemoryAllocated - m_MemoryRelease << std::endl;
	std::cout << "---Allocated memory " << m_MemoryAllocated << std::endl;
	std::cout << "---Rleased memory " << m_MemoryRelease << std::endl;

	//ASSERT((m_MemoryAllocated - m_MemoryRelease == 0));
	return 0;
}