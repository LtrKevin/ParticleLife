#pragma once

#include <cmath>
#include "SFML/System/Vector2.hpp"
#include "constants.h"

namespace forces {
    inline sf::Vector2f computeGravity(const float mass) {
        return {0, mass * config::gravityPresets[config::currentPlanet].value};
    }

    inline sf::Vector2f computeAirFriction(const sf::Vector2f& velocity) {
        return -velocity * config::AIR_FRICTION;
    }

    inline sf::Vector2f computeMouseAttraction(const sf::Vector2f& distanceToMouse, const sf::Vector2f& velocity, const float mass) {
        if (distanceToMouse.lengthSquared() > 400*400 || distanceToMouse.lengthSquared() == 0) return {0,0};

        // F = k*d - c*v avec c=2sqrt(k*m) -> Amortissement critique
        return config::MOUSE_ATTRACTION * distanceToMouse - 2.0f * std::sqrt(config::MOUSE_ATTRACTION * mass) * 0.5f * velocity;
    }

    inline sf::Vector2f computeCollisionImpulsion(
        const sf::Vector2f& distanceBtoA,
        const float mass_a,
        const sf::Vector2f& velocity_a,
        const float mass_b,
        const sf::Vector2f& velocity_b
    ) {
        const auto N = distanceBtoA.normalized();
        const auto relativeVelocity = velocity_a - velocity_b;
        const auto relativeVelocityNLength = relativeVelocity.dot(N);

        if (relativeVelocityNLength > 0) return {0,0};

        const float impulsion = -(1 + config::RESTITUTION)*relativeVelocityNLength/(1/mass_a + 1/mass_b);

        return impulsion * N;
    }
}