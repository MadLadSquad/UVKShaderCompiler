#include <iostream>


enum ShaderType
{
    VERTEX,
    FRAGMENT,
    COMPUTE,
    GEOMETRY,
    TESSELATION
};

enum ShaderLanguageType
{
    HLSL,
    GLSL,
    MSL,
    GLSLV,
    SPV
};

int main(int argc, char** argv)
{
    bool bOpenGL = false;
    ShaderType type;
    ShaderLanguageType languageType;
    std::string inputLocation;
    std::string outputLocation;

    if (argv[1] && argv[2] && argv[3] && argv[4] && argv[5] && argv[6])
    {
        std::string a[6] = { argv[1], argv[2], argv[3], argv[4], argv[5], argv[6] };

        if (a[0] == "--open-gl")
        {
            bOpenGL = true;
        }
        else if (a[0] == "--vulkan")
        {
            bOpenGL = false;
        }
        else
        {
            return -1;
        }

        if (a[1] == "--vertex")
        {
            type = VERTEX;
        }
        else if (a[1] == "--fragment")
        {
            type = FRAGMENT;
        }
        else if (a[1] == "--geometry")
        {
            type = GEOMETRY;
        }
        else if (a[1] == "--tesselation")
        {
            type = TESSELATION;
        }
        else if (a[1] == "--compute")
        {
            type = COMPUTE;
        }
        else
        {
            return -2;
        }

        if (a[2] == "--hlsl")
        {
            languageType = HLSL;
        }
        else if (a[2] == "--glsl")
        {
            languageType = GLSL;
        }
        else if (a[2] == "--msl")
        {
            languageType = MSL;
        }
        else if (a[2] == "--glsl-v")
        {
            languageType = GLSLV;
        }
        else if (a[2] == "--spv")
        {
            languageType = SPV;
        }
        else
        {
            return -3;
        }

        inputLocation = a[4];
        outputLocation = a[5];


#ifdef _WIN32
        std::string command;
                switch (languageType)
        {
        case GLSL:
            command = "cd .. && glslangValidator.exe -G " + inputLocation + "-o" + outputLocation;
            system(command.c_str());

            break;
        case GLSLV:
            command = "cd .. && glslangValidator.exe -V " + inputLocation + "-o" + outputLocation;
            system(command.c_str());

            break;
        case HLSL:


            break;
        case MSL:

            break;
        case SPV:

            break;
        }
#else
        std::string command;
        switch (languageType)
        {
        case GLSL:
            command = "cd .. && glslangValidator -G " + inputLocation + "-o" + outputLocation;
            system(command.c_str());

            break;
        case GLSLV:
            command = "cd .. && glslangValidator -V " + inputLocation + "-o" + outputLocation;
            system(command.c_str());

            break;
        case HLSL:


            break;
        case MSL:

            break;
        case SPV:

            break;
        }
#endif
    }
}
