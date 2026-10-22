//
// Created by Filho, Antonio on 21/10/2026.
//
#include "Game.h"

#include "Brick.h"
#include "Constants.h"
#include "Colors.h"
#include "Vector2.h"

Game::Game()
    : running(true) {
    CreateBricks();
}

bool Game::InitializeWindow() {
    if (!SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO)) {
        SDL_Log("Error starting SDL3: %s", SDL_GetError());
        return false;
    }

    window = SDL_CreateWindow(Constants::Window::Title, Constants::Window::Width, Constants::Window::Height, 0);
    if (!window) {
        SDL_Log("Error creating window: %s", SDL_GetError());
        SDL_Quit();
        return false;
    }

    renderer = SDL_CreateRenderer(window, nullptr);
    if (!renderer) {
        SDL_Log("Error creating renderer: %s", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        return false;
    }

    if (!SDL_SetRenderVSync(renderer, 1)) {
        SDL_Log("Unable to enable vertical sync: %s", SDL_GetError());
        return false;
    }

    return true;
}

void Game::HandleInput() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_EVENT_QUIT:
                running = false;
                break;
            case SDL_EVENT_KEY_DOWN:
                switch (event.key.key) {
                    case SDLK_ESCAPE:
                        running = false;
                        break;
                }
                break;
        }
    }
}

void Game::Draw() {
    SDL_SetRenderDrawColor(renderer, white.r, white.g, white.b, white.a);
    SDL_RenderClear(renderer);

    DrawGameArea();

    for (auto& brick : bricks) {
        brick.Draw(renderer);
    }

    SDL_RenderPresent(renderer);
}

void Game::DrawGameArea() {
    SDL_SetRenderDrawColor(renderer, black.r, black.g, black.b, black.a);
    SDL_FRect gameArea = {
        Constants::GameArea::X,
        Constants::GameArea::Y,
        Constants::GameArea::Width,
        Constants::GameArea::Height
    };
    SDL_RenderFillRect(renderer, &gameArea);
}

void Game::CreateBricks() {
    constexpr int colorCount = 4;
    constexpr int rowsPerColor = 2;
    constexpr int columns = 12;

    for (int row = 0; row < colorCount * rowsPerColor; row++) {
        const Color& color = *Brick::colors.at(row / rowsPerColor);
        for (int column = 0; column < columns; column++) {
            Vector2 position(Constants::GameArea::X + Constants::Brick::XOffset + column * (Constants::Brick::Width + Constants::Brick::XSpacing),
                             Constants::GameArea::Y + Constants::Brick::YOffset + row * (Constants::Brick::Height + Constants::Brick::YSpacing));
            bricks.emplace_back(position, color);
        }
    }
}

Game::~Game() {
    bricks.clear();
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}
