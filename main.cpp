
#include "GameManager.h"

int main(int argc, char* argv[]) {
    GameManager game;
    if (!game.init("Pac-Man", 800, 600)) {
        return -1;  // Exit if initialization fails
    }

    game.run();
    game.cleanup();

    return 0;
}
