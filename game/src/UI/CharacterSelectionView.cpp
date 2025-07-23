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
    float spacing = 50.0f;
    float totalArrowWidth = arrowButtonSize * 2 + spacing;
    float arrowX = (Window_Width - totalArrowWidth) * 0.5f;

    ImGui::SetCursorPos(ImVec2(arrowX, Window_Height - 260.0f));
    if (ImGui::ArrowButton("##left", ImGuiDir_Left))
    {
        select(-1);
    }

    ImGui::SameLine();
    ImGui::SetCursorPosX(ImGui::GetCursorPosX() + spacing);

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
