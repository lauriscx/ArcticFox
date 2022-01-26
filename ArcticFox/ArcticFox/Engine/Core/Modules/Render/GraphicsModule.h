#pragma once
/*#include "Core/Core.h"
#include "Core/ModuleSystem/Module.h"*/
#include <AppFrame.h>

#include "GraphicsContext.h"
/*#include "Engine/Core/Modules/Render/Renderer.h"
#include "Engine/Core/Modules/Render/Mesh.h"*/
#include "Engine/Core/Modules/Render/Shader.h"
#include "Buffer.h"
#include "Camera.h"
#include "Texture.h"

#include "../OrthographicCameraController.h"

/*#include "Application/Modules/Render/Mesh.h"
#include "Application/Modules/Render/Renderer.h"*/


class /*ENGINE_API*/ GraphicsModule : public AppFrame::Module {
public:
	GraphicsModule();

	virtual void OnStart() override;
	virtual void OnEarlyUpdate(float deltaTime) override;
	virtual void OnUpdate(float deltaTime) override;
	virtual void OnLateUpdate(float deltaTime) override;
	virtual void OnAppInput(int x, int y, int action, int key) override;
	virtual void OnAppEvent(AppFrame::BasicEvent* event);
	virtual void OnStop() override;

	virtual ~GraphicsModule();
private:
	Graphics::OrthographicCameraController m_Controller;

	Graphics::GraphicsContext* m_GraphicsContext;
	/*Graphics::OpenGL::Mesh* m_Mesh;
	Graphics::OpenGL::Renderer* m_Renderer;*/
	Graphics::ShaderLibrary m_ShaderLibrary;

	Graphics::Texture* m_Texture;

	Graphics::VertexArray* VAO;
	Graphics::VertexBuffer* VBO;
	Graphics::IndexBuffer* IBO;

	//Graphics::OrthographicCamera m_Camera;

};