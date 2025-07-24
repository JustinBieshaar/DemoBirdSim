#pragma once
#include <string>

class ImGuiInspectorWindow
{
public:
	ImGuiInspectorWindow(const char* windowName);
	void render();
	virtual void clear() {} // can be overriden

protected:
	virtual void renderInspectables() = 0;

private:
	const char* m_windowName;
};

