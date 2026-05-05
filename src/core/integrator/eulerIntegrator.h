#pragma once

#include "integrator.h"
#include "../utils.h"

class EulerIntegrator : public IIntegrator<Utils::ParticleState> {
public:
    void integrate(Utils::ParticleState& state, float dt) override;
};