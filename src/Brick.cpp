//
// Created by Filho, Antonio on 21/10/2026.
//

#include "Brick.h"
#include "Constants.h"

const std::map<int, const Color*> Brick::colors = {
    {0, &red}, //7
    {1, &orange}, //5
    {2, &green}, //3
    {3, &yellow} //1
};

const std::map<const Color*, int> Brick::scores = {
    {&red, 7},
    {&orange, 5},
    {&green, 3},
    {&yellow, 1}
};

Brick::Brick(Vector2 position, const Color& color)
    : position(position)
    , color(&color)
    , score(scores.at(&color)) {
}

void Brick::Draw(SDL_Renderer* renderer) {
    SDL_SetRenderDrawColor(renderer, color->r, color->g, color->b, color->a);
    SDL_FRect rect = GetRect();
    SDL_RenderFillRect(renderer, &rect);
}

SDL_FRect Brick::GetRect() {
    return {
        position.x,
        position.y,
        Constants::Brick::Width,
        Constants::Brick::Height
    };
}

int Brick::GetScore() const {
    return score;
}
