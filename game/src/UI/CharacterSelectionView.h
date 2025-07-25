#pragma once
#include<memory>
#include <Scene.h>
#include <SignalHandler.h>
#include <IBird.h>

#include <vector>
#include <string>

/// <summary>
/// Constucts character selection view ImGui controls.
/// It invokes signal when characters are selected.
/// </summary>
class CharacterSelectionView
{
public:
	CharacterSelectionView(std::shared_ptr<Signals::SignalHandler> signalHandler);
	void init();

	void renderImGui();

private:
	void select(int direction);

	std::shared_ptr<Signals::SignalHandler> m_signalHandler;
	std::vector<std::string> m_characters;

	int m_selectedIndex = 0;

	// ImGui view data
	float m_arrowButtonSize = 30.0f;
	float m_spacing = 125.0f;
	float m_totalArrowWidth;
	float m_arrowX;
};