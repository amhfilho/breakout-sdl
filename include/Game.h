//
// Created by Filho, Antonio on 21/10/2026.
//

#pragma once

#include <SDL3/SDL.h>
#include <vector>

#include "Brick.h"

class Game {
public:
    explicit Game();
    ~Game();

    bool running;
    bool InitializeWindow();
    void HandleInput();
    void Draw();

private:
    SDL_Window* window;
    SDL_Renderer* renderer;

    std::vector<Brick> bricks;

    void DrawGameArea();

    void CreateBricks();
};

