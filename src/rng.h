#ifndef RNG_H
#define RNG_H

class RNG
{
public:
    RNG();

    unsigned int a, b, c, last;
    float getNextf();
    void reset();
};

#endif // RNG_H
