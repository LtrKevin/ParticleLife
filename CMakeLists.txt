cmake_minimum_required(VERSION 3.20)
project(ParticleLife)

set(CMAKE_POLICY_VERSION_MINIMUM 3.5)

set(CMAKE_CXX_STANDARD 17)

include(FetchContent)

FetchContent_Declare(
        SFML
        GIT_REPOSITORY https://github.com/SFML/SFML.git
        GIT_TAG 3.0.0
)

set(SFML_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(SFML_BUILD_TESTS OFF CACHE BOOL "" FORCE)

FetchContent_MakeAvailable(SFML)

add_executable(ParticleLife main.cpp
        src/entities/Particle.cpp
        src/entities/Particle.h
        src/entities/Particle.h
        src/core/constants.h
        src/core/physics.h
        src/systems/grid.cpp
        src/systems/grid.h)

target_link_libraries(ParticleLife SFML::Graphics SFML::Window SFML::System)
