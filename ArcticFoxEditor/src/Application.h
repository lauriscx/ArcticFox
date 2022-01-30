#pragma once

#include "Engine/Core/Application.h"

namespace Editor {
	class Application : public ArcticFox::Application {
	public:
		Application(AppFrame::AppConfig* config);

		virtual void Run() override;
		virtual void OnEarlyUpdate() override;
		virtual void OnUpdate() override;
		virtual void OnLateUpdate() override;
		virtual bool OnEvent(AppFrame::BasicEvent & event) override;
		virtual void Stop() override;

		virtual ~Application();
	};
}