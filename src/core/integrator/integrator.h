#pragma once

template<typename State>
class IIntegrator {
public:
    virtual void integrate(State& state, float dt) = 0;
    virtual ~IIntegrator() = default;
};
