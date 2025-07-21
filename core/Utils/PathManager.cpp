#include "PathManager.h"
#include <iostream>

std::filesystem::path PathManager::resourceRoot = _SOLUTIONDIR; // Default

void PathManager::setResourceRoot(const std::filesystem::path& root)
{
    resourceRoot = root;

    std::cout << "Pathmanager resourceRoot changed to: " << resourceRoot << "\n";
}

std::string PathManager::getConfigPath(const std::string& filename)
{
    return (resourceRoot / "resources" / "config" / filename).string();
}

std::string PathManager::getTexturePath(const std::string& filename)
{
    return (resourceRoot / "resources" / "textures" / filename).string();
}

std::string PathManager::getTexturesFolderPath()
{
    return (resourceRoot / "resources" / "textures").string();
}

std::string PathManager::getObjPath(const std::string& filename)
{
    return (resourceRoot / "resources" / "3d-obj" / filename).string();
}

std::string PathManager::getObjFolderPath()
{
    return (resourceRoot / "resources" / "3d-obj").string();
}

std::string PathManager::getShaderPath()
{
    return (resourceRoot / "resources" / "shaders").string() + "/";
}
