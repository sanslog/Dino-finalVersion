#include "Dino.h"

Dino::Dino() { reset(); }

void Dino::reset() {
    width = 14; height = 16;
    x = 1000 / 20;
    y = (400 - 46) / 4 - height;
    vx = 0; vy = 0;
    gravity = 0.25;
    groundFlag = 1;
    ani = 0;
    skill1 = 0; skill2 = 0;
    skill1_flag = 1;
}

void Dino::update() {
    vy += gravity;
    y += vy;
    x += vx;
    ani = (ani + 1) % 9;//����֡ѭ������
    // ����ж�
    double bottom = (400 - 46) / 4;
    if (y >= bottom - height) {
        vy = 0;
        y = bottom - height;
        groundFlag = 1;
        skill1_flag = 1;
        if (skill2)
            groundFlag = 2;
    }
    else {
        ani = 3;
    }

    // �߽��ж�����ֹ����Խ��
    if (x < 0) x = 0;
    if (x >= 235) x = 235;
    if (y < 0) y = 0;
    //if (x < 0) x = 0;
    //if (x > 1000 - width) x = 1000 - width;
}

void Dino::handleInput(char input, int score, int tmpscore1) {
    // �����
    if ((int)input == 72 && groundFlag >= 1) { // ��
        vy = -5;
        groundFlag -= 1;
        if (groundFlag < 0) groundFlag = 0;
        skill1_flag = 0;
    }
    if ((int)input == 80) { // ��
        vy = 5;
        vx = 0;
    }
    if ((int)input == 77) { // ��
        vx = 1;
        if (score >= tmpscore1 && groundFlag >= 0 && skill1_flag == 0) {
            x += 10;//ʹ�ü��ܵĺ��Ĵ��롪����10
            skill1_flag = 1;
        }
    }
    if ((int)input == 75) { // ��
        vx = -1;
    }
}

bool Dino::checkCollision(const Obstacle& obs) const {
    return (obs.x < x + width && obs.y + 1 < y + height && x < obs.x + obs.width);
}

void Dino::checkSkill(int score, int tmpscore1, int tmpscore2) {
    if (score >= tmpscore1) skill1 = true;
    if (score >= tmpscore2) skill2 = true;
}