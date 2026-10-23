//
// Created by Filho, Antonio on 23/10/2026.
//
#pragma once

#include "Vector2.h"
#include <SDL3/SDL.h>

class Paddle {
private:
    Vector2 position;

public:
    Paddle(Vector2 position);
    ~Paddle() = default;

    void Draw(SDL_Renderer* renderer);
    void Move(float deltaTime, int direction);

    SDL_FRect GetRect();

};
