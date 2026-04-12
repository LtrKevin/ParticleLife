#include <iostream>
#include <random>
#include <SFML/Graphics.hpp>

#include "cmake-build-debug/_deps/sfml-src/src/SFML/Window/InputImpl.hpp"
#include "src/entities/particle.h"
#include "src/core/constants.h"
#include "src/core/physics.h"

int main() {
    std::vector<std::unique_ptr<Particle>> particles;
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(-200, 200);

    sf::RenderWindow window(sf::VideoMode({config::WINDOW_WIDTH, config::WINDOW_HEIGHT}), config::WINDOW_TITLE);
    sf::Clock clock;

    clock.start();

    while (window.isOpen()) {
        while (const std::optional event = window.pollEvent()) {

            if (event->is<sf::Event::Closed>()) window.close();

            if (event->is<sf::Event::KeyPressed>()) {
                auto& particle = particles.emplace_back(std::make_unique<Particle>(sf::Vector2f(
                    sf::Mouse::getPosition(window)),
                    sf::Vector2f(dis(gen), dis(gen)),
                    10.0));
            }
        }

        const float dt = clock.restart().asSeconds();

        window.clear();

        if (!particles.empty()) {
            for (int i = 0; i < particles.size() - 1; i++) {
                for (int j = i + 1; j < particles.size() - 1; j++) {
                    const auto& particle_i = particles.at(i);
                    const auto& particle_j = particles.at(j);

                    const float distanceSquared = (particle_i->getPosition() - particle_j->getPosition()).lengthSquared();
                    const float particleIRadiusSquared = particle_i->getShape().getRadius() * particle_i->getShape().getRadius();
                    const float particleJRadiusSquared = particle_j->getShape().getRadius() * particle_j->getShape().getRadius();

                    if (distanceSquared <= particleIRadiusSquared * particleJRadiusSquared) {
                        //TODO: Implement collision
                    }
                }
            }
        }

        if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
            for (const auto& particle : particles) {
                particle->applyForce(forces::computeMouseAttraction(
                    particle->getMass(),
                    window.mapPixelToCoords(sf::Mouse::getPosition(window)) - particle->getPosition()
                ));
            }
        }

        for (const auto& particle : particles) {
            window.draw(particle->getShape());
            particle->applyForce(forces::computeGravity(particle->getMass()));
            particle->applyForce(forces::computeAirFriction(particle->getVelocity()));
            particle->update(dt);
        }

        window.display();
    }

    return 0;
}
