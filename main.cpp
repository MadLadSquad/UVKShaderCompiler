#include "Src/Vulkan.hpp"

int main(int argc, char** argv)
{
    if (argc > 1)
    {
        USC::setPrefixDir("../../");
        if (std::string(argv[1]) == "--help")
            USC::showHelpMessage();
        else if (std::string(argv[1]) == "--complete-regen")
            USC::recompileShaders();
        else if (std::string(argv[1]) == "--compile")
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
