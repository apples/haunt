
#include "game.h"

#include "makestring.h"

#include <GL/glfw.h>

Game::Game()
{
    //Do nothing
}

Game::~Game()
{
    glfwTerminate();
}

int Game::init(int w, int h)
{
    running = true;

    windowWidth = w;
    windowHeight = h;

    initGLFW();

    load();

    font = BitmapFont();
    font.setTexture(textures[0]);

    humans.setTexture(textures[1]);
    ghosts.setTexture(textures[1]);

    framerate.setTargetFramerate(60);
    framerate.setAveragePeriod(1);

    reset();

    return 0;
}

int Game::initGLFW()
{
    glfwInit();

    glfwOpenWindowHint(GLFW_WINDOW_NO_RESIZE, GL_TRUE);

    if(!glfwOpenWindow(windowWidth, windowHeight, 0, 0, 0, 0, 0, 0, GLFW_WINDOW))
    {
        glfwTerminate();
        running = false;
    }

    glfwSetWindowTitle("Haunt");

    //OpenGL settings
    glEnable(GL_TEXTURE_2D);
    glShadeModel(GL_SMOOTH);
    glEnable(GL_BLEND);
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_FASTEST);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glClearColor( 1.0f, 1.0f, 1.0f, 1.0f );

    //Adjust matrices
    glViewport(0, 0, (GLfloat)windowWidth, (GLfloat)windowHeight);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, windowWidth, windowHeight, 0);

    glfwEnable(GLFW_STICKY_MOUSE_BUTTONS);
    glfwEnable(GLFW_MOUSE_CURSOR);

    return 0;
}

int Game::load()
{
    //Load texture
    glGenTextures(3,&textures[0]);

    glBindTexture(GL_TEXTURE_2D, textures[0]);
    glfwLoadTexture2D("art/font.tga", GLFW_ORIGIN_UL_BIT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    glBindTexture(GL_TEXTURE_2D, textures[1]);
    glfwLoadTexture2D("art/sprites.tga", GLFW_ORIGIN_UL_BIT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    glBindTexture(GL_TEXTURE_2D, textures[2]);
    glfwLoadTexture2D("art/tomb.tga", GLFW_ORIGIN_UL_BIT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    return 0;
}

int Game::reset()
{
    humans.reset(12);
    ghosts.reset(13);

    ghostSummons = 0;
    totalFearCaused = 0;

    return 0;
}

int Game::gameLoop()
{
    glClearColor(1, 1, 1, 1);

    bool mouseLock = false;

    startTime = glfwGetTime();

    while(running)
    {
        framerate.nextFrame();

        //User input
        if (glfwGetMouseButton(GLFW_MOUSE_BUTTON_LEFT) && !mouseLock)
        {
            int a, b;
            glfwGetMousePos(&a, &b);
            a -= 16;
            b -= 16;
            if (ghosts.activateNext(a, b))
                ghostSummons++;
            mouseLock = true;
        }
        if (!glfwGetMouseButton(GLFW_MOUSE_BUTTON_LEFT) && mouseLock)
        {
            mouseLock = false;
        }

        //Cheats
        if (glfwGetKey(']'))
            framerate.setTargetFramerate(600);
        else if (glfwGetKey('['))
            framerate.setTargetFramerate(6);
        else
            framerate.setTargetFramerate(60);

        //Entity updates
        humans.update();
        ghosts.update();

        //Interactions
        for (int a=0; a<ghosts.size(); a++)
        {
            if (ghosts.isBoo(a))
                for (int b=0; b<humans.size(); b++)
                {
                    if (!humans.get(b)->dead)
                    {
                        int dx = ghosts.get(a)->x - humans.get(b)->x;
                        int dy = ghosts.get(a)->y - humans.get(b)->y;
                        int dist2 = dx*dx + dy*dy;

                        if (dist2 <= 16384)
                        {
                            if (glfwGetKey('F')) //Cheat
                                dist2 = -75000;
                            totalFearCaused += 16384 - dist2;
                            if (humans.get(b)->addFear(16384 - dist2))
                            {
                                ghosts.addGhost();
                            }
                            else
                            {
                                float dxfin = ((dx>0)?-1.0:1.0)+dx/128.0;
                                float dyfin = ((dy>0)?-1.0:1.0)+dy/128.0;
                                humans.get(b)->dirX = dxfin;
                                humans.get(b)->dirY = dyfin;
                            }
                        }
                    }
                }
        }

        //Win check
        if (humans.size() == 0) {
            winTime = glfwGetTime();
            if (win() == 1)
                return 1;
            return 0;
        }

        //Rendering
        glMatrixMode(GL_MODELVIEW);
        glPushMatrix();
        glClear(GL_COLOR_BUFFER_BIT);

        //Begin Render

        drawBackground();
        humans.drawAll(font);
        ghosts.drawAll();

        font.drawString2D(616, 456, 24, 1, 1, 1, makeString((int)(glfwGetTime() - startTime)), 2);
        font.drawString2D(0, 456, 24, 1, 1, 1, makeString(ghostSummons), 0);
        font.drawString2D(320, 464, 16, 1, 1, 1, makeString(totalFearCaused), 1);

        //End render

        glPopMatrix();
        glfwSwapBuffers();

        running = !glfwGetKey(GLFW_KEY_ESC) && glfwGetWindowParam(GLFW_OPENED);
        framerate.wait();
    }

    return 0;
}

void Game::drawBackground()
{
    glBindTexture(GL_TEXTURE_2D, textures[1]);
    glColor3f(1, 1, 1);

    for (int x=0; x < windowWidth; x+=32)
    {
        for (int y=0; y < windowHeight; y+=32)
        {
            glBegin(GL_QUADS);
                glTexCoord2f(0.5, 0.5);
                glVertex2f(x, y);

                glTexCoord2f(1.0, 0.5);
                glVertex2f(x+32, y);

                glTexCoord2f(1.0, 1.0);
                glVertex2f(x+32, y+32);

                glTexCoord2f(0.5, 1.0);
                glVertex2f(x, y+32);
            glEnd();
        }
    }

    glBindTexture(GL_TEXTURE_2D, textures[2]);

    glBegin(GL_QUADS);
        glTexCoord2f(0.0, 0.0);
        glVertex2f(256, 176);

        glTexCoord2f(1.0, 0.0);
        glVertex2f(384, 176);

        glTexCoord2f(1.0, 1.0);
        glVertex2f(384, 304);

        glTexCoord2f(0.0, 1.0);
        glVertex2f(256, 304);
    glEnd();
}

int Game::win() {
    glClearColor(1, 1, 1, 1);

    while(running)
    {
        framerate.nextFrame();

        //User input
        if (glfwGetKey(GLFW_KEY_ENTER))
            return 1;

        //Rendering
        glMatrixMode(GL_MODELVIEW);
        glPushMatrix();
        glClear(GL_COLOR_BUFFER_BIT);

        //Begin Render

        drawBackground();
        font.drawString2D(320, 32, 48, 1, 1, 1, "COMPLETE", 1+4);
        font.drawString2D(16, 120, 24, 1, 1, 1, "TIME:", 0+4);
        font.drawString2D(592, 120, 24, 1, 1, 1, makeString((int)((winTime - startTime)*100.0) / 100.0), 2+4);
        font.drawString2D(16, 144, 24, 1, 1, 1, "GHOSTS SUMMONED:", 0+4);
        font.drawString2D(592, 144, 24, 1, 1, 1, makeString(ghostSummons), 2+4);
        font.drawString2D(320, 312, 24, 1, 1, 1, "FEAR CAUSED:", 1+4);
        font.drawString2D(320, 336, 24, 1, 1, 1, makeString(totalFearCaused), 1+4);
        font.drawString2D(8, 456, 16, 1, 1, 1, "ESC TO QUIT", 0+4);
        font.drawString2D(616, 456, 16, 1, 1, 1, "ENTER TO RETRY", 2+4);

        //End render

        glPopMatrix();
        glfwSwapBuffers();

        running = !glfwGetKey(GLFW_KEY_ESC) && glfwGetWindowParam(GLFW_OPENED);
        framerate.wait();
    }

    return 0;
}
