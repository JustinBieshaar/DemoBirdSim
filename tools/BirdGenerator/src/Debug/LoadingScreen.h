#pragma once
#include <imgui.h>
#include <string>
#include <chrono>

/// <summary>
/// Quick and dirty easy accessible loading screen.
/// I am definetly NOT proud of this, but making it static got the job done quickly.
/// Plus as it has a single purpose I did not feel to bad for it. Just a bit ashamed it's static.
/// 
/// (It would've been better to use SimpleDI in this tool.. my apologies <3)
/// </summary>
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
        // only showing when it is loading.
        if (!s_isLoading)
            return;

        // this so short loading times won't be affecting
        auto now = std::chrono::steady_clock::now();
        std::chrono::duration<float> elapsed = now - s_startTime;

        // Only show when time is passed.
        // This is so we can prevent having very quick loads showing a loading screen.
        // As if something takes e.g. 0.3 seconds, it may be just annoying to have a quick loading screen.
        //
        // However, another (may be better solution) is to make it always appear for at least x seconds.
        // This way the loading is clear even when it loads fast. However, this is just a design decision.
        if (elapsed.count() < m_showLoadingAfterSeconds) 
            return;

        // Rendering a full screen window
        // which is black and has a text in the middle.
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