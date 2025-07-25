#pragma once
#include <string>
#include <filesystem>

/// <summary>
/// This is a manager which controls where and how to find paths.
/// This is only tested on windows and I must admit it may not be the best and/or most ideal
/// implementations. But it did the trick for me. :)
/// </summary>
class PathManager
{
public:
    /// <summary>
    /// Set resources root for the paths to work.
    /// This is a necessity if used cross libraries/executables. So the root is set
    /// accordingly to where we are calling this from.
    /// </summary>
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