//
// Created by Filho, Antonio on 23/10/2026.
//
#pragma once
#include "Vector2.h"
#include "BallDirection.h"
#include <SDL3/SDL.h>

#include "Brick.h"

class Ball {
public:
    Ball(Vector2 position, BallDirection direction);
    ~Ball() = default;

    void Update(float deltaTime);
    void CheckWallCollision(const SDL_FRect& gameArea);

    bool CheckPaddleCollision(const SDL_FRect &paddleRect);

    bool CheckBrickCollision(Brick &brick);
    void BounceBallDown();

    bool isMissed(const SDL_FRect& gameArea);

    void Draw(SDL_Renderer* renderer);

    void IncreaseSpeedPercentageBy(float amount);

    SDL_FRect GetRect();

private:
    void SetVelocityFromAngle(float degreesFromHorizontal);

    Vector2 position;
    BallDirection direction;
    Vector2 ballVelocity;

};
