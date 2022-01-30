#pragma once
#include "AppFrame.h"

namespace ArcticFox {
	class Application : public AppFrame::Application {
	public:
		Application(AppFrame::AppConfig* config);

		virtual void Run() override;
		virtual void OnEarlyUpdate() override;
		virtual void OnUpdate() override;
		virtual void OnLateUpdate() override;
		virtual bool OnEvent(AppFrame::BasicEvent & event) override;
		bool Close();
		virtual void Stop() override;

		virtual ~Application();
	private:
		bool m_Close;
	};
}