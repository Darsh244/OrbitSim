cmake_minimum_required(VERSION 4.3)
project(OrbitSim LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)


# Dependencies
include(FetchContent)

# SFML
FetchContent_Declare(
    SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 3.0.2
    GIT_SHALLOW ON
    EXCLUDE_FROM_ALL
    SYSTEM
)

FetchContent_MakeAvailable(SFML)


# ImGui
FetchContent_Declare(
    ImGui
    GIT_REPOSITORY https://github.com/ocornut/imgui.git
    GIT_TAG v1.91.9b
    GIT_SHALLOW ON
    EXCLUDE_FROM_ALL
    SYSTEM
)

FetchContent_MakeAvailable(ImGui)

FetchContent_GetProperties(ImGui SOURCE_DIR IMGUI_DIR)


# ImGui-SFML
set(IMGUI_SFML_FIND_SFML OFF)

FetchContent_Declare(
    ImGui-SFML
    GIT_REPOSITORY https://github.com/SFML/imgui-sfml.git
    GIT_TAG v3.0
    GIT_SHALLOW ON
    EXCLUDE_FROM_ALL
    SYSTEM
)

FetchContent_MakeAvailable(ImGui-SFML)


# OrbitSim
add_executable(OrbitSim
    src/main.cpp
    src/Simulator.cpp
    src/renderer/Renderer.cpp
    src/physics/PhysicsEngine.cpp
    src/core/Timer.cpp
    src/core/Camera.cpp
    src/core/UI.cpp
)

target_include_directories(OrbitSim PRIVATE include)
target_link_libraries(OrbitSim PRIVATE
    SFML::Graphics
    SFML::Window
    SFML::System
    ImGui-SFML::ImGui-SFML
)
target_compile_definitions(OrbitSim PRIVATE PROJECT_ROOT="${CMAKE_SOURCE_DIR}")