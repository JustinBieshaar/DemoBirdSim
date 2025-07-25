#pragma once
#include <string>

class ImGuiInspectorWindow
{
public:
	ImGuiInspectorWindow(const char* windowName);
	void render();
	virtual void clear() {} // can be overriden

protected:
	// This will be called within render so each inheritent
	// can control how they are being inspected.
	virtual void renderInspectables() = 0;

private:
	const char* m_windowName;
};

