#include "Game.h"

int main() {
    initgraph(1000, 400);
    setaspectratio(4.0, 4.0);//使背景图与界面大小一致
    setbkcolor(RGB(177, 236, 240));//使文字正常显示
    Game game;
    game.run();
    return 0;
}