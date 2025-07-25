#pragma once
#include "ImGuiInspectorWindow.h"

#include <memory>
#include <ISceneManager.h>

/// <summary>
/// Exposing global values.
/// </summary>
class GlobalInspectorWindow : public ImGuiInspectorWindow
{
public:
	GlobalInspectorWindow(std::shared_ptr<Scenes::ISceneManager> sceneManager);

protected:
	void renderInspectables() override;

private:
	std::shared_ptr<Scenes::ISceneManager> m_sceneManager;
};

