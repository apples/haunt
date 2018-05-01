#include "point2d.h"

Point2D::Point2D()
{
    x = 0;
    y = 0;
}

Point2D::Point2D(float nx, float ny)
{
    x = nx;
    y = ny;
}

bool Point2D::testRect(Point2D pos, Point2D s)
{
    bool r=false;

    if (x < pos.x + s.x &&
            y < pos.y + s.y &&
            x > pos.x &&
            y > pos.y)
        r = true;

    return r;
}
