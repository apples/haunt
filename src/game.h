#ifndef GAME_H
#define GAME_H

#include "bitmapfont.h"
#include "frameratecounter.h"
#include "ghostgroup.h"
#include "humangroup.h"
#include "rng.h"

#include <GL/glfw.h>

class Game
{
public:
    Game();
    virtual ~Game();

    int windowWidth, windowHeight;

    BitmapFont font;

    bool running;
    GLuint textures[3];

    FramerateCounter framerate;

    HumanGroup humans;
    GhostGroup ghosts;

    //Stats
    float startTime;
    float winTime;
    int ghostSummons;
    uint64_t totalFearCaused;

    int init(int w, int h);
    int initGLFW();
    int load();
    int reset();

    int gameLoop();
    void drawBackground();

    int win();
};

extern Game game;

#endif // GAME_H
