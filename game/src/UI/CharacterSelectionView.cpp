#include "CharacterSelectionView.h"
#include <imgui.h>
#include "../Global/Globals.h"

#include <BirdRegistry.h>
#include "../Signals/PlayerChangedSignal.h"

CharacterSelectionView::CharacterSelectionView(std::shared_ptr<Signals::SignalHandler> signalHandler) : m_signalHandler(signalHandler), m_characters(BirdRegistry::getAllEntries())
{
    // calculating values in constructor so it's only calculated once.
    m_totalArrowWidth = m_arrowButtonSize * 2 + m_spacing;
    m_arrowX = (Window_Width - m_totalArrowWidth) * 0.5f;
}

void CharacterSelectionView::init()
{
    m_signalHandler->invokeSignal(PlayerChangedSignal
        {
            nullptr, BirdRegistry::getInstance(m_characters[m_selectedIndex])
        });
}

void CharacterSelectionView::renderImGui()
{
    // ---------- Centered arrow group with name in between
    // Position arrows and text as a group
    ImGui::SetCursorPos(ImVec2(m_arrowX, Window_Height - 260.0f));

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
    float availableSpace = m_spacing;
    float textX = (availableSpace - textWidth) * 0.5f;

    ImGui::SetCursorPosX(ImGui::GetCursorPosX() + textX);
    ImGui::Text("%s", characterName);

    // Right arrow
    ImGui::SameLine();
    ImGui::SetCursorPosX(m_arrowX + m_arrowButtonSize + m_spacing); // after left arrow + spacing
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
    m_signalHandler->invokeSignal(PlayerChangedSignal
        {
            BirdRegistry::getInstance(m_characters[previousSelected]), BirdRegistry::getInstance(m_characters[m_selectedIndex])
        });
}
