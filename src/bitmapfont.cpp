#include "bitmapfont.h"

BitmapFont::BitmapFont()
{
    charWidth = 8;
    charHeight = 8;
    genLists();
}

BitmapFont::~BitmapFont()
{
    //dtor
}

void BitmapFont::setTexture(GLuint t) {
    texture = t;
}

void BitmapFont::genLists()
{
    glLists2D = glGenLists(256);

    float sx = charWidth / 128.0;
    float sy = charHeight / 128.0;

    for (int i = 0; i < 256; i++)
    {
        float a = (char)(i & 0x0f);
        float b = (char)((i >> 4) & 0x0f);

        glNewList(glLists2D + i, GL_COMPILE);

        glBegin(GL_QUADS);
            glTexCoord2f(a * sx, b * sy);
            glVertex2f(0, 0);

            glTexCoord2f((a + 1) * sx, b * sy);
            glVertex2f(1, 0);

            glTexCoord2f((a + 1) * sx, (b + 1) * sy);
            glVertex2f(1, 1);

            glTexCoord2f(a * sx, (b + 1) * sy);
            glVertex2f(0, 1);
        glEnd();

        glEndList();
    }
}

void BitmapFont::drawString2D(float x, float y, float size, float r, float g, float b, std::string text, int style)
{
    if (style & 1)
        x = x - text.length() * size / 2;

    glPushMatrix();

    glColor3f(r, g, b);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTranslatef(x, y, 0);
    glScalef(size, size, 1);

    for (uint32_t i = 0; i < text.length(); i++)
    {
        if (style & 4) {
            glBindTexture(GL_TEXTURE_2D, 0);
            glColor4f(0, 0, 0, .5);
            glBegin(GL_QUADS);
                glVertex2f(0, 0);
                glVertex2f(1, 0);
                glVertex2f(1, 1);
                glVertex2f(0, 1);
            glEnd();
            glColor4f(r, g, b, 1);
            glBindTexture(GL_TEXTURE_2D, texture);
        }

        glCallList(glLists2D + text.at((style & 2) ? text.length()-1-i : i));

        glTranslatef((style & 2) ? -1 : 1, 0, 0);
    }

    glPopMatrix();
}
