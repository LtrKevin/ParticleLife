#include "particle.h"
#include <cmath>
#include "../core/constants.h"

Particle::Particle(
    const sf::Vector2f initialPosition,
    const sf::Vector2f initialVelocity,
    const float radius)
: position_(initialPosition),
  velocity_(initialVelocity)
{
    shape_ = sf::CircleShape(radius);
    shape_.setFillColor(sf::Color::White);
    shape_.setOrigin(sf::Vector2f(radius, radius));

    mass_ = radius*radius;
    forceAccumulator_ = {0, 0};
}

void Particle::applyForce(const sf::Vector2f force) {
    forceAccumulator_ += force;
}

void Particle::update(const float dt) {
    acceleration_ = forceAccumulator_ / mass_;

    auto state = getState();
    integrator_->integrate(state, dt);
    setState(state);

    const float MIN_POSITION = 0 + shape_.getRadius();
    const float MAX_X_POSITION = config::WINDOW_WIDTH - shape_.getRadius();
    const float MAX_Y_POSITION = config::WINDOW_HEIGHT - shape_.getRadius();

    if (position_.x >= MAX_X_POSITION || position_.x <= MIN_POSITION) {
        velocity_.x = -velocity_.x * config::RESTITUTION;

        position_.x = position_.x < MIN_POSITION ? MIN_POSITION : MAX_X_POSITION;
    }

    if (position_.y >= MAX_Y_POSITION || position_.y <= MIN_POSITION) {
        velocity_.y = -velocity_.y * config::RESTITUTION;
        velocity_.x > 0 ? velocity_.x -= config::SLIDE_FRICTION*dt: velocity_.x += config::SLIDE_FRICTION*dt;

        position_.y = position_.y < MIN_POSITION ? MIN_POSITION : MAX_Y_POSITION;
    }

    if (std::abs(velocity_.x) < config::VELOCITY_X_THRESHOLD) velocity_.x = 0.0f;

    shape_.setPosition(position_);
    forceAccumulator_ = {0, 0};
}

void Particle::setVelocity(const sf::Vector2f velocity) {
    velocity_ = velocity;
}

sf::Vector2f Particle::getPosition() const {
    return position_;
}

sf::Vector2f Particle::getVelocity() const {
    return velocity_;
}

const sf::CircleShape& Particle::getShape() const {
    return shape_;
}

float Particle::getMass() const {
    return mass_;
}

Utils::ParticleState Particle::getState() const {
    return Utils::ParticleState{position_, velocity_, acceleration_};
}

void Particle::setState(const Utils::ParticleState &state) {
    acceleration_ = state.acceleration;
    velocity_ = state.velocity;
    position_ = state.position;
}

void Particle::setIntegrator(std::unique_ptr<IIntegrator<Utils::ParticleState>> integrator) {
    integrator_ = std::move(integrator);
}
