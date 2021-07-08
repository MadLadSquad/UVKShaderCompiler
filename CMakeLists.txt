cmake_minimum_required(VERSION 3.17)
project(UVKShaderCompiler)

set(CMAKE_CXX_STANDARD 17)
include_directories(ThirdParty/shaderc/libshaderc/include/)
include_directories(ThirdParty/spirv-cross/include)
add_subdirectory(ThirdParty/shaderc/)
add_subdirectory(ThirdParty/spirv-cross/include)

file(GLOB_RECURSE SRC "Src/*.hpp" "Src/*.h" "Src/*.cpp")

add_executable(UVKShaderCompiler ${SRC})
target_link_libraries(UVKShaderCompiler shaderc glslang SPIRV-Tools SPIRV-Tools-opt SPIRV OGLCompiler OSDependent spirv-cross-cpp)