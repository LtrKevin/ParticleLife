#include <random>
#include <SFML/Graphics.hpp>

#include "src/entities/particle.h"
#include "src/core/constants.h"
#include "src/core/physics.h"
#include "src/systems/grid.h"
#include "src/systems/ui.h"
#include "imgui-SFML.h"

int main() {
    std::vector<std::unique_ptr<Particle>> particles;
    const auto grid = std::make_unique<Grid>(100);
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(-200, 200);
    std::uniform_real_distribution<> radiusDis(5.0, 20.0);

    sf::RenderWindow window(sf::VideoMode({config::WINDOW_WIDTH, config::WINDOW_HEIGHT}), config::WINDOW_TITLE);
    sf::Clock clock;

    clock.start();

    UIManager uiManager(window);

    while (window.isOpen()) {
        while (const std::optional event = window.pollEvent()) {
            uiManager.processEvents(window, *event);

            if (event->is<sf::Event::Closed>()) window.close();

            if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>()) {
                if (keyPressed->code == sf::Keyboard::Key::Space) {
                    auto& particle = particles.emplace_back(std::make_unique<Particle>(sf::Vector2f(
                        sf::Mouse::getPosition(window)),
                        sf::Vector2f(dis(gen), dis(gen)),
                        radiusDis(gen)
                    ));
                }
            }
        }

        const sf::Time frameTime = clock.restart();
        const float dt = frameTime.asSeconds();

        window.clear();

        if (!particles.empty()) {
            grid->clear();
            for (const auto& particle : particles) {
                grid->addParticle(particle.get());
            }
            grid->computeCollision();
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
            particle->applyForce(forces::computeGravity(particle->getMass()));
            particle->applyForce(forces::computeAirFriction(particle->getVelocity()));

            particle->update(dt);

            window.draw(particle->getShape());
        }

        uiManager.update(frameTime, particles, window);
        uiManager.render(window);

        window.display();
    }

    return 0;
}
