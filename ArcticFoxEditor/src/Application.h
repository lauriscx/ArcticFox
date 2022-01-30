#pragma once

#include "Engine/Core/Application.h"

/*#include "Engine/Core/Modules/Render/Renderer.h"
#include "Engine/Core/Modules/Render/Mesh.h"*/
#include "Engine/Core/Modules/Render/Shader.h"
#include "Engine/Core/Modules/Render/Buffer.h"
#include "Engine/Core/Modules/Render/Camera.h"
#include "Engine/Core/Modules/Render/Texture.h"

#include "Engine/Core/Modules/OrthographicCameraController.h"
#include "Engine/Core/Modules/Render/FrameBuffer.h"

/*#include "Application/Modules/Render/Mesh.h"
#include "Application/Modules/Render/Renderer.h"*/

namespace Editor {
	class Application : public ArcticFox::Application {
	public:
		Application(AppFrame::AppConfig* config);

		virtual void Run() override;
		virtual void OnEarlyUpdate() override;
		virtual void OnUpdate() override;
		virtual void OnLateUpdate() override;
		virtual bool OnInput(int x, int y, int action, int key) override;
		virtual bool OnEvent(AppFrame::BasicEvent & event) override;
		virtual void Stop() override;

		virtual ~Application();
	private:

		ArcticFox::Graphics::OrthographicCameraController m_Controller;


		/*Graphics::OpenGL::Mesh* m_Mesh;
		Graphics::OpenGL::Renderer* m_Renderer;*/
		ArcticFox::Graphics::ShaderLibrary m_ShaderLibrary;

		ArcticFox::Graphics::Texture* m_Texture;
		ArcticFox::Graphics::Texture* m_Texture2;

		ArcticFox::Graphics::VertexArray* VAO;
		ArcticFox::Graphics::VertexBuffer* VBO;
		ArcticFox::Graphics::IndexBuffer* IBO;
		ArcticFox::Graphics::FrameBuffer* FBO;
		float rotation = 0;
		float x;
		float y;

		glm::vec2 m_vieportSize;
	};
}