#ifndef FRAMERATECOUNTER_H
#define FRAMERATECOUNTER_H

#include <deque>
#include <GL/glfw.h>

struct FramerateCounter
{
    FramerateCounter();
    virtual ~FramerateCounter();

    void nextFrame();
    void setTargetFramerate(float n);
    void setAveragePeriod(int n);

    void wait();

    float currentFramerate;

    float targetFramerate;
    int period;

    double frameStart;

    std::deque<float> framerateList;
};

#endif // FRAMERATECOUNTER_H
