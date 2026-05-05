#include "verletIntegrator.h"

void VerletIntegrator::integrate(Utils::ParticleState &state, float dt) {
    state.position = state.position + state.velocity * dt + 0.5f * previousAcceleration_ * dt * dt;
    state.velocity = state.velocity + (state.acceleration + previousAcceleration_) * dt * 0.5f;
    previousAcceleration_ = state.acceleration;
}
