cmake_minimum_required(VERSION 3.31)
project(VulkanCourseEngine)

find_package(Vulkan REQUIRED)

include(FetchContent)

FetchContent_Declare(
        glm
        GIT_REPOSITORY "https://github.com/g-truc/glm.git"
        GIT_TAG "1.0.1"
        GIT_SHALLOW TRUE
)

FetchContent_Declare(
        spdlog
        GIT_REPOSITORY "https://github.com/gabime/spdlog.git"
        GIT_TAG "v1.15.2"
        GIT_SHALLOW TRUE
)

FetchContent_Declare(
        glfw
        GIT_REPOSITORY "https://github.com/glfw/glfw.git"
        GIT_TAG "3.4"
        GIT_SHALLOW TRUE
)

FetchContent_Declare(
        microsoft-gsl
        GIT_REPOSITORY "https://github.com/microsoft/GSL.git"
        GIT_TAG "v4.2.0"
        GIT_SHALLOW TRUE
)

FetchContent_MakeAvailable(glm glfw microsoft-gsl spdlog)

file(GLOB_RECURSE VulkanEngineSources CONFIGURE_DEPENDS
    "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/*.h"
)

add_executable(VulkanCourseEngine ${VulkanEngineSources}
        src/CPP/glfw_initialization.cpp
        src/Headers/glfw_initialization.h
        src/Headers/glfw_window.h
        src/CPP/glfw_window.cpp
        src/CPP/glfw_monitor.cpp
        src/Headers/glfw_monitor.h
        src/CPP/graphics.cpp
        src/Headers/graphics.h
        src/CPP/utilities.cpp
        src/Headers/utilities.h
)

target_link_libraries(VulkanCourseEngine PRIVATE Vulkan::Vulkan glm glfw Microsoft.GSL::GSL spdlog)

target_include_directories(VulkanCourseEngine PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/src")

target_compile_features(VulkanCourseEngine PRIVATE cxx_std_20)

target_precompile_headers(VulkanCourseEngine PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/src/Headers/precomp.h")