#pragma once
#include <iostream>
#include <fstream>
#include <vector>

#ifdef _WIN32
    #ifdef USC_LIB_COMPILE
        #define USC_PUBLIC_API __declspec(dllexport)
    #else
        #define USC_PUBLIC_API __declspec(dllimport)
    #endif
#else
    #define USC_PUBLIC_API
#endif

namespace USC
{
    inline std::string prefixDir = "../../";
    USC_PUBLIC_API void setPrefixDir(const char* pt = "../../");
}