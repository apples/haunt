#ifndef HUMANGROUP_H
#define HUMANGROUP_H

#include "bitmapfont.h"
#include "human.h"

#include <vector>

class HumanGroup
{
public:
    HumanGroup();

    std::vector<Human> humans;

    GLuint texture;

    void reset(int n);

    Human *get(int n);

    void update();
    void drawAll(BitmapFont &font);

    int size()
    {
        return humans.size();
    }

    void setTexture(GLuint n);
};

#endif // HUMANGROUP_H
