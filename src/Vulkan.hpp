#pragma once
#include <shaderc/shaderc.h>
#include "Core.hpp"
#include "Functions.hpp"

namespace USC
{
    USC_PUBLIC_API std::vector<uint32_t> generateVulkanBinaries(const std::string& loc, const std::string& shaderLoc, const std::string& filename, const shaderc_shader_kind& shaderType);
}