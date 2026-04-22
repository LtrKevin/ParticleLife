#include "ui.h"
#include "imgui.h"
#include "imgui-SFML.h"
#include "../core/constants.h"
#include <iostream>

UIManager::UIManager(sf::RenderWindow &window) {
    ImGui::SFML::Init(window);
}

UIManager::~UIManager() {
    ImGui::SFML::Shutdown();
}

void UIManager::render(sf::RenderWindow &window) {
    ImGui::SFML::Render(window);
}

void UIManager::processEvents(const sf::Window &window, const sf::Event &event) {
    ImGui::SFML::ProcessEvent(window, event);
}

void UIManager::update(const sf::Time dt, std::vector<std::unique_ptr<Particle> > &particles, sf::RenderWindow &window) {
    ImGui::SFML::Update(window, dt);
    ImGui::Begin("Menu");
    ImGui::SliderInt("Gravité", &config::currentPlanet, 0, config::Planet::count - 1, config::gravityPresets[config::currentPlanet].name);
    if (ImGui::Button("Supprimer les particules")) {
        std::cout << "Suppression des particules ..." << std::endl;
        particles.clear();
    }
    ImGui::End();
}
