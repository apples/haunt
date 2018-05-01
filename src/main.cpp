
#include <GL/glfw.h>
#include "game.h"

extern Game game = Game();

int main(int argc, char* argv[])
{
    game.init(640, 480);

    while (game.running)
    {
        if (game.gameLoop() == 1) {
            game.reset();
            continue;
        }
        break;
    }

    return 0;
}
