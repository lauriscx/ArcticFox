#pragma once
#include <AppFrame.h>

class GraphicsModule : public AppFrame::Module {
public:
	GraphicsModule();

	virtual void OnStart() override;
	virtual void OnEarlyUpdate(float deltaTime) override;
	virtual void OnUpdate(float deltaTime) override;
	virtual void OnLateUpdate(float deltaTime) override;
	virtual void OnAppInput(int x, int y, int action, int key) override;
	virtual void OnStop() override;

	virtual ~GraphicsModule();
};