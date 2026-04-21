#include <iostream>
#include <random>
#include <SFML/Graphics.hpp>

#include "cmake-build-debug/_deps/sfml-src/src/SFML/Window/InputImpl.hpp"
#include "src/entities/particle.h"
#include "src/core/constants.h"
#include "src/core/physics.h"
#include "src/systems/grid.h"
#include "imgui-SFML.h"
#include "imgui.h"

int main() {
    std::vector<std::unique_ptr<Particle>> particles;
    const auto grid = std::make_unique<Grid>(100);
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(-200, 200);

    sf::RenderWindow window(sf::VideoMode({config::WINDOW_WIDTH, config::WINDOW_HEIGHT}), config::WINDOW_TITLE);
    if (!ImGui::SFML::Init(window))
        return -1;
    sf::Clock clock;

    clock.start();

    while (window.isOpen()) {
        while (const std::optional event = window.pollEvent()) {

            ImGui::SFML::ProcessEvent(window, *event);

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
            window.draw(particle->getShape());

            if (config::earthMode) {
                particle->applyForce(forces::computeGravity(particle->getMass()));
                particle->applyForce(forces::computeAirFriction(particle->getVelocity()));
            }

            particle->update(dt);
        }

        ImGui::SFML::Update(window, frameTime);

        ImGui::Begin("Menu");
        ImGui::Button("Look at this pretty button");
        ImGui::End();

        ImGui::SFML::Render(window);
        window.display();
    }

    ImGui::SFML::Shutdown();

    return 0;
}
