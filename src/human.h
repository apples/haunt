#ifndef HUMAN_H
#define HUMAN_H

#include "bitmapfont.h"
#include "rng.h"

#include <GL/glfw.h>

class Human
{
public:
    Human();

    int x, y;
    float dirX, dirY;
    int tmpDist;

    int fear;
    bool dead;
    float fade;

    int scream;
    int screamTime;

    int aniType;
    int aniFrame;

    RNG rng;

    void drawMe(BitmapFont &font);

    void update();
    int move();
    int addFear(int f);
};

#endif // HUMAN_H
