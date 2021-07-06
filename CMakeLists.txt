cmake_minimum_required(VERSION 3.17)
project(UVKShaderCompiler)

set(CMAKE_CXX_STANDARD 17)
include_directories(ThirdParty/libshaderc/include/)
include_directories(spirv-cross/include)
add_subdirectory(ThirdParty)
add_subdirectory(spirv-cross)

file(GLOB_RECURSE SRC "Src/*.hpp" "Src/*.h" "Src/*.cpp")

add_executable(UVKShaderCompiler ${SRC})
target_link_libraries(UVKShaderCompiler shaderc glslang SPIRV-Tools SPIRV-Tools-opt SPIRV OGLCompiler OSDependent spirv-cross-cpp)