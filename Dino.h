#pragma once
#include "ResourceManager.h"
#include "Obstacle.h"

class Dino {
public:
    Dino();
    void update();
    void handleInput(char input, int score, int tmpscore1);
    void reset();
    bool checkCollision(const Obstacle& obs) const;
    void checkSkill(int score, int tmpscore1, int tmpscore2);

    double x, y, vx, vy;
    int width, height;
    int groundFlag;
    int ani;
    bool skill1, skill2;
    int skill1_flag;

    double gravity;
};
