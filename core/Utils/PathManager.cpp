#include "PathManager.h"

std::filesystem::path PathManager::resourceRoot = _SOLUTIONDIR; // Default

void PathManager::setResourceRoot(const std::filesystem::path& root)
{
    resourceRoot = root;
}

std::string PathManager::getConfigPath(const std::string& filename)
{
    return (resourceRoot / "resources" / "config" / filename).string();
}

std::string PathManager::getTexturePath(const std::string& filename)
{
    return (resourceRoot / "resources" / "textures" / filename).string();
}

std::string PathManager::getObjPath(const std::string& filename)
{
    return (resourceRoot / "resources" / "obj" / filename).string();
}
