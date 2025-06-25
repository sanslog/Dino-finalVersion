#include "Background.h"

Background::Background() { reset(); }

void Background::reset() {
    cloudX1 = 220;
    cloudX2 = 220 + 70;
}

void Background::update() {
    cloudX1 -= 0.5;
    cloudX2 -= 0.5;
}

void Background::loopCloud() {
    if (cloudX1 <= 0)   cloudX1 = 1000 / 4 + 27;
    if (cloudX2 <= 0)   cloudX2 = 1000 / 4 + 63;
}