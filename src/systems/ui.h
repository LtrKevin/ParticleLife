#ifndef PARTICLELIFE_UI_H
#define PARTICLELIFE_UI_H

#include <SFML/Graphics.hpp>
#include <SFML/Window/Event.hpp>
#include <vector>
#include <memory>
#include "../entities/particle.h"
#include "grid.h"

class UIManager {
public:
    UIManager(sf::RenderWindow& window);
    ~UIManager();

    void update(sf::Time dt, std::vector<std::unique_ptr<Particle>>& particles, sf::RenderWindow& window);
    void processEvents(const sf::Window& window, const sf::Event& event);
    void render(sf::RenderWindow& window);
};

#endif //PARTICLELIFE_UI_H