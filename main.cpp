#include "Game.h"

int main() {
    initgraph(1000, 400);
    setaspectratio(4.0, 4.0);//ʹ����ͼ������Сһ��
    setbkcolor(RGB(177, 236, 240));//ʹ����������ʾ
    Game game;
    game.run();
    return 0;
}