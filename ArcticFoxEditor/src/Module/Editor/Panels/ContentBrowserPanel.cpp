#include "ContentBrowserPanel.h"

Editor::ContentBrowserPanel::ContentBrowserPanel() {
	m_MountDirectory = (AppFrame::PhysicalMountPoint*)AppFrame::VFS::GetInstance()->GetMount("C:/Users/Kosmosas/Desktop/Application/");
}

void Editor::ContentBrowserPanel::OnImGuiRender() {
/*	for (m_MountDirectory->) {

	}
	*/
}