#include "SceneGuiInspectorWindow.h"
#include <imgui.h>
#include "../../Utils/StringUtils.h"
#include "IInspectable.h"

void SceneGuiInspectorWindow::renderInspectables()
{
    m_scene->RenderImGui();

    if (ImGui::CollapsingHeader("Entities"))
    {
        for (const auto& entity : m_entities)
        {
            std::string label = StringUtils::runtime_type_name(*entity) +
                "##" + std::to_string(reinterpret_cast<uintptr_t>(entity.get()));
            if (ImGui::TreeNode(label.c_str()))
            {
                auto inspectableComponents = entity->getAllComponentsOfType<IInspectable>();
                for (auto inspectableComponent : inspectableComponents)
                {
                    std::string inspectableComponentLabel = StringUtils::runtime_type_name(*inspectableComponent) +
                        "##" + std::to_string(reinterpret_cast<uintptr_t>(inspectableComponent.get()));
                    if (ImGui::CollapsingHeader(inspectableComponentLabel.c_str()))
                    {
                        inspectableComponent->RenderImGui();
                    }
                }

                ImGui::TreePop();
            }
        }
    }
}
