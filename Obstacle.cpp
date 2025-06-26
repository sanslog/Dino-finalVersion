#include "Obstacle.h"
#include <cstdlib>

Obstacle::Obstacle(int id) : id(id) { reset(0); }

void Obstacle::reset(double otherX) {
    width = 16; height = 21;
    double bottom = (400 - 46) / 4;
    if (id == 1) {
        x = 1000 / 4 - 25;
    }
    else {
        x = 1000 / 4 - 25 + 100;
    }
    if (otherX > 0 && id == 2) {
        x = otherX + 100 + (rand() % 5) * 16;
    }
    y = bottom - height;
    vx = -2.5;
}

void Obstacle::update() {
    x += vx;
}