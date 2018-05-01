#ifndef POINT2D_H
#define POINT2D_H

struct Point2D
{
    Point2D();
    Point2D(float, float);

    float x, y;

    bool testRect(Point2D, Point2D);
};

#endif // POINT2D_H
