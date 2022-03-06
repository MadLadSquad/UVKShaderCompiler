#pragma once
#include "Core.hpp"

namespace USC
{
    USC_PUBLIC_API void checkForCompile();
    USC_PUBLIC_API void recompileShaders();

    USC_PUBLIC_API void loadData(std::string& buf, std::ifstream& stream);
    USC_PUBLIC_API void showNamingStandards();
    USC_PUBLIC_API void showHelpMessage();

    USC_PUBLIC_API void compileShader(const std::string& arg, const std::string& hash);
}