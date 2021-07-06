#include "Vulkan.hpp"
#include "OpenGL.hpp"

//#define DEBUG
#ifndef DEBUG
    constexpr const char* loc = "../../";
#else
    constexpr const char* loc = "./";
#endif


int main(int argc, char** argv)
{
    if (argc > 1 )
    {
        if (std::string(argv[1]) == "--help")
        {
            showHelpMessage();
            return 0;
        }
        else
        {
            shaderc_shader_kind shaderType;
            std::string shaderLoc = argv[1];
            std::string filename = shaderLoc;

            init(filename, shaderLoc, shaderType);

            auto vkBin = generateVulkanBinaries(loc, shaderLoc, filename, shaderType);
            std::cout << "[SUCCESS] UVKShaderCompiler: Compiled Vulkan Shader" << std::endl;

            generateOpenGLBinaries(vkBin, loc, shaderLoc, filename, shaderType);

            return 0;
        }
    }

    std::cout << "Not enough arguments passed" << std::endl;
    showHelpMessage();
    return 0;
}
