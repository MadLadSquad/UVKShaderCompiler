#include "Src/Vulkan.hpp"

std::string toLower(std::string str)
{
    for (auto& a : str)
        a = tolower(a);
    return str;
}

int main(int argc, char** argv)
{
    if (argc > 2)
    {
        USC::setPrefixDir(argv[2]);

        if (std::string(argv[1]) == toLower("--help"))
            USC::showHelpMessage();
        else if (std::string(argv[1]) == toLower("--complete-regen"))
            USC::recompileShaders();
        else if (std::string(argv[1]) == toLower("--compile"))
            USC::checkForCompile();
        else
        {
            std::cout << "\x1b[31mInvalid parameter: " << argv[1] << "\x1b[0m" << std::endl;
            USC::showHelpMessage();
        }
        return 0;
    }

    std::cout << "\x1b[31mNot enough arguments passed\x1b[0m" << std::endl;
    USC::showHelpMessage();
    return 0;
}