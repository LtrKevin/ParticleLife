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

            if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>()) {
                if (keyPressed->code == sf::Keyboard::Key::G) {
                    config::earthMode = !config::earthMode;
                    std::cout << "Mode terre : " << config::earthMode << std::endl;
                } else if (keyPressed->code == sf::Keyboard::Key::R) {
                    std::cout << "Suppression des particules ..." << std::endl;
                    particles.clear();
                } else if (keyPressed->code == sf::Keyboard::Key::Space) {
                    auto& particle = particles.emplace_back(std::make_unique<Particle>(sf::Vector2f(
                        sf::Mouse::getPosition(window)),
                        sf::Vector2f(dis(gen), dis(gen)),
                        12.0
                    ));
                }
            }
        }

        const float dt = clock.restart().asSeconds();

        window.clear();

        if (!particles.empty()) {
            for (int i = 0; i < particles.size(); i++) {
                for (int j = i + 1; j < particles.size(); j++) {
                    const auto& particle_i = particles.at(i);
                    const auto& particle_j = particles.at(j);

                    const float distanceSquared = (particle_i->getPosition() - particle_j->getPosition()).lengthSquared();
                    const float particleIJRadiusSquared = (particle_i->getShape().getRadius() + particle_j->getShape().getRadius()) * (particle_i->getShape().getRadius() + particle_j->getShape().getRadius());

                    if (distanceSquared <= particleIJRadiusSquared) {
                        if (distanceSquared == 0) continue;

                        const auto collisionSpeed = forces::computeCollisionImpulsion(
                            particle_i->getPosition() - particle_j->getPosition(),
                            particle_i->getMass(),
                            particle_i->getVelocity(),
                            particle_j->getMass(),
                            particle_j->getVelocity()
                        );

                        particle_i->setVelocity(particle_i->getVelocity() + collisionSpeed/particle_i->getMass());
                        particle_j->setVelocity(particle_j->getVelocity() - collisionSpeed/particle_j->getMass());
                    }
                }
            }
        }

        if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
            for (const auto& particle : particles) {
                particle->applyForce(forces::computeMouseAttraction(
                    window.mapPixelToCoords(sf::Mouse::getPosition(window)) - particle->getPosition(),
                    particle->getVelocity(),
                    particle->getMass()
                ));
            }
        }

        for (const auto& particle : particles) {
            window.draw(particle->getShape());

            if (config::earthMode) {
                particle->applyForce(forces::computeGravity(particle->getMass()));
                particle->applyForce(forces::computeAirFriction(particle->getVelocity()));
            }

            particle->update(dt);
        }

        window.display();
    }

    return 0;
}
