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
        return {0,0}; //TODO Implement mouse attraction
    }
}

#endif //PARTICLELIFE_PHYSICS_H