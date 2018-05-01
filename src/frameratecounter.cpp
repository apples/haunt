#include "frameratecounter.h"

FramerateCounter::FramerateCounter()
{
    framerateList.resize(1, 0);
    currentFramerate = 0;
    period = 1;
}

FramerateCounter::~FramerateCounter()
{
    //dtor
}


void FramerateCounter::nextFrame()
{
    float instFPS = 1/(glfwGetTime() - frameStart);

    framerateList.pop_front();
    framerateList.push_back(instFPS);

    float sum = 0;
    for (unsigned int i=0; i<framerateList.size(); i++)
    {
        sum += framerateList.at(i);
    }
    currentFramerate = sum / framerateList.size();

    frameStart = glfwGetTime();
}

void FramerateCounter::setTargetFramerate(float n)
{
    targetFramerate = n;
}

void FramerateCounter::setAveragePeriod(int n)
{
    period = n;
    framerateList.resize(n, currentFramerate);
}

void FramerateCounter::wait()
{
    double instFPS = 1.0/(glfwGetTime() - frameStart);
    if (instFPS > targetFramerate)
    {
        glfwSleep((1.0/targetFramerate)-(glfwGetTime() - frameStart));
    }
}
