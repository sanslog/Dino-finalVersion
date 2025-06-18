#pragma once
#include "ResourceManager.h"
#include "Dino.h"
#include "Obstacle.h"
#include "Background.h"
#include <tchar.h>

class Game;

class UI {
public:
    void showStartScreen(ResourceManager&, Dino&, Background&);
    void showTutorial(ResourceManager&, Dino&, Background&, Game&);
    void showGameOver(ResourceManager&, int score);
    void drawGame(ResourceManager&, Dino&, const Obstacle&, const Obstacle&, Background&, int score);
private:
    void PutPng(int x, int y, IMAGE* im_show1, IMAGE* im_show2);
};