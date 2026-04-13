#ifndef PARTICLELIFE_CONSTANTS_H
#define PARTICLELIFE_CONSTANTS_H

#pragma once
#include <string>

namespace config {
    constexpr unsigned int WINDOW_HEIGHT = 720;
    constexpr unsigned int WINDOW_WIDTH = 1280;
    const std::string WINDOW_TITLE = "Particle Life";

    constexpr float GRAVITY = 500.0f;
    constexpr float RESTITUTION = 0.8f;
    constexpr float AIR_FRICTION = 2.0f;
    constexpr float SLIDE_FRICTION = 40.0f;
    constexpr float VELOCITY_X_THRESHOLD = 1.0f;
    constexpr float GRAVITATIONAL_CONSTANT = 10.0f;
    constexpr float MOUSE_MASS = 100000.0f;
}

#endif //PARTICLELIFE_CONSTANTS_H