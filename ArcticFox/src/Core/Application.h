#pragma once
//#include <AppFrame.h>
#include "AppFrame.h"
//#include <Application/Logger.h>
#include "../Editor/Editor.h"

class Application : public AppFrame::Application {
public:
	Application(AppFrame::AppConfig* config);

	virtual void Run() override;
	virtual void OnEarlyUpdate() override;
	virtual void OnUpdate() override;
	virtual void OnLateUpdate() override;
	virtual bool OnEvent(AppFrame::BasicEvent & event) override;
	//virtual bool OnInput(int x, int y, int action, int key) override;
	bool Close();
	virtual void Stop() override;

	virtual ~Application();
private:
	bool m_Close;
	Editor editor;
};