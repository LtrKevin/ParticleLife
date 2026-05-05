#ifndef PARTICLELIFE_CONSTANTS_H
#define PARTICLELIFE_CONSTANTS_H

#pragma once

#include <string>
#include <functional>
#include "integrator/eulerIntegrator.h"
#include "integrator/verletIntegrator.h"

namespace config {
    enum Planet {Earth, Moon, ZeroG, planetCount};
    enum Integrator {Euler, Verlet, intergratorCount};

    struct GravityPreset {
        const char* name;
        float value;
    };

    using IntegratorFactory = std::function<std::unique_ptr<IIntegrator<Utils::ParticleState>>()>;

    struct IntegratorPreset {
        const char* name;
        IntegratorFactory integrator;
    };

    constexpr unsigned int WINDOW_HEIGHT = 720;
    constexpr unsigned int WINDOW_WIDTH = 1280;
    const std::string WINDOW_TITLE = "Particle Life";

    constexpr float BASE_GRAVITY = 500.0f;

    inline const IntegratorPreset integratorPresets[] = {
        {"Euler", [] {return std::make_unique<EulerIntegrator>();}},
        {"Verlet", [] {return std::make_unique<VerletIntegrator>();}}
    };

    inline constexpr GravityPreset gravityPresets[] = {
        {"Terre", BASE_GRAVITY},
        {"Lune", BASE_GRAVITY * 0.165f},
        {"Espace", 0}
    };

    constexpr float RESTITUTION = 0.8f;
    constexpr float AIR_FRICTION = 2.0f;
    constexpr float SLIDE_FRICTION = 40.0f;
    constexpr float VELOCITY_X_THRESHOLD = 1.0f;
    constexpr float MOUSE_ATTRACTION = 1000.0f;

    inline int currentPlanet = Earth;
    inline int currentIntegrator = Euler;
}

#endif //PARTICLELIFE_CONSTANTS_H