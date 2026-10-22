#include <iostream>

#include "Game.h"

int main() {
    Game game;
    if (!game.InitializeWindow()) {
        return -1;
    }

    while (game.running) {
        game.HandleInput();
        //game.Update();
        game.Draw();
    }

    return 0;
}
