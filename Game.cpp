#include "Game.h"
#include <conio.h>
#include <ctime>

Game::Game()
    : dino(), obstacle1(1), obstacle2(2), background(), resourceManager(), ui(),
    score(0), tmpscore1(10), tmpscore2(25), running(true), inTutorial(false) {
    srand((int)time(0));
    resourceManager.loadResources();
    reset();
}

void Game::run() {//��Ϸ��ʼͨ��
    ui.showStartScreen(resourceManager, dino, background);
    while (running) {
        processInput();
        update();
        render();
        Sleep(24);
    }
}

void Game::processInput() {
    if (_kbhit()) {
        char input = _getch();
        if (input == ' ') {
            reset();
        }
        else if (input == 'A' || input == 'a') {
            inTutorial = true;
            ui.showTutorial(resourceManager, dino, background, *this);
        }
        else if (input == 'B' || input == 'b') {
            running = false;
        }
        else if ((int)input == -32) {
            input = _getch();
            dino.handleInput(input, score, tmpscore1);
        }
    }
}

void Game::update() {
    dino.update();
    obstacle1.update();
    obstacle2.update();
    background.update();

    // �ϰ���ѭ��
    if (obstacle1.x <= 0) {
        obstacle1.reset(obstacle2.x);
        score++;
        if (score >= tmpscore1) {
            obstacle1.vx -= 0.1;
            obstacle2.vx -= 0.1;
        }
    }
    if (obstacle2.x <= 0) {
        obstacle2.reset(obstacle1.x);
        score++;
    }

    // �ƶ�ѭ��
    background.loopCloud();

    // �����ж�
    dino.checkSkill(score, tmpscore1, tmpscore2);

    // ��ײ�ж�
    if (dino.checkCollision(obstacle1) || dino.checkCollision(obstacle2)) {
        ui.showGameOver(resourceManager, score);
        reset();
    }
}

void Game::render() {
    ui.drawGame(resourceManager, dino, obstacle1, obstacle2, background, score);
}

void Game::reset() {//������Ϸ
    dino.reset();
    obstacle1.reset(0);
    obstacle2.reset(obstacle1.x);
    background.reset();
    score = 0;
}
