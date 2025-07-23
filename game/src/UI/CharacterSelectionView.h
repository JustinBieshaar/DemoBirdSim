#pragma once
#include<memory>
#include <Scene.h>
#include <SignalHandler.h>
#include <IBird.h>

#include <vector>
#include <string>

class CharacterSelectionView
{
public:
	CharacterSelectionView(std::shared_ptr<SignalHandler> signalHandler);
	void init();

	void renderImGui();

private:
	void select(int direction);

	std::shared_ptr<SignalHandler> m_signalHandler;
	std::vector<std::string> m_characters;

	int m_selectedIndex = 0;
};