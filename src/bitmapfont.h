#ifndef BITMAPFONT_H
#define BITMAPFONT_H

#include <GL/glfw.h>
#include <string>

class BitmapFont
{
public:
    BitmapFont();
    virtual ~BitmapFont();

    int charWidth;
    int charHeight;

    void setTexture(GLuint);

    void genLists();
    void drawString2D(float x, float y, float size, float r, float g, float b, std::string text, int style);

    GLuint texture;
    GLuint glLists2D;
};

#endif // BITMAPFONT_H
