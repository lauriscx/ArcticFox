#include "ContentBrowserPanel.h"

Editor::ContentBrowserPanel::ContentBrowserPanel() : m_Dir("") {
	m_MountDirectory = (AppFrame::PhysicalMountPoint*)AppFrame::VFS::GetInstance()->GetMount("C:/Users/Kosmosas/Desktop/Application");
	m_Dir = m_MountDirectory->GetPath();
}

void Editor::ContentBrowserPanel::OnImGuiRender() {
	ImGui::Begin("FileExplorer");
	ImGui::Text(m_Dir.string().c_str());
	if(ImGui::Button("Back")) {
		if (m_MountDirectory->GetPath() != m_Dir) {
			m_Dir = m_Dir.parent_path();
		}
	}
	ImGui::Separator();
	for (auto& path : m_MountDirectory->Directories(m_Dir)) {
		std::string _path = path.path().string();
		if (path.is_directory()) {
			if (ImGui::Button(_path.c_str())) {
				m_Dir = path.path();
			}
		} else {
			ImGui::Text(path.path().filename().string().c_str());
		}
	}

	ImGui::End();
}