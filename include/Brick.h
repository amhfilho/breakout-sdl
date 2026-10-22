//
// Created by Filho, Antonio on 21/10/2026.
//

#pragma once
#include "Vector2.h"
#include <SDL3/SDL.h>
#include <map>

#include "Colors.h"

class Brick {

private:
    Vector2 position;
    const Color& color;
public:
    // Pointers avoid static-initialization-order issues with the globals in Colors.cpp
    static const std::map<int, const Color*> colors;

    Brick(Vector2 position, const Color& color);
    ~Brick();

    void Draw(SDL_Renderer* renderer);

    SDL_FRect GetRect();
};

