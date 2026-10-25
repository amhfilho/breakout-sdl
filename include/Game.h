//
// Created by Filho, Antonio on 21/10/2026.
//

#pragma once

#include <SDL3/SDL.h>
#include <memory>
#include <vector>

#include "Ball.h"
#include "Brick.h"
#include "FontLoader.h"
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
    SDL_FRect gameArea;
    int paddleDirection;

    int balls;
    std::vector<Brick> bricks;
    int score;
    Paddle paddle;
    Ball ball;
    int currentBall;
    std::unique_ptr<FontLoader> scoreFont;

    void DrawGameArea();
    void CreateBricks();
    Ball CreateBall();

    static Vector2 GetRandomPosition();

    void CheckBrickCollision();

    void WriteScore();

    void WriteCurrentBall();

    static int GetRandomXDirection();
};

