#pragma once
#include <AppFrame.h>

namespace Editor {
	class ContentBrowserPanel {
	public:
		ContentBrowserPanel();

		void OnImGuiRender();

	private:
		AppFrame::PhysicalMountPoint* m_MountDirectory;
	};
}