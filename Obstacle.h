#pragma once

class Obstacle {
public:
    Obstacle(int id);
    void update();
    void reset(double otherX);
    double x, y;
    int width, height;
    double vx;
    int id;
};
