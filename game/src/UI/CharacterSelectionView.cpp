#include "CharacterSelectionView.h"
#include <imgui.h>
#include "../Global/Globals.h"

#include <BirdRegistry.h>
#include "../Signals/PlayerChangedEvent.h"

CharacterSelectionView::CharacterSelectionView(std::shared_ptr<Signals::SignalHandler> signalHandler) : m_signalHandler(signalHandler), m_characters(BirdRegistry::getAllEntries())
{
}

void CharacterSelectionView::init()
{
    m_signalHandler->invokeEvent(PlayerChangedEvent
        {
            nullptr, BirdRegistry::getInstance(m_characters[m_selectedIndex])
        });
}

void CharacterSelectionView::renderImGui()
{

    // === Centered Arrows Group ===
    float arrowButtonSize = 30.0f;
    float spacing = 125.0f;
    float totalArrowWidth = arrowButtonSize * 2 + spacing;
    float arrowX = (Window_Width - totalArrowWidth) * 0.5f;

    // Position arrows and text as a group
    ImGui::SetCursorPos(ImVec2(arrowX, Window_Height - 260.0f));

    // Left arrow
    if (ImGui::ArrowButton("##left", ImGuiDir_Left))
    {
        select(-1);
    }

    // Text centered between arrows
    ImGui::SameLine();

    // Measure text width
    const char* characterName = m_characters[m_selectedIndex].c_str();
    float textWidth = ImGui::CalcTextSize(characterName).x;

    // Compute space left for text between arrows
    float availableSpace = spacing;
    float textX = (availableSpace - textWidth) * 0.5f;

    ImGui::SetCursorPosX(ImGui::GetCursorPosX() + textX);
    ImGui::Text("%s", characterName);

    // Right arrow
    ImGui::SameLine();
    ImGui::SetCursorPosX(arrowX + arrowButtonSize + spacing); // after left arrow + spacing
    if (ImGui::ArrowButton("##right", ImGuiDir_Right))
    {
        select(1);
    }
}

void CharacterSelectionView::select(int direction)
{
    int previousSelected = m_selectedIndex;
    m_selectedIndex += direction;

    // loop
    if (m_selectedIndex < 0)
    {
        m_selectedIndex = m_characters.size() - 1;
    }
    else if (m_selectedIndex >= m_characters.size())
    {
        m_selectedIndex = 0;
    }

    // invoke newly selected character
    m_signalHandler->invokeEvent(PlayerChangedEvent
        {
            BirdRegistry::getInstance(m_characters[previousSelected]), BirdRegistry::getInstance(m_characters[m_selectedIndex])
        });
}
