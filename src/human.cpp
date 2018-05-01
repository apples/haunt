
#include "human.h"
#include "rng.h"

#include <cmath>

Human::Human()
{
    x = rng.getNextf()*640.0;
    y = rng.getNextf()*480.0;

    dirX = 1.0-rng.getNextf()*2.0;
    dirY = 1.0-rng.getNextf()*2.0;

    tmpDist = 0;

    fear = 0;
    dead = false;
    fade = 1.0;

    scream = 0;
    screamTime = 0;

    aniType = (int)(rng.getNextf()*4.0);
    aniFrame = 0;
}

void Human::drawMe(BitmapFont &font)
{
    float cxShift = aniFrame*0.25;
    float cyShift = aniType*0.25;

    glPushMatrix();

    glColor4f(1.0-fear/49152.0, 1.0-fear/49152.0, 1, fade);
    glTranslatef(x+16, y+16, 0);
    glScalef(5.0-fade*4.0, 5.0-fade*4.0, 0);

    glBegin(GL_QUADS);
        glTexCoord2f(0.0+cxShift, 0.0+cyShift);
        glVertex2f(-16, -16);

        glTexCoord2f(0.25+cxShift, 0.0+cyShift);
        glVertex2f(16, -16);

        glTexCoord2f(0.25+cxShift, 0.25+cyShift);
        glVertex2f(16, 16);

        glTexCoord2f(0.0+cxShift, 0.25+cyShift);
        glVertex2f(-16, 16);
    glEnd();

    glPopMatrix();

    if (screamTime > 0) {
        if (scream == 1) {
            font.drawString2D(x+16, y+32, 8, 1, 1, 1, "AAAAAAH!", 1);
        } else if (scream == 2) {
            font.drawString2D(x+16, y+32, 8, 1, 1, 1, "DEMONS", 1);
        } else if (scream == 3) {
            font.drawString2D(x+16, y+32, 8, 1, 1, 1, "IEEEEE!", 1);
        } else if (scream == 4) {
            font.drawString2D(x+16, y+32, 8, 1, 1, 1, "NOOOOOO!", 1);
        } else if (scream == 5) {
            font.drawString2D(x+16, y+32, 8, 1, 1, 1, "YEAAARGH", 1);
        } else {
            font.drawString2D(x+16, y+32, 8, 1, 1, 1, "GHOST!", 1);
        }

        screamTime--;
    }
}

void Human::update()
{
    if (!dead)
    {
        tmpDist += move();
        if (tmpDist >= 5)
        {
            aniFrame++;
            if (aniFrame>1)
                aniFrame=0;
            tmpDist -= 5;
        }
        fear -= 56;
        if (fear < 0)
            fear = 0;
    }
    else
    {
        fade -= 1.0/30.0;
    }
}

int Human::move()
{
    int r=0;

    float roll = rng.getNextf();

    if (roll < std::abs(dirX))
    {
        if (dirX > 0)
        {
            x += 1;
        }
        else
        {
            x -= 1;
        }
        r++;
    }

    if (roll < std::abs(dirY))
    {
        if (dirY > 0)
        {
            y += 1;
        }
        else
        {
            y -= 1;
        }
        r++;
    }

    if (r)
    {
        if (((x <= 0) || (x <= 384 && x > 384 - 32 && y > 176-32 && y <= 304)) && dirX <= 0)
            dirX = rng.getNextf();
        if (((x >= 640 - 32) || (x >= 256-32 && x < 256 && y > 176-32 && y <= 304)) && dirX >= 0)
            dirX = -rng.getNextf();

        if (((y <= 0) || (y <= 304 && y > 304 - 32 && x > 256-32 && x <= 384)) && dirY <= 0)
            dirY = rng.getNextf();
        if (((y >= 480 - 32) || (y >= 176-32 && y < 176 && x > 256-32 && x <= 384)) && dirY >= 0)
            dirY = -rng.getNextf();
    }

    return r;
}

int Human::addFear(int f)
{
    fear += f;

    if (fear >= 49152)
    {
        dead = true;
        return 1;
    }

    RNG rng;

    scream = rng.getNextf()*6.0+1.0;
    screamTime = 60;

    return 0;
}
