#pragma once
#include <AppFrame.h>

namespace Editor {
	class Editor : public AppFrame::Module {
	public:
		///virtual void OnInit(AppContext* context) { m_Context = context; };
		void OnStart();
		void OnEarlyUpdate(float deltaTime);
		void OnUpdate(float deltaTime);
		void OnLateUpdate(float deltaTime);
		void OnAppInput(int x, int y, int action, int key);
		//void OnAppEvent(BasicEvent* event);
		void OnStop();

	private:
		void GameView();
		void Menu();
		void EntytiesList();
		void Docking();

	};
}