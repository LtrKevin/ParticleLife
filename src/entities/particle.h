#ifndef PARTICLELIFE_PARTICLE_H
#define PARTICLELIFE_PARTICLE_H
#include "SFML/Graphics/CircleShape.hpp"
#include "SFML/System/Vector2.hpp"

class Particle {
public:
    Particle(sf::Vector2f initialPosition, sf::Vector2f initialVelocity, float radius);

    sf::Vector2f getPosition() const;
    sf::Vector2f getVelocity() const;
    sf::CircleShape getShape() const;
    float getMass() const;

    void update(float dt);
    void applyForce(sf::Vector2f force);

private:
    sf::Vector2f position_;
    sf::Vector2f velocity_;
    sf::CircleShape shape_;
    float mass_;

    sf::Vector2f forceAccumulator_;
};

#endif //PARTICLELIFE_PARTICLE_H