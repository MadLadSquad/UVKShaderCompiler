#include "Vulkan.hpp"
#include <shaderc/shaderc.hpp>
//#include "../spirv-cross/spirv_cross.hpp"
//#include "../spirv-cross/spirv_glsl.hpp"
//#include "../spirv-cross/spirv_hlsl.hpp"

std::vector<uint32_t> USC::generateVulkanBinaries(const std::string& loc, const std::string& shaderLoc, const std::string& filename, const shaderc_shader_kind& shaderType)
{
    shaderc::Compiler compiler;
    shaderc::CompileOptions options;

    options.SetTargetEnvironment(shaderc_target_env_vulkan, shaderc_env_version_vulkan_1_2);
    options.SetOptimizationLevel(shaderc_optimization_level_performance);

    std::string buffer;
    std::ifstream in(static_cast<std::string>(std::string(loc) + "Content/" + shaderLoc));
    loadData(buffer, in);
    in.close();

    shaderc::SpvCompilationResult result = compiler.CompileGlslToSpv(buffer, shaderType, static_cast<std::string>(std::string(loc) + "Content/" + shaderLoc).c_str(), options);

    if (result.GetCompilationStatus() != shaderc_compilation_status_success)
    {
        std::cout << "\x1b[31mError when creating a shader binary: " << result.GetErrorMessage() << "\x1b[0m" << std::endl;
        std::terminate();
    }

    auto data = std::vector<uint32_t>(result.cbegin(), result.cend());
    std::ofstream out(static_cast<std::string>(std::string(loc) + "Generated/" + filename + ".spv").c_str(), std::ios::out | std::ios::binary);

    out.write((char*)data.data(), data.size() * sizeof(uint32_t));
    out.flush();
    out.close();

    return data;
}