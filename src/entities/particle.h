#pragma once

#include <memory>

#include "SFML/Graphics/CircleShape.hpp"
#include "SFML/System/Vector2.hpp"
#include "../core/utils.h"
#include "../core/integrator/integrator.h"

class Particle {
public:
    Particle(sf::Vector2f initialPosition, sf::Vector2f initialVelocity, float radius);

    sf::Vector2f getPosition() const;
    sf::Vector2f getVelocity() const;
    const sf::CircleShape& getShape() const;
    float getMass() const;

    void setVelocity(sf::Vector2f velocity);
    void setIntegrator(std::unique_ptr<IIntegrator<Utils::ParticleState>> integrator);

    void update(float dt);
    void applyForce(sf::Vector2f force);

private:
    sf::Vector2f position_;
    sf::Vector2f velocity_;
    sf::Vector2f acceleration_;
    sf::CircleShape shape_;
    float mass_;
    std::unique_ptr<IIntegrator<Utils::ParticleState>> integrator_;
    sf::Vector2f forceAccumulator_;

    Utils::ParticleState getState() const;
    void setState(const Utils::ParticleState& state);
};