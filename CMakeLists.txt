cmake_minimum_required(VERSION 3.17)
project(UVKShaderCompilerLib)
project(UVKShaderCompiler)

set(CMAKE_CXX_STANDARD 17)
include_directories(ThirdParty/shaderc/libshaderc/include/)
# include_directories(ThirdParty/spirv-cross/include)
add_subdirectory(ThirdParty/shaderc/)
# add_subdirectory(ThirdParty/spirv-cross/)

file(GLOB_RECURSE SRC "Src/*.cpp" "ThirdParty/Crypto/*.cpp")
file(GLOB_RECURSE HEAD "Src/*hpp" "ThirdParty/Crypto/sha256.hpp" "ThirdParty/Crypto/*.h")

add_library(UVKShaderCompilerLib SHARED ${SRC} ${HEAD})
add_executable(UVKShaderCompiler main.cpp ${HEAD})

target_compile_definitions(UVKShaderCompilerLib PRIVATE "USC_LIB_COMPILE")
target_link_libraries(UVKShaderCompilerLib shaderc glslang SPIRV-Tools SPIRV-Tools-opt SPIRV )
target_link_libraries(UVKShaderCompiler UVKShaderCompilerLib)
