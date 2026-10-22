//
// Created by Filho, Antonio on 21/10/2026.
//

#include "Brick.h"

#include "Constants.h"

const std::map<int, const Color*> Brick::colors = {
    {0, &red},
    {1, &orange},
    {2, &green},
    {3, &yellow}
};

Brick::Brick(Vector2 position, const Color& color)
    : position(position)
    , color(color) {
}

Brick::~Brick() {
}

void Brick::Draw(SDL_Renderer* renderer) {
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
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
