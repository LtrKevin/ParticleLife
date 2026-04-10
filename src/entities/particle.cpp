#include "particle.h"
#include "../core/constants.h"

particle::particle(
    const sf::Vector2f initialPosition,
    const sf::Vector2f initialVelocity,
    const float radius)
: position_(initialPosition),
  velocity_(initialVelocity)
{
    shape_ = sf::CircleShape(radius);
    shape_.setFillColor(sf::Color::White);
}

sf::Vector2f particle::getPosition() const {
    return position_;
}

sf::Vector2f particle::getVelocity() const {
    return velocity_;
}

sf::CircleShape particle::getShape() const {
    return shape_;
}

void particle::update(const float dt) {
    const auto pos = position_ + velocity_ * dt;

    if (pos.x > config::WINDOW_WIDTH - shape_.getRadius() * 2 || pos.x < 0) {
        velocity_.x = -velocity_.x;
    }

    if (pos.y > config::WINDOW_HEIGHT - shape_.getRadius() * 2 || pos.y < 0) {
        velocity_.y = -velocity_.y;
    }

    position_ = pos;
    shape_.setPosition(pos);
}
