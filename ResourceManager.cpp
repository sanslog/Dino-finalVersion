#include "ResourceManager.h"

void ResourceManager::loadResources() {
    loadimage(&imBg, _T("./res/Background.png"));
    loadimage(&imLogo1, _T("./res/logo1.png"));
    loadimage(&imLogo2, _T("./res/logo2.png"));
    loadimage(&imDino21, _T("./res/move2_1.png"));
    loadimage(&imDino22, _T("./res/move2_2.png"));
    loadimage(&imDino31, _T("./res/move3_1.png"));
    loadimage(&imDino32, _T("./res/move3_2.png"));
    loadimage(&imDino41, _T("./res/move4_1.png"));
    loadimage(&imDino42, _T("./res/move4_2.png"));
    loadimage(&imFly1, _T("./res/fly_1.png"));
    loadimage(&imFly2, _T("./res/fly_2.png"));
    loadimage(&imGround, _T("./res/1.png"));
    loadimage(&imTree, _T("./res/Tree.png"));
    loadimage(&imCloud, _T("./res/Cloud.png"));
}