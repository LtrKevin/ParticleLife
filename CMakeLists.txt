cmake_minimum_required(VERSION 3.24)
project(ParticleLife)

# Tolérance pour les vieux scripts CMake (ex: FreeType)
set(CMAKE_POLICY_VERSION_MINIMUM 3.5)
set(CMAKE_CXX_STANDARD 17)

include(FetchContent)

# ==========================================
# 1. SFML (Version 3.0.0)
# ==========================================
set(SFML_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(SFML_BUILD_TESTS OFF CACHE BOOL "" FORCE)

FetchContent_Declare(
        SFML
        GIT_REPOSITORY https://github.com/SFML/SFML.git
        GIT_TAG 3.0.0
        OVERRIDE_FIND_PACKAGE
)
FetchContent_MakeAvailable(SFML)

# ==========================================
# 2. DEAR IMGUI (On le compile à la main !)
# ==========================================
FetchContent_Declare(
        imgui
        GIT_REPOSITORY https://github.com/ocornut/imgui.git
        GIT_TAG v1.91.5
        OVERRIDE_FIND_PACKAGE # On dit à ImGui-SFML : "C'est bon, on gère"
)
FetchContent_MakeAvailable(imgui)

# ⚠️ LA SOLUTION EST ICI : On fabrique la librairie avec les sources
add_library(imgui STATIC
        ${imgui_SOURCE_DIR}/imgui.cpp
        ${imgui_SOURCE_DIR}/imgui_draw.cpp
        ${imgui_SOURCE_DIR}/imgui_tables.cpp
        ${imgui_SOURCE_DIR}/imgui_widgets.cpp
        ${imgui_SOURCE_DIR}/imgui_demo.cpp
)
target_include_directories(imgui PUBLIC $<BUILD_INTERFACE:${imgui_SOURCE_DIR}>)
add_library(imgui::imgui ALIAS imgui) # On crée l'alias exact attendu par ImGui-SFML
set(IMGUI_DIR ${imgui_SOURCE_DIR} CACHE PATH "Chemin vers ImGui" FORCE)

# ==========================================
# 3. IMGUI-SFML (Le pont)
# ==========================================
FetchContent_Declare(
        ImGui-SFML
        GIT_REPOSITORY https://github.com/SFML/imgui-sfml.git
        GIT_TAG v3.0
)
FetchContent_MakeAvailable(ImGui-SFML)

target_include_directories(ImGui-SFML PUBLIC $<BUILD_INTERFACE:${imgui_SOURCE_DIR}>)
# ==========================================
# 4. TON EXÉCUTABLE PRINCIPAL
# ==========================================
add_executable(ParticleLife
        main.cpp
        src/entities/Particle.cpp
        src/entities/Particle.h
        src/core/constants.h
        src/core/physics.h
        src/systems/grid.cpp
        src/systems/grid.h
        src/systems/ui.cpp
        src/systems/ui.h
)

# On lie SFML, ImGui-SFML, et notre nouvelle librairie imgui !
target_link_libraries(ParticleLife PRIVATE
        SFML::Graphics
        SFML::Window
        SFML::System
        ImGui-SFML::ImGui-SFML
        imgui::imgui
)