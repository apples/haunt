#include "rng.h"

#include "game.h"

#include <GL/glfw.h>

RNG::RNG()
{
    reset();
}

void RNG::reset()
{
    //TODO *(int*)&x
    a=glfwGetTime()*1000000.0;
    unsigned int t=glfwGetTime()*1000000.0;
    last=(t<<28);
}

float RNG::getNextf()
{
    unsigned int t = a^(a<<11);

    a = b;
    b = c;
    c = last;

    last = last^(last>>21)^(t^(t<<9));

    return last/4294967296.0;
}
