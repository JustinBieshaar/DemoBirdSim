#pragma once
#include <imgui.h>
#include <string>
#include <chrono>

// just static for easy access
class LoadingScreen
{

public:
    static void start(const std::string& message = "Loading...")
    {
        s_message = message;
        s_isLoading = true;
        s_startTime = std::chrono::steady_clock::now();
    }

    static void stop()
    {
        s_isLoading = false;
    }

    static bool isLoading()
    {
        return s_isLoading;
    }

    static void render()
    {
        if (!s_isLoading)
            return;

        // this so short loading times won't be affecting
        auto now = std::chrono::steady_clock::now();
        std::chrono::duration<float> elapsed = now - s_startTime;
        if (elapsed.count() < m_showLoadingAfterSeconds) // show only if more than 0.5 seconds passed
            return;

        ImGui::SetNextWindowPos(ImVec2(0, 0));
        ImGui::SetNextWindowSize(ImGui::GetIO().DisplaySize);

        ImGuiWindowFlags flags = ImGuiWindowFlags_NoDecoration
            | ImGuiWindowFlags_NoMove
            | ImGuiWindowFlags_NoSavedSettings
            | ImGuiWindowFlags_NoFocusOnAppearing
            | ImGuiWindowFlags_NoNav
            | ImGuiWindowFlags_AlwaysAutoResize;

        ImGui::Begin("LoadingOverlay", nullptr, flags);

        ImVec2 windowSize = ImGui::GetWindowSize();
        ImVec2 textSize = ImGui::CalcTextSize(s_message.c_str());
        ImGui::SetCursorPos(ImVec2((windowSize.x - textSize.x) * 0.5f, (windowSize.y - textSize.y) * 0.5f));

        ImGui::TextUnformatted(s_message.c_str());

        ImGui::End();
    }

private:
    inline static bool s_isLoading;
    inline static std::string s_message;
    inline static std::chrono::steady_clock::time_point s_startTime;

    inline static float m_showLoadingAfterSeconds = 0.1f;
};