#include "grid.h"

#include <cmath>
#include "../core/constants.h"
#include "../core/physics.h"

Grid::Grid(const int cellSize, const int numThreads) : cellSize_(cellSize), threadPool_(numThreads){
    rows_ = static_cast<int>(floor(config::WINDOW_HEIGHT/cellSize_));
    columns_ = static_cast<int>(floor(config::WINDOW_WIDTH/cellSize_));

    cells_.resize(rows_*columns_);
}

void Grid::computeCollision() {
    for (int row = 0; row < rows_; row++) {
        threadPool_.submit([this, row] {
        for (int column = 0; column < columns_; column++) {
        const int i = row * columns_ + column;
        std::vector<Particle*> neighbours;

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

        for (int pi = 0; pi < neighbours.size(); pi++) {
            for (int pj = pi + 1; pj < neighbours.size(); pj++) {
                const auto& particle_i = neighbours.at(pi);
                const auto& particle_j = neighbours.at(pj);

                const float distanceSquared = (particle_i->getPosition() - particle_j->getPosition()).lengthSquared();
                const float particleIJRadiusSquared = (particle_i->getShape().getRadius() + particle_j->getShape().getRadius()) * (particle_i->getShape().getRadius() + particle_j->getShape().getRadius());

                if (distanceSquared <= particleIJRadiusSquared) {
                    if (distanceSquared == 0) continue;

                    const float distance = std::sqrt(distanceSquared);
                    const float radius_i = particle_i->getShape().getRadius();
                    const float radius_j = particle_j->getShape().getRadius();
                    const float overlap = (radius_i + radius_j) - distance;

                    const sf::Vector2f normal = (particle_i->getPosition() - particle_j->getPosition()) / distance;
                    const float totalMass = particle_i->getMass() + particle_j->getMass();

                    particle_i->setPosition(particle_i->getPosition() + normal * overlap * (particle_j->getMass() / totalMass));
                    particle_j->setPosition(particle_j->getPosition() - normal * overlap * (particle_i->getMass() / totalMass));

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
        } // fin du for column
        }); // fin du submit
    }
    threadPool_.wait();
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
