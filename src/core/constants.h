#ifndef PARTICLELIFE_CONSTANTS_H
#define PARTICLELIFE_CONSTANTS_H

#pragma once
#include <string>

namespace config {
    enum Planet {Earth, Moon, ZeroG, count};

    struct GravityPreset {
        const char* name;
        float value;
    };

    constexpr unsigned int WINDOW_HEIGHT = 720;
    constexpr unsigned int WINDOW_WIDTH = 1280;
    const std::string WINDOW_TITLE = "Particle Life";

    constexpr float BASE_GRAVITY = 500.0f;

    inline constexpr GravityPreset gravityPresets[] = {
        {"Terre", BASE_GRAVITY},
        {"Lune", BASE_GRAVITY * 0.165f},
        {"Espace", 0}
    };

    constexpr float RESTITUTION = 0.8f;
    constexpr float AIR_FRICTION = 2.0f;
    constexpr float SLIDE_FRICTION = 40.0f;
    constexpr float VELOCITY_X_THRESHOLD = 1.0f;
    constexpr float GRAVITATIONAL_CONSTANT = 10.0f;
    constexpr float MOUSE_ATTRACTION = 1000.0f;

    inline int currentPlanet = Earth;
}

#endif //PARTICLELIFE_CONSTANTS_H