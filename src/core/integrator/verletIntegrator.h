#pragma once

#include "integrator.h"
#include "../utils.h"

class VerletIntegrator : public IIntegrator<Utils::ParticleState>{
public:
    void integrate(Utils::ParticleState &state, float dt) override;
private:
    sf::Vector2f previousAcceleration_{0.0f, 0.0f};
};

