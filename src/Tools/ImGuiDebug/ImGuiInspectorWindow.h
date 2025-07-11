#pragma once
#include <string>

class ImGuiInspectorWindow
{
public:
	ImGuiInspectorWindow(const char* windowName);
	void render();

protected:
	virtual void renderInspectables() = 0;

private:
	const char* m_windowName;
};

