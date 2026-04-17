#include "grid.h"

#include <cmath>
#include "../core/constants.h"
#include "../core/physics.h"

Grid::Grid(const int cellSize) : cellSize_(cellSize){
    rows_ = static_cast<int>(floor(config::WINDOW_HEIGHT/cellSize_));
    columns_ = static_cast<int>(floor(config::WINDOW_WIDTH/cellSize_));

    cells_.resize(rows_*columns_);
}

void Grid::computeCollision() {
    for (int i = 0; i < rows_ * columns_; i++) {
        std::vector<Particle*> neighbours; // BOTTOM_LEFT, BOTTOM, BOTTOM_RIGHT, RIGHT

        const int column = i % columns_;
        const int row = (i - column) / columns_;

        if (row < rows_ - 1) {
            neighbours.insert(neighbours.end(), cells_[i + columns_].begin(), cells_[i + columns_].end());

            if (column < columns_ - 1) {
                neighbours.insert(neighbours.end(), cells_[i + 1].begin(), cells_[i + 1].end());
                neighbours.insert(neighbours.end(), cells_[i + columns_ + 1].begin(), cells_[i + columns_ + 1].end());
            }

            if (column > 0) {
                neighbours.insert(neighbours.end(), cells_[i + columns_ - 1].begin(), cells_[i + columns_ - 1].end());
            }
        } else {
            if (column < columns_ - 1) {
                neighbours.insert(neighbours.end(), cells_[i + 1].begin(), cells_[i + 1].end());
            }
        }

        neighbours.insert(neighbours.end(), cells_[i].begin(), cells_[i].end());

        for (int i = 0; i < neighbours.size(); i++) {
            for (int j = i + 1; j < neighbours.size(); j++) {
                const auto& particle_i = neighbours.at(i);
                const auto& particle_j = neighbours.at(j);

                const float distanceSquared = (particle_i->getPosition() - particle_j->getPosition()).lengthSquared();
                const float particleIJRadiusSquared = (particle_i->getShape().getRadius() + particle_j->getShape().getRadius()) * (particle_i->getShape().getRadius() + particle_j->getShape().getRadius());

                if (distanceSquared <= particleIJRadiusSquared) {
                    if (distanceSquared == 0) continue;

                    const auto collisionSpeed = forces::computeCollisionImpulsion(
                        particle_i->getPosition() - particle_j->getPosition(),
                        particle_i->getMass(),
                        particle_i->getVelocity(),
                        particle_j->getMass(),
                        particle_j->getVelocity()
                    );

                    particle_i->setVelocity(particle_i->getVelocity() + collisionSpeed/particle_i->getMass());
                    particle_j->setVelocity(particle_j->getVelocity() - collisionSpeed/particle_j->getMass());
                }
            }
        }

        neighbours.clear();
    }
}

void Grid::addParticle(Particle* p){
    int row = static_cast<int>(p->getPosition().y / cellSize_);
    int column = static_cast<int>(p->getPosition().x / cellSize_);

    if (row < 0) row = 0;
    if (column < 0 ) column = 0;
    if (row >= rows_) row = rows_ - 1;
    if (column >= columns_) column = columns_ - 1;

    const int index = column + row * columns_;

    cells_[index].push_back(p);
}

void Grid::clear(){
    for (auto& cell : cells_) {
        cell.clear();
    }
}
