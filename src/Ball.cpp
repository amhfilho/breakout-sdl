//
// Created by Filho, Antonio on 23/10/2026.
//
#include <SDL3/SDL.h>
#include <cmath>
#include <numbers>
#include "Ball.h"

#include "Brick.h"
#include "Colors.h"
#include "Constants.h"

Ball::Ball(Vector2 position, BallDirection direction) :
    position(position),
    direction(direction),
    ballVelocity(Vector2(Constants::Ball::InitialVelocity.x, Constants::Ball::InitialVelocity.y)) {

    }

void Ball::Update(float deltaTime) {
    position.x += ballVelocity.x * deltaTime * static_cast<float>(direction.x);
    position.y += ballVelocity.y * deltaTime * static_cast<float>(direction.y);
}

void Ball::CheckWallCollision(const SDL_FRect &gameArea) {
    if (position.x + Constants::Ball::SquareSize > gameArea.x + gameArea.w
        && direction.x > 0) {
        direction.x = -1;
    }
    else if (position.x < gameArea.x && direction.x < 0) {
        direction.x = 1;
    }
}

bool Ball::CheckPaddleCollision(const SDL_FRect &paddleRect) {
    bool collides = false;
    // A ball already moving up is still overlapping the paddle from a previous hit
    if (direction.y < 0) {
        return false;
    }
    SDL_FRect ballRect = GetRect();
    float sectionWidth = paddleRect.w / 4.0f;
    SDL_FRect leftOuter = {paddleRect.x, paddleRect.y, sectionWidth, paddleRect.h};
    SDL_FRect leftInner = {paddleRect.x + sectionWidth, paddleRect.y, sectionWidth, paddleRect.h};
    SDL_FRect rightInner = {paddleRect.x + 2 * sectionWidth, paddleRect.y, sectionWidth, paddleRect.h};
    SDL_FRect rightOuter = {paddleRect.x + 3 * sectionWidth, paddleRect.y, sectionWidth, paddleRect.h};

    if (SDL_HasRectIntersectionFloat(&ballRect, &leftOuter)) {
        direction.y = -1;
        direction.x = -1;
        SetVelocityFromAngle(Constants::Ball::OuterBounceAngle);
        collides = true;
    }
    else if (SDL_HasRectIntersectionFloat(&ballRect, &leftInner)) {
        direction.y = -1;
        direction.x = -1;
        ballVelocity.x = std::max(ballVelocity.x, Constants::Ball::InitialVelocity.x);
        ballVelocity.y = std::max(ballVelocity.y, Constants::Ball::InitialVelocity.y);
        collides = true;
    }
    else if (SDL_HasRectIntersectionFloat(&ballRect, &rightInner)) {
        direction.y = -1;
        direction.x = 1;
        ballVelocity.x = std::max(ballVelocity.x, Constants::Ball::InitialVelocity.x);
        ballVelocity.y = std::max(ballVelocity.y, Constants::Ball::InitialVelocity.y);
        collides = true;
    }
    else if (SDL_HasRectIntersectionFloat(&ballRect, &rightOuter)) {
        direction.y = -1;
        direction.x = 1;
        SetVelocityFromAngle(Constants::Ball::OuterBounceAngle);
        collides = true;
    }
    return collides;

}

void Ball::SetVelocityFromAngle(float degreesFromHorizontal) {
    const Vector2 initial = {
        std::max(ballVelocity.x, Constants::Ball::InitialVelocity.x),
        std::max(ballVelocity.y, Constants::Ball::InitialVelocity.y)
    };
    const float speed = std::sqrt(initial.x * initial.x + initial.y * initial.y);
    const float radians = degreesFromHorizontal * std::numbers::pi_v<float> / 180.0f;
    ballVelocity = Vector2(speed * std::cos(radians), speed * std::sin(radians));
}

bool Ball::CheckBrickCollision(Brick &brick) {
    SDL_FRect ballRect = GetRect();
    SDL_FRect brickRect = brick.GetRect();
    return SDL_HasRectIntersectionFloat(&ballRect, &brickRect);
}

void Ball::BounceBallDown() {
    direction.y = 1;
}

bool Ball::isMissed(const SDL_FRect &gameArea) {
    return position.y > (gameArea.y + gameArea.h);
}

void Ball::Draw(SDL_Renderer *renderer) {
    SDL_FRect rect = GetRect();
    SDL_SetRenderDrawColor(renderer, white.r, white.g, white.b, white.a);
    SDL_RenderFillRect(renderer, &rect);
}

void Ball::IncreaseSpeedPercentageBy(float amount) {
    ballVelocity.x *= 1.0f + amount/100;
    ballVelocity.y *= 1.0f + amount/100;
}

SDL_FRect Ball::GetRect() {
    return SDL_FRect {
        position.x,
        position.y,
        Constants::Ball::SquareSize,
        Constants::Ball::SquareSize
    };
}
