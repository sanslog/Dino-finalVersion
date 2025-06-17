#pragma once
#include "Dino.h"
#include "Obstacle.h"
#include "Background.h"
#include "ResourceManager.h"
#include "UI.h"

class Game {
public:
    Game();
    void run();

private:
    void processInput();
    void update();
    void render();
    void reset();

    Dino dino;
    Obstacle obstacle1, obstacle2;
    Background background;
    ResourceManager resourceManager;
    UI ui;

    int score;
    int tmpscore1, tmpscore2;
    bool running;
    bool inTutorial;
};
