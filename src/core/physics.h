#ifndef PARTICLELIFE_PHYSICS_H
#define PARTICLELIFE_PHYSICS_H

#include "SFML/System/Vector2.hpp"
#include "../entities/particle.h"
#include "constants.h"

#pragma once

namespace forces {
    inline sf::Vector2f computeGravity(const Particle& particle) {
        return {0, particle.getMass() * config::GRAVITY};
    }

    inline sf::Vector2f computeAirFriction(const Particle& particle) {
        return -particle.getVelocity() * config::AIR_FRICTION;
    }
}

#endif //PARTICLELIFE_PHYSICS_H