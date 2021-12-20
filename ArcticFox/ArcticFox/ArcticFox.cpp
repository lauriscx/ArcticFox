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

	~Application() {
	}
private:
	bool m_Close;
};

void Application::Run() {
	m_Close = false;
	/*ARFMountPoint * VirtualFiles = new ARFMountPoint();
	//VirtualFiles->CreateMount("C:/Users/Kosmosas/Desktop/GameData/Contet.ARF");
	VirtualFiles->SetMountPoint("C:/Users/Kosmosas/Desktop/GameData/Contet.ARF");
	VFS::GetInstance().Mount(VirtualFiles);

	PhysicalMountPoint * PhysicalSystem = new PhysicalMountPoint();
	PhysicalSystem->SetMountPoint("C:/Users/Kosmosas/Desktop/Export/");
	VFS::GetInstance().Mount(PhysicalSystem);

	PhysicalMountPoint * _PhysicalSystem = new PhysicalMountPoint();
	_PhysicalSystem->SetMountPoint("C:/Users/Kosmosas/Desktop/Import/");
	VFS::GetInstance().Mount(_PhysicalSystem);



	File* file = PhysicalSystem->ReadFile("Data/zip.zip");//Get file from exports folder.
	VirtualFiles->WriteFile(file);//write file to virtual file system.
	File* VRfile = VirtualFiles->ReadFile("Data/zip.zip");
	ASSERT(VRfile != nullptr);
	_PhysicalSystem->WriteFile(VRfile);//write file to virtual file system.*/
	/*AppFrame::PhysicalMountPoint * PhysicalSystem = new AppFrame::PhysicalMountPoint();
	PhysicalSystem->SetMountPoint("C:/Users/Kosmosas/Desktop/Application/");
	AppFrame::VFS::GetInstance()->Mount(PhysicalSystem);*/

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


int main() {
	std::cout << "Start with memory " << m_MemoryAllocated << std::endl;
	{
		//Engine::Memory::Scope<Application> app = Engine::Memory::CreateScope<Application>();
		Application * aap = new Application();
		Application::SetInstance(aap);
		AppFrame::AppConfig config;
		aap->SetConfig(&config);
		aap->Run();
		//Examples();

		while (!aap->Close()) {
			aap->OnEarlyUpdate();
			aap->OnUpdate();
			aap->OnLateUpdate();
		}
		aap->Stop();
	}
	std::cout << "---Left with memory " << m_MemoryAllocated - m_MemoryRelease << std::endl;
	std::cout << "---Left with memory current " << m_MemoryCurrentMemory << std::endl;
	std::cout << "---Ended with memory " << m_MemoryAllocated - m_MemoryRelease << std::endl;
	std::cout << "---Allocated memory " << m_MemoryAllocated << std::endl;
	std::cout << "---Rleased memory " << m_MemoryRelease << std::endl;

	//ASSERT((m_MemoryAllocated - m_MemoryRelease == 0));
	return 0;
}