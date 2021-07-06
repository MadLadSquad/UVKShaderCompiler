#pragma once
#include "Core.hpp"

static void generateOpenGLBinaries(const std::vector<uint32_t>& data, const std::string& loc, const std::string& shaderLoc, const std::string& filename, const shaderc_shader_kind& shaderType)
{
    shaderc::Compiler compiler;
    shaderc::CompileOptions options;
    options.SetTargetEnvironment(shaderc_target_env_opengl, shaderc_env_version_opengl_4_5);
    options.SetOptimizationLevel(shaderc_optimization_level_performance);

    spirv_cross::CompilerGLSL compilerglsl(data);
    std::string glslCompiled = compilerglsl.compile();

    auto result = compiler.CompileGlslToSpv(glslCompiled, shaderType, static_cast<std::string>(std::string(loc) + "Content/" + shaderLoc).c_str());
    if (result.GetCompilationStatus() != shaderc_compilation_status_success)
    {
        std::cout << "OpenGL compilation error: " << result.GetErrorMessage();
        return;
    }

    auto binary = std::vector<uint32_t>(result.begin(), result.end());

    std::ofstream out(static_cast<std::string>(std::string(loc) + "Generated/" + filename + ".gl.spv").c_str(), std::ios::out | std::ios::binary);
    if (out.is_open())
    {
        out.write((char*)binary.data(), binary.size() * sizeof(uint32_t));
        out.flush();
        out.close();
    }
}