#pragma once

class Background {
public:
    Background();
    void update();
    void reset();
    void loopCloud();

    double cloudX1, cloudX2;
};