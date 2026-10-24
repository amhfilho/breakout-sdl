//
// Created by Filho, Antonio on 23/10/2026.
//

#include "Paddle.h"
#include "Colors.h"
#include "Constants.h"

Paddle::Paddle(Vector2 position)
    : position(position)
{

}

void Paddle::Draw(SDL_Renderer* renderer) {
    SDL_SetRenderDrawColor(renderer, blue.r, blue.g, blue.b, blue.a);
    SDL_FRect rect = GetRect();
    SDL_RenderFillRect(renderer, &rect);
}

void Paddle::Move(float deltaTime, int direction) {
    position.x += direction * Constants::Paddle::Speed * deltaTime;
    if (position.x < Constants::GameArea::X) {
        position.x = Constants::GameArea::X;
    }
    else if (position.x + Constants::Paddle::Width > Constants::GameArea::X + Constants::GameArea::Width) {
        position.x = Constants::GameArea::X + Constants::GameArea::Width - Constants::Paddle::Width;
    }
}

SDL_FRect Paddle::GetRect() {
    return {
        position.x,
        position.y,
        Constants::Paddle::Width,
        Constants::Paddle::Height
    };
}