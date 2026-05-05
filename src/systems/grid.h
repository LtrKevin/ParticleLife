#pragma once

#include <vector>
#include "../entities/particle.h"

class Grid {

public:
    Grid(int cellSize);

    void addParticle(Particle*);
    void computeCollision();
    void clear();

private:
    int rows_;
    int columns_;
    int cellSize_;
    std::vector<std::vector<Particle*>> cells_;
};