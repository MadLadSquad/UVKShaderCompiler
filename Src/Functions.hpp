#pragma once
#include "Core.hpp"

static void loadData(std::string& buf, std::ifstream& stream)
{
    std::string it;

    while (std::getline(stream, it))
    {
        buf.append(it + '\n');
        it.clear();
    }
}

static void showNamingStandards()
{
    std::cout << R"(ERROR: File does not conform to shader naming standards!
    .vert - vertex shaders
    .frag - fragment shaders
    .comp - compute shaders
    .geom - geometry shaders
    .tesc - tesselation control shaders
    .tese - tesselation evaluation shaders
UVKShaderCompiler, made by MadLad Squad, developed and maintained by Stanislav Vasilev(Madman10K))" << std::endl;
}

static void init(std::string& filename, const std::string& shaderLoc, shaderc_shader_kind& shaderType)
{
    if (filename.find_last_of('/') != std::string::npos)
        filename = filename.erase(0, filename.find_last_of('/'));

    if (shaderLoc.substr(shaderLoc.find_last_of('.')) == ".vert")
    {
        shaderType = shaderc_glsl_vertex_shader;
    }
    else if (shaderLoc.substr(shaderLoc.find_last_of('.')) == ".frag")
    {
        shaderType = shaderc_glsl_fragment_shader;
    }
    else if (shaderLoc.substr(shaderLoc.find_last_of('.')) == ".geom")
    {
        shaderType = shaderc_glsl_geometry_shader;
    }
    else if (shaderLoc.substr(shaderLoc.find_last_of('.')) == ".comp")
    {
        shaderType = shaderc_glsl_compute_shader;
    }
    else if (shaderLoc.substr(shaderLoc.find_last_of('.')) == ".tesc")
    {
        shaderType = shaderc_glsl_tess_control_shader;
    }
    else if (shaderLoc.substr(shaderLoc.find_last_of('.')) == ".tese")
    {
        shaderType = shaderc_glsl_tess_evaluation_shader;
    }
    else
    {
        showNamingStandards();
    }
}

static void showHelpMessage()
{
    std::cout << R"(UVKShaderCompiler - The universal Untitled Vulkan Game Engine shader compiler
    --help - displays this help message
    --vk <input file location> - compiles a shader to a Vulkan shader cache format
    --gl <input file location> - compiles a shader to an OpenGL shader cache format
UVKShaderCompiler, made by MadLad Squad, developed and maintained by Stanislav Vasilev(Madman10K))" << std::endl;
}