#pragma once

#include <memory>
#include <string>
#include <Scene.h>

namespace Scenes
{
    class ISceneManager
    {
    public:
        virtual ~ISceneManager() = default;

        virtual void addScene(const std::string& sceneName, std::shared_ptr<Scene> scene) = 0;
        virtual void loadScene(const std::string& sceneName) = 0;
        virtual void unloadScene(const std::string& sceneName) = 0;

        virtual std::vector<std::shared_ptr<Scene>> getActiveScenes() = 0;

        virtual void update(float deltaTime) = 0;
        virtual void render() = 0;
        virtual void renderImGui() = 0;
    };
}