cmake_minimum_required(VERSION 4.3)
project(OrbitSim LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

find_package(SFML 3 COMPONENTS Graphics Window System REQUIRED)

add_executable(OrbitSim
    src/main.cpp
    src/Simulator.cpp
    src/renderer/Renderer.cpp
    src/physics/PhysicsEngine.cpp
    src/core/Timer.cpp
)

target_include_directories(OrbitSim PRIVATE include)
target_link_libraries(OrbitSim PRIVATE SFML::Graphics SFML::Window SFML::System)
target_compile_definitions(OrbitSim PRIVATE PROJECT_ROOT="${CMAKE_SOURCE_DIR}")