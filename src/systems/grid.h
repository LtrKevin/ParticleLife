#ifndef PARTICLELIFE_GRID_H
#define PARTICLELIFE_GRID_H

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


#endif //PARTICLELIFE_GRID_H