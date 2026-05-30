#pragma once

#include <vector>
#include "../entities/particle.h"
#include "../core/threadPool.h"

class Grid {

public:
    Grid(int cellSize, int numThreads = 4);

    void addParticle(Particle*);
    void computeCollision();
    void clear();

private:
    int rows_;
    int columns_;
    int cellSize_;
    std::vector<std::vector<Particle*>> cells_;
    ThreadPool threadPool_;
};