#include "Game.h"
#include <conio.h>
#include <ctime>
#include<Windows.h>

Game::Game()
    : dino(), obstacle1(1), obstacle2(2), background(), resourceManager(), ui(),
    score(0), tmpscore1(1), tmpscore2(2), running(true), inTutorial(false) {
    srand((int)time(0));
    resourceManager.loadResources();
    reset();
}

void Game::run() {
    ui.showStartScreen(resourceManager, dino, background);
	// �ȴ��û����¿ո����ʼ��Ϸ
    while (1) {
        if (GetAsyncKeyState(VK_SPACE) & 0x8000) break;
        if (GetAsyncKeyState('A') & 0x8000)
        {
            inTutorial = true;
            ui.showTutorial(resourceManager, dino, background, *this);
            break;
        }
        if (GetAsyncKeyState('B') & 0x8000)
        {
            running = false;
            break;
        }
        Sleep(10);
    }
    while (running) {
        BeginBatchDraw();//�����˸����
        processInput();
        update();
        render();
		EndBatchDraw();//�����˸����
        Sleep(24);
    }
}

void Game::processInput() {
        if (GetAsyncKeyState(VK_SPACE) & 0x8000)
            reset();
        else if (GetAsyncKeyState('A') & 0x8000)
        {
            inTutorial = true;
            ui.showTutorial(resourceManager, dino, background, *this);
        }
        else if (GetAsyncKeyState('B') & 0x8000) {
            running = false;
        }
        // ����������ƿ���
        else if (GetAsyncKeyState(VK_UP) & 0x8000) {
            dino.handleInput(72, score, tmpscore1); // 72 = �Ϸ����
        }
        else if (GetAsyncKeyState(VK_DOWN) & 0x8000) {
            dino.handleInput(80, score, tmpscore1); // 80 = �·����
        }
        else if (GetAsyncKeyState(VK_LEFT) & 0x8000) {
            dino.handleInput(75, score, tmpscore1); // 75 = �����
        }
        else if (GetAsyncKeyState(VK_RIGHT) & 0x8000) {
            dino.handleInput(77, score, tmpscore1); // 77 = �ҷ����
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

void Game::reset() {
    dino.reset();
    obstacle1.reset(0);
    obstacle2.reset(obstacle1.x);
    background.reset();
    score = 0;
}
