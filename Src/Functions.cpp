#include "Functions.hpp"
#include "Vulkan.hpp"
#include <shaderc/shaderc.hpp>
#include <cstring>

// This is for MinGW32 because it is retarded
#ifndef __MINGW32__
    #if __has_include(<filesystem>)
        #include <filesystem>
        #define std_filesystem std::filesystem
    #else
        #include <experimental/filesystem>
        #define std_filesystem std::experimental::filesystem
    #endif
#else
    #error "Compiling against MinGW is not supported!"
#endif
#include <openssl/sha.h>

namespace USC
{
    void init(std::string& filename, const std::string& shaderLoc, shaderc_shader_kind& shaderType);
}
void USC::init(std::string& filename, const std::string& shaderLoc, shaderc_shader_kind& shaderType)
{
    if (filename.find_last_of('/') != std::string::npos)
        filename = filename.erase(0, filename.find_last_of('/'));

    if (shaderLoc.substr(shaderLoc.find_last_of('.')) == ".vert")
        shaderType = shaderc_glsl_vertex_shader;
    else if (shaderLoc.substr(shaderLoc.find_last_of('.')) == ".frag")
        shaderType = shaderc_glsl_fragment_shader;
    else if (shaderLoc.substr(shaderLoc.find_last_of('.')) == ".geom")
        shaderType = shaderc_glsl_geometry_shader;
    else if (shaderLoc.substr(shaderLoc.find_last_of('.')) == ".comp")
        shaderType = shaderc_glsl_compute_shader;
    else if (shaderLoc.substr(shaderLoc.find_last_of('.')) == ".tesc")
        shaderType = shaderc_glsl_tess_control_shader;
    else if (shaderLoc.substr(shaderLoc.find_last_of('.')) == ".tese")
        shaderType = shaderc_glsl_tess_evaluation_shader;
    else
        showNamingStandards();
}

void USC::loadData(std::string& buf, std::ifstream& stream)
{
    std::string it;

    while (std::getline(stream, it))
    {
        buf.append(it + '\n');
        it.clear();
    }
}

void USC::showHelpMessage()
{
    std::cout << R"(UVKShaderCompiler - The universal Untitled Vulkan Game Engine shader compiler
    --help - displays this help message
    --complete-regen - completely regenerates the shader cache
    --compile - compiles the shaders

UVKShaderCompiler, made by MadLad Squad, developed and maintained by Stanislav Vasilev(Madman10K))" << std::endl;
}

void USC::showNamingStandards()
{
    std::cout << "\x1b[31mERROR: File does not conform to shader naming standards!\x1b[0m" << R"(
    .vert - vertex shaders
    .frag - fragment shaders
    .comp - compute shaders
    .geom - geometry shaders
    .tesc - tesselation control shaders
    .tese - tesselation evaluation shaders
UVKShaderCompiler, made by MadLad Squad, developed and maintained by Stanislav Vasilev(Madman10K))" << std::endl;
    std::terminate();
}

void USC::compileShader(const std::string& arg, const std::string& hash)
{
    shaderc_shader_kind shaderType;
    std::string filename = arg;

    USC::init(filename, arg, shaderType);

    auto vkBin = USC::generateVulkanBinaries(prefixDir, arg, hash, shaderType);
    std::cout << "\x1b[32m[SUCCESS] UVKShaderCompiler: Compiled Vulkan Shader\x1b[0m" << std::endl;
}

void USC::checkForCompile()
{
    for (auto& a : std_filesystem::recursive_directory_iterator(prefixDir + "Content/"))
    {
        if (!a.is_directory() && (a.path().extension() == ".vert" || a.path().extension() == ".frag" || a.path().extension() == ".comp" || a.path().extension() == ".geom" || a.path().extension() == ".tesc" || a.path().extension() == ".tese"))
        {
            std::ifstream istream(a.path(), std::ios::ate);
            std::streamsize size = istream.tellg();
            istream.seekg(0, std::ios::beg);

            std::vector<char> buffer(size);
            if (istream.read(buffer.data(), size))
            {
                unsigned char result[SHA256_DIGEST_LENGTH];
                SHA256(reinterpret_cast<unsigned char*>(buffer.data()), buffer.size(), result);

                std::stringstream ss;
                ss << std::hex;
                for (auto& f : result)
                    ss << static_cast<int>(f);

                bool bFound = false;
                for (auto& f : std_filesystem::recursive_directory_iterator(prefixDir + "Generated/"))
                {
                    if (!f.is_directory() && f.path().extension() == ".spv")
                    {
                        auto filename = f.path().filename().string();
                        filename.erase(filename.size() - 4);

                        if (filename == ss.str())
                        {
                            bFound = true;
                            goto exit_loop;
                        }
                    }
                }
exit_loop:
                if (!bFound)
                {
                    recompileShaders();
                    return;
                }
            }
        }
    }
}

void USC::recompileShaders()
{
    // Remove all old shader cache objects
    for (auto& a : std_filesystem::directory_iterator(prefixDir + "Generated/"))
        if (a.path().extension() == ".spv" && !a.is_directory())
            std_filesystem::remove_all(a.path());
    for (auto& a : std_filesystem::recursive_directory_iterator(prefixDir + "Content/"))
    {
        if (!a.is_directory() && (a.path().extension() == ".vert" || a.path().extension() == ".frag" || a.path().extension() == ".comp" || a.path().extension() == ".geom" || a.path().extension() == ".tesc" || a.path().extension() == ".tese"))
        {
            std::ifstream istream(a.path(), std::ios::ate);
            std::streamsize size = istream.tellg();
            istream.seekg(0, std::ios::beg);

            std::vector<char> buffer(size);
            if (istream.read(buffer.data(), size))
            {
                unsigned char result[SHA256_DIGEST_LENGTH];
                SHA256(reinterpret_cast<unsigned char*>(buffer.data()), buffer.size(), result);

                std::stringstream ss;
                ss << std::hex;
                for (auto& f : result)
                    ss << static_cast<int>(f);

                auto tmp = a.path().string();
                tmp.erase(0, strlen((prefixDir + "Content/").c_str()));
                compileShader(tmp, ss.str());
            }
        }
    }
}