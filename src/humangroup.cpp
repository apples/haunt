
#include "humangroup.h"

HumanGroup::HumanGroup()
{
    reset(0);
}

void HumanGroup::reset(int n)
{
    humans.reserve(n);
    humans.clear();
    for (int i = 0; i<n; i++)
    {
        humans.push_back(Human());
    }
}

Human *HumanGroup::get(int n)
{
    return &humans.at(n);
}

void HumanGroup::update()
{
    for (unsigned int i=0; i<humans.size(); i++)
    {
        if (humans.at(i).dead && humans.at(i).fade <= 0)
        {
            humans.erase(humans.begin()+i);
            i--;
        }
        else
        {
            humans.at(i).update();
        }
    }
}

void HumanGroup::drawAll(BitmapFont &font)
{
    for (unsigned int i=0; i<humans.size(); i++)
    {
        glBindTexture(GL_TEXTURE_2D, texture);
        glColor3f(1, 1, 1);
        humans.at(i).drawMe(font);
    }
}

void HumanGroup::setTexture(GLuint n)
{
    texture = n;
}
