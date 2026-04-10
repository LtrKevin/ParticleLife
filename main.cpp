#include <iostream>
#include <random>
#include <SFML/Graphics.hpp>

#include "cmake-build-debug/_deps/sfml-src/src/SFML/Window/InputImpl.hpp"
#include "src/entities/particle.h"
#include "src/core/constants.h"

int main() {
    std::vector<std::unique_ptr<particle>> particles;
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(-200, 200);

    sf::RenderWindow window(sf::VideoMode({config::WINDOW_WIDTH, config::WINDOW_HEIGHT}), config::WINDOW_TITLE);
    sf::Clock clock;

    clock.start();

    while (window.isOpen()) {
        while (const std::optional event = window.pollEvent()) {

            if (event->is<sf::Event::Closed>()) window.close();

            if (event->is<sf::Event::MouseButtonPressed>()) {
                particles.push_back(std::make_unique<particle>(sf::Vector2f(
                    sf::Mouse::getPosition(window)),
                    sf::Vector2f(dis(gen), dis(gen)),
                    10.0));
            }
        }

        const float dt = clock.restart().asSeconds();

        window.clear();

        for (const auto& p : particles) {
            window.draw(p->getShape());
            p->update(dt);
        }

        window.display();
    }

    return 0;
}
