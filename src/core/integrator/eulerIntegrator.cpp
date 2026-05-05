#include "eulerIntegrator.h"

void EulerIntegrator::integrate(Utils::ParticleState& state, const float dt) {
    state.velocity = state.velocity + state.acceleration * dt;
    state.position = state.position + state.velocity * dt;
}
