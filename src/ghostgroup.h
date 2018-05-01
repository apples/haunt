#ifndef GHOSTGROUP_H
#define GHOSTGROUP_H

#include "ghost.h"
#include <GL/glfw.h>

#include <vector>

class GhostGroup
{
public:
    GhostGroup();

    std::vector<Ghost> ghosts;

    GLuint texture;

    void reset(int n);

    void addGhost();
    bool activateNext(int x, int y);

    int isActive(int n);
    bool isBoo(int n);

    Ghost *get(int n);

    void update();
    void drawAll();

    int size()
    {
        return ghosts.size();
    }

    void setTexture(GLuint n);
};

#endif // GHOSTGROUP_H
