#include "ghost.h"

#include <GL/glfw.h>

Ghost::Ghost()
{
    active = false;

    tmpDist = 0;
    totalDist = 0;

    aniFrame = 0;
    boo = false;
    booCheck = false;

    totalTime = 0;
    aniTime = 0;

    trans = 0;
}

void Ghost::drawMe(int n)
{
    int hudShift = n*48;

    glColor4f(1, 1, 1, (active) ? .25 : 1);
    glBegin(GL_QUADS);
    glTexCoord2f(0.75, 0.25);
    glVertex2f(16+hudShift, 16);

    glTexCoord2f(1.0, 0.25);
    glVertex2f(48+hudShift, 16);

    glTexCoord2f(1.0, 0.5);
    glVertex2f(48+hudShift, 48);

    glTexCoord2f(0.75, 0.5);
    glVertex2f(16+hudShift, 48);
    glEnd();

    if (!active)
        return;

    float cxShift = aniFrame*0.25;

    int ty = y-(totalTime)/12;

    glColor4f(1, 1, 1, trans);

    glBegin(GL_QUADS);
    glTexCoord2f(0.5+cxShift, 0.0);
    glVertex2f(x, ty);

    glTexCoord2f(0.75+cxShift, 0.0);
    glVertex2f(x+32, ty);

    glTexCoord2f(0.75+cxShift, 0.25);
    glVertex2f(x+32, ty+32);

    glTexCoord2f(0.5+cxShift, 0.25);
    glVertex2f(x, ty+32);
    glEnd();

    if (boo)
    {
        glColor4f(1, 1, 1, 1);

        glBegin(GL_QUADS);
        glTexCoord2f(0.5, 0.25);
        glVertex2f(x+20, ty-20);

        glTexCoord2f(0.75, 0.25);
        glVertex2f(x+52, ty-20);

        glTexCoord2f(0.75, 0.5);
        glVertex2f(x+52, ty+12);

        glTexCoord2f(0.5, 0.5);
        glVertex2f(x+20, ty+12);
        glEnd();
    }
}

void Ghost::activate(int a, int b)
{
    active = true;
    booCheck = false;
    setPos(a, b);
    totalDist = 0;
    tmpDist = 0;

    totalTime = 0;
}

void Ghost::update()
{
    if (!active)
        return;

    totalTime++;
    aniTime++;

    if (totalTime >= 24)
    {
        aniFrame++;
        if (aniFrame >= 2)
            aniFrame = 0;
        aniTime = 0;
    }

    if (totalTime >= 60 && totalTime < 75)
    {
        boo = true;
    }
    else
    {
        boo = false;
    }

    if (totalTime <= 60)
    {
        trans = totalTime/60.0;
    }
    else
    {
        trans = (120.0 - totalTime)/60.0;
    }

    if (totalTime >= 120)
    {
        active = false;
    }
}

void Ghost::setPos(int a, int b)
{
    x = a;
    y = b;
}
