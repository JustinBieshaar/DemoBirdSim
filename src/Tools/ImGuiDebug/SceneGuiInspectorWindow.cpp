#include "SceneGuiInspectorWindow.h"
#include <imgui.h>
#include "../../Utils/StringUtils.h"
#include "IInspectable.h"

void SceneGuiInspectorWindow::renderInspectables()
{
    if (ImGui::Begin("Entities"))
    {
        for (const auto& entity : m_entities)
        {
            std::string label = "Entity " + StringUtils::runtime_type_name(*entity) +
                "##" + std::to_string(reinterpret_cast<uintptr_t>(entity.get()));
            if (ImGui::TreeNode(label.c_str()))
            {
                auto inspectableComponents = entity->getAllComponentsOfType<IInspectable>();
                for (auto inspectableComponent : inspectableComponents)
                {
                    inspectableComponent->RenderImGui();
                }

                ImGui::TreePop();
            }
        }
    }
    ImGui::End();
}
