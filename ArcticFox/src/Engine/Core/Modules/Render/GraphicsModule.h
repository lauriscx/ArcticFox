#pragma once
#include <AppFrame.h>

#include "Engine/Core/Modules/Render/GraphicsContext.h"
#include "Engine/Core/Modules/Render/Render2D.h"
#include "Engine/Core/Modules/Render/RenderCommand.h"
#include "Engine/Core/Modules/Render/RendererAPI.h"
#include "Engine/Core/Modules/Render/Renderer.h"

namespace ArcticFox {
	class /*ENGINE_API*/ GraphicsModule : public AppFrame::Module {
	public:
		GraphicsModule();

		virtual void OnStart() override;
		virtual void OnEarlyUpdate(float deltaTime) override;
		virtual void OnUpdate(float deltaTime) override;
		virtual void OnLateUpdate(float deltaTime) override;
		virtual void OnAppInput(const AppFrame::InputData& input) override;
		virtual void OnAppEvent(AppFrame::BasicEvent* event);
		virtual void OnStop() override;

		virtual ~GraphicsModule();
	private:
		Graphics::GraphicsContext* m_GraphicsContext;
	};
}