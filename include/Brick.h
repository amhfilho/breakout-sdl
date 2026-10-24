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
    const Color* color;
    int score;
public:
    // Pointers avoid static-initialization-order issues with the globals in Colors.cpp
    static const std::map<int, const Color*> colors;
    static const std::map<const Color*, int> scores;

    Brick(Vector2 position, const Color& color);
    ~Brick() = default;

    void Draw(SDL_Renderer* renderer);

    SDL_FRect GetRect();
    int GetScore() const;
};

