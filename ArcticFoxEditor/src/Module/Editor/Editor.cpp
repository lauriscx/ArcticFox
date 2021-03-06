#include "Editor.h"
#include "Engine/Core/Modules/Render/Render2D.h"
#include <AppFrame.h>


void Editor::Editor::OnStart() {
}

void Editor::Editor::OnEarlyUpdate(float deltaTime) {
}

void Editor::Editor::OnUpdate(float deltaTime) {
	Docking();
	EntytiesList();
	Menu();

	auto stats = ArcticFox::Graphics::Render2D::GetStats();
	ImGui::Begin("Render stats");
	ImGui::Text("Draw calls %d", stats.m_DrawCalls);
	ImGui::Text("Quad count %d", stats.m_QuodCount);
	ImGui::Text("Vertex count %d", stats.GetTotalVertexCount());
	ImGui::Text("Index count %d", stats.GetTotalIndexCount());
	ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
	ImGui::End();

	ImGui::Begin("Resource Manager");
	if (ImGui::Button("Release all resources")) {
		AppFrame::ResourceManager::GetInstance()->ReleaseResources();
	}
	for (auto&& [path, resource] : AppFrame::ResourceManager::GetInstance()->GetResources()) {
		ImGui::Text("Resource: usage %d, path %s, memory %d", resource->getRefCount(), resource->GetPath().string().c_str(), resource->GetMemoryUsage());
	}

	ImGui::End();

}

void Editor::Editor::OnLateUpdate(float deltaTime) {
}

void Editor::Editor::OnAppInput(int x, int y, int action, int key) {
}

void Editor::Editor::OnStop() {
}

void Editor::Editor::GameView() {	
}

void Editor::Editor::Menu() {

}
void Editor::Editor::EntytiesList()  {

}

void Editor::Editor::Docking()
{
	static ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_PassthruCentralNode;

	// We are using the ImGuiWindowFlags_NoDocking flag to make the parent window not dockable into,
	// because it would be confusing to have two docking targets within each others.
	ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;

	ImGuiViewport* viewport = ImGui::GetMainViewport();
	ImGui::SetNextWindowPos(viewport->Pos);
	ImGui::SetNextWindowSize(viewport->Size);
	ImGui::SetNextWindowViewport(viewport->ID);
	ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
	ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
	window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
	window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;


	// When using ImGuiDockNodeFlags_PassthruCentralNode, DockSpace() will render our background and handle the pass-thru hole, so we ask Begin() to not render a background.
	if (dockspace_flags & ImGuiDockNodeFlags_PassthruCentralNode)
		window_flags |= ImGuiWindowFlags_NoBackground;

	// Important: note that we proceed even if Begin() returns false (aka window is collapsed).
	// This is because we want to keep our DockSpace() active. If a DockSpace() is inactive, 
	// all active windows docked into it will lose their parent and become undocked.
	// We cannot preserve the docking relationship between an active window and an inactive docking, otherwise 
	// any change of dockspace/settings would lead to windows being stuck in limbo and never being visible.
	ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
	ImGui::Begin("DockSpace", nullptr, window_flags);
	ImGui::PopStyleVar();
	ImGui::PopStyleVar(2);

	// DockSpace
	ImGuiIO& io = ImGui::GetIO();

	if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable)
	{
		ImGuiID dockspace_id = ImGui::GetID("DockSpace");
		ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);
		//ImGui::DockBuilderSetNodeSize(dockspace_id, viewport->Size);

		/*static auto first_time = true;
		if (first_time)
		{
			first_time = false;

			ImGui::DockBuilderRemoveNode(dockspace_id); // clear any previous layout
			ImGui::DockBuilderAddNode(dockspace_id, dockspace_flags | ImGuiDockNodeFlags_DockSpace);
			ImGui::DockBuilderSetNodeSize(dockspace_id, viewport->Size);

			// split the dockspace into 2 nodes -- DockBuilderSplitNode takes in the following args in the following order
			//   window ID to split, direction, fraction (between 0 and 1), the final two setting let's us choose which id we want (which ever one we DON'T set as NULL, will be returned by the function)
			//                                                              out_id_at_dir is the id of the node in the direction we specified earlier, out_id_at_opposite_dir is in the opposite direction
			auto dock_id_left = ImGui::DockBuilderSplitNode(dockspace_id, ImGuiDir_Left, 0.4f, nullptr, &dockspace_id);
			auto dock_id_right = ImGui::DockBuilderSplitNode(dockspace_id, ImGuiDir_Right, 0.4f, nullptr, &dockspace_id);
			auto dock_id_down = ImGui::DockBuilderSplitNode(dockspace_id, ImGuiDir_Down, 0.4f, nullptr, &dockspace_id);
			//auto dock_id_down = ImGui::DockBuilderSplitNode(dockspace_id, ImGuiDir_m, 0.4f, nullptr, &dockspace_id);

			// we now dock our windows into the docking node we made above
			ImGui::DockBuilderDockWindow("Entyties", dock_id_left);
			ImGui::DockBuilderDockWindow("Properties", dock_id_right);
			ImGui::DockBuilderDockWindow("FileExplorer", dock_id_down);
			ImGui::DockBuilderFinish(dockspace_id);
		}*/
	}
	ImGui::End();
}
