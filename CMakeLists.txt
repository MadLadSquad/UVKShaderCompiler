cmake_minimum_required(VERSION 3.17)
project(UVKShaderCompilerLib)
project(UVKShaderCompiler)

set(CMAKE_CXX_STANDARD 17)
set(BUILD_SHARED_LIBS OFF)
include_directories(ThirdParty/shaderc/libshaderc/include/)
add_subdirectory(ThirdParty/shaderc/)
set(BUILD_SHARED_LIBS ON)

file(GLOB_RECURSE SRC "src/*.cpp" "ThirdParty/Crypto/*.cpp")
file(GLOB_RECURSE HEAD "src/*.hpp" "ThirdParty/Crypto/sha256.hpp" "ThirdParty/Crypto/*.h")

add_library(UVKShaderCompilerLib SHARED ${SRC} ${HEAD})
add_executable(UVKShaderCompiler main.cpp ${HEAD})

target_compile_definitions(UVKShaderCompilerLib PRIVATE "USC_LIB_COMPILE")
if (WIN32)
    target_compile_options(UVKShaderCompilerLib PRIVATE "/MT;")
endif()

target_link_libraries(UVKShaderCompilerLib shaderc glslang SPIRV-Tools SPIRV-Tools-opt SPIRV )
target_link_libraries(UVKShaderCompiler UVKShaderCompilerLib)
