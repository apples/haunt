#include "ghostgroup.h"

GhostGroup::GhostGroup()
{
    reset(0);
}

void GhostGroup::reset(int n)
{
    ghosts.reserve(n+1);
    ghosts.clear();
    ghosts.push_back(Ghost());
}

void GhostGroup::addGhost()
{
    ghosts.push_back(Ghost());
}

bool GhostGroup::activateNext(int x, int y)
{
    unsigned int i;

    for (i=0; i<ghosts.size(); i++)
    {
        if (!ghosts.at(i).active)
        {
            ghosts.at(i).activate(x, y);
            return true;
        }
    }
    return false;
}

bool GhostGroup::isBoo(int n)
{
    if (ghosts.at(n).boo && !ghosts.at(n).booCheck)
    {
        ghosts.at(n).booCheck = true;
        return true;
    }
    return false;
}

int GhostGroup::isActive(int n)
{
    if (ghosts.at(n).active)
        return 1;
    return 0;
}

Ghost *GhostGroup::get(int n)
{
    return &ghosts.at(n);
}

void GhostGroup::update()
{
    for (unsigned int i=0; i<ghosts.size(); i++)
    {
        ghosts.at(i).update();
    }
}

void GhostGroup::drawAll()
{
    glBindTexture(GL_TEXTURE_2D, texture);
    glColor3f(1, 1, 1);

    for (unsigned int i=0; i<ghosts.size(); i++)
    {
        ghosts.at(i).drawMe(i);
    }
}

void GhostGroup::setTexture(GLuint n)
{
    texture = n;
}
