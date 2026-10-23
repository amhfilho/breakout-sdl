//
// Created by Filho, Antonio on 21/10/2026.
//

#pragma once

#include <SDL3/SDL.h>
#include <vector>
#include "Brick.h"
#include "Paddle.h"

class Game {
public:
    explicit Game();
    ~Game();

    bool running;
    bool InitializeWindow();
    void HandleInput();
    void Update();
    void Draw();

private:
    SDL_Window* window;
    SDL_Renderer* renderer;

    Uint64 mTicksCount;
    float deltaTime;
    int paddleDirection;

    std::vector<Brick> bricks;
    Paddle paddle;

    void DrawGameArea();
    void CreateBricks();
};

