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
    enum class GameState {
        Playing, GameOver
    };

    explicit Game();
    ~Game();

    bool running;
    GameState state;
    bool InitializeWindow();

    void Reset();

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
    int paddleHits;
    std::unique_ptr<FontLoader> scoreFont;

    SDL_FRect CreateGameArea();
    void DrawGameArea();
    void CreateBricks();
    Ball CreateBall();

    static Vector2 GetRandomPosition();

    void CheckBrickCollision();

    void WriteScore();

    void WriteCurrentBall();

    static int GetRandomXDirection();

    void WriteGameOver();

    void WriteTextCenter(const char *text, float size, float y);
};

