#ifndef RECT2D_H
#define RECT2D_H

#include "point2d.h"

class Rect2D
{
public:
    Rect2D();
    virtual ~Rect2D();

    Point2D pos;
    Point2D size;

    bool intersect(Rect2D target);
};

#endif // RECT2D_H
