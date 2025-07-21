#pragma once
#include <string>
#include <filesystem>

class PathManager
{
public:
    static void setResourceRoot(const std::filesystem::path& root);

    static std::string getConfigPath(const std::string& filename);
    static std::string getTexturePath(const std::string& filename);
    static std::string getTexturesFolderPath();
    static std::string getObjPath(const std::string& filename);
    static std::string getObjFolderPath();
    static std::string getShaderPath();

private:
    static std::filesystem::path resourceRoot;
};