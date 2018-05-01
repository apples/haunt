#include "rect2d.h"

#include <iostream>

Rect2D::Rect2D()
{
    pos = Point2D(0,0);
    size = Point2D(0,0);
}

Rect2D::~Rect2D()
{
    //dtor
}

bool Rect2D::intersect(Rect2D target)
{
    bool r = false;

    if (pos.x < target.pos.x + target.size.x &&
            pos.y < target.pos.y + target.size.y &&
            target.pos.x < pos.x + size.x &&
            target.pos.y < pos.y + size.y)
        r = true;

    return r;
}
