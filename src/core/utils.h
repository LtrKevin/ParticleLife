#pragma once

#include "SFML/System/Vector2.hpp"

namespace Utils {
    struct ParticleState {
        sf::Vector2f position;
        sf::Vector2f velocity;
        sf::Vector2f acceleration;
    };
}