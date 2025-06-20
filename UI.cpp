#include "UI.h"
#include <graphics.h>
#include <conio.h>
#include <cstdio>
#include <windows.h>
#include "Game.h"

void UI::PutPng(int x, int y, IMAGE* im_show1, IMAGE* im_show2) {
    putimage(x, y, im_show1, SRCAND);
    putimage(x, y, im_show2, SRCPAINT);
}

void UI::showStartScreen(ResourceManager& res, Dino& dino, Background& bg) {
    int width = 1000, height = 400;
    int dino_width = 14, dino_height = 16;
    putimage(0, 0, &res.imBg);
    settextstyle(15, 0, _T("Consolas"));
    settextcolor(RGB(253, 138, 101));
    TCHAR Intro[30];
    wcscpy_s(Intro, _T("New Dinosaur"));
    int Intro_wid = width / 8 - textwidth(Intro) / 2;
    int Intro_hei = height / 8 - textheight(Intro);
    outtextxy(Intro_wid + 10, Intro_hei, Intro);
    PutPng(Intro_wid - dino_width * 2 + 10, Intro_hei - 1, &res.imLogo1, &res.imLogo2);
    Sleep(1500);

    cleardevice();
    putimage(0, 0, &res.imBg);
    putimage(bg.cloudX1, 10, &res.imCloud);
    putimage(bg.cloudX2, 15, &res.imCloud);
    PutPng(dino.x, dino.y, &res.imLogo1, &res.imLogo2);
    for (int i = 0; i < width / 4 * 46; i++)
        putimage(i * 46, (height - 46) / 4, &res.imGround);

    settextcolor(RGB(0, 0, 0));
    settextstyle(8, 0, _T("宋体"));
    wcscpy_s(Intro, _T("开始 -   空格"));
    Intro_wid = width / 8 - textwidth(Intro) / 2;
    Intro_hei = height / 8 - textheight(Intro) * 2;
    outtextxy(Intro_wid, Intro_hei, Intro);
    wcscpy_s(Intro, _T("教程 - press A"));
    Intro_hei = Intro_hei + textheight(Intro);
    outtextxy(Intro_wid, Intro_hei + 5, Intro);
    wcscpy_s(Intro, _T("退出 - press B"));
    outtextxy(Intro_wid, Intro_hei + textheight(Intro) + 10, Intro);
}

void UI::showTutorial(ResourceManager& res, Dino& dino, Background& bg, Game& game) {
    TCHAR tmp[30];
    int flag1 = 1, flag2 = 1, flag3 = 1, flag4 = 1, flag5 = 1;
    int width = 1000, height = 400;
    while (1) {
        dino.groundFlag = 2;
        if (GetAsyncKeyState(VK_UP) & 0x8000)
        {
            dino.vy = -5;
            dino.groundFlag -= 1;
            dino.skill1_flag = 0;
            flag1 = 0;
        }
        if (GetAsyncKeyState(VK_DOWN) & 0x8000)
        {
            dino.vy = 5;
            dino.vx = 0;
            flag2 = 0;
        }
        if (GetAsyncKeyState(VK_RIGHT) & 0x8000)
        {
            dino.vx = 1;
            flag3 = 0;
            if (dino.groundFlag >= 0 && dino.skill1_flag == 0)
                dino.x += 10, dino.skill1_flag = 1, flag5 = 0;
        }
        if (GetAsyncKeyState(VK_LEFT) & 0x8000)
        {
            dino.vx = -1;
            flag4 = 0;
        }
        if (GetAsyncKeyState(VK_SPACE) & 0x8000)
        {
            game.reset();
            return;
        }
        cleardevice();
        dino.update();
        bg.update();
        bg.loopCloud();
        BeginBatchDraw();
        drawGame(res, dino, Obstacle(1), Obstacle(2), bg, 0);

        settextstyle(7, 0, _T("宋体"));
        if (flag1 == 1)	wcscpy_s(tmp, _T("方向键上  控制跳跃"));
        else if (flag2 == 1)	wcscpy_s(tmp, _T("下  控制下落,并让水平速度为0"));
        else if (flag3 == 1)	wcscpy_s(tmp, _T("方向键右  控制水平向右加速,下可停止"));
        else if (flag4 == 1)  {
            wcscpy_s(tmp, _T("方向键左  控制水平向左加速"));
            dino.skill1 = 1;
        }
        else if (flag5 == 1)	wcscpy_s(tmp, _T("方向键右  技能:空中可瞬移"));
        else wcscpy_s(tmp, _T("空格正式开始游戏"));

        outtextxy(width / 8 - textwidth(tmp) / 2, height / 8, tmp);
        EndBatchDraw();
        Sleep(24);
    }
}

void UI::showGameOver(ResourceManager& res, int score) {
    BeginBatchDraw();
    int width = 1000, height = 400;
    TCHAR tmp[20];
    swprintf_s(tmp, _T("Score:%d"), score);
    settextstyle(14, 0, _T("宋体"));
    outtextxy(width / 8 - textwidth(tmp) / 2, height / 8 - textheight(tmp), tmp);
    settextstyle(7, 0, _T("宋体"));
    wcscpy_s(tmp, _T("空格-重新开始游戏"));
    outtextxy(width / 8 - textwidth(tmp) / 2, height / 8 + 0.5 * textheight(tmp), tmp);

    settextstyle(15, 0, _T("Consolas"));
    wcscpy_s(tmp, _T("made by zbwer"));
    settextstyle(7, 0, _T("宋体"));
    outtextxy(width / 8 - textwidth(tmp) / 2, height / 8 + 2 * textheight(tmp), tmp);
    settextstyle(15, 0, _T("Consolas"));
    EndBatchDraw();
    while (1) {
		if (GetAsyncKeyState(VK_SPACE) & 0x8000) break;
        if (GetAsyncKeyState('B') & 0x8000 || GetAsyncKeyState('b') & 0x8000) exit(0);
    }
}

void UI::drawGame(ResourceManager& res, Dino& dino, const Obstacle& obs1, const Obstacle& obs2, Background& bg, int score) {
    int width = 1000, bottom = (400 - 46) / 4;
    putimage(0, 0, &res.imBg);
    putimage(bg.cloudX1, 10, &res.imCloud);
    putimage(bg.cloudX2, 10 + 5, &res.imCloud);

    // 恐龙动画
    if (dino.ani <= 3) PutPng(dino.x, dino.y, &res.imDino21, &res.imDino22);
    else if (dino.ani > 3 && dino.ani <= 5) PutPng(dino.x, dino.y, &res.imDino31, &res.imDino32);
    else PutPng(dino.x, dino.y, &res.imDino41, &res.imDino42);

    for (int i = 0; i < width / 46; i++)
        putimage(i * 46, bottom, &res.imGround);

    putimage(obs1.x, obs1.y, &res.imTree);
    putimage(obs2.x, obs2.y, &res.imTree);

    TCHAR s[20];
    swprintf_s(s, _T("%d"), score);
    settextstyle(14, 0, _T("Consolas"));
    outtextxy(50 / 4, 30 / 4, s);
}