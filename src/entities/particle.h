#ifndef PARTICLELIFE_PARTICLE_H
#define PARTICLELIFE_PARTICLE_H
#include "SFML/Graphics/CircleShape.hpp"
#include "SFML/System/Vector2.hpp"


class particle {
public:
    particle(sf::Vector2f initialPosition, sf::Vector2f initialVelocity, float radius);

    sf::Vector2f getPosition() const;
    sf::Vector2f getVelocity() const;
    sf::CircleShape getShape() const;

    void update(float dt);

private:
    sf::Vector2f position_;
    sf::Vector2f velocity_;
    sf::CircleShape shape_;
};

#endif //PARTICLELIFE_PARTICLE_H