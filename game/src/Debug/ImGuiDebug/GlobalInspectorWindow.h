#pragma once
#include "ImGuiInspectorWindow.h"

#include <memory>
#include <ISceneManager.h>

class GlobalInspectorWindow : public ImGuiInspectorWindow
{
public:
	GlobalInspectorWindow(std::shared_ptr<ISceneManager> sceneManager);

protected:
	void renderInspectables() override;

private:
	std::shared_ptr<ISceneManager> m_sceneManager;
};

