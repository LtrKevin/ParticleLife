#ifndef PARTICLELIFE_PHYSICS_H
#define PARTICLELIFE_PHYSICS_H

#include "SFML/System/Vector2.hpp"
#include "constants.h"

#pragma once

namespace forces {
    inline sf::Vector2f computeGravity(const float mass) {
        return {0, mass * config::GRAVITY};
    }

    inline sf::Vector2f computeAirFriction(const sf::Vector2f& speed) {
        return -speed * config::AIR_FRICTION;
    }

    inline sf::Vector2f computeMouseAttraction(const float mass, const sf::Vector2f& distance) {
        return {0,0}; //TODO: Implement mouse attraction
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

#endif //PARTICLELIFE_PHYSICS_H