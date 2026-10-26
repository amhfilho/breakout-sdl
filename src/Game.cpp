//
// Created by Filho, Antonio on 21/10/2026.
//
#include "Game.h"

#include <random>

#include "Brick.h"
#include "Constants.h"
#include "Colors.h"
#include "Vector2.h"

Game::Game()
    : running(true),
      state(GameState::Playing),
      mTicksCount(0),
      deltaTime(0.0f),
      gameArea(CreateGameArea()),
      paddleDirection(0),
      balls(Constants::Game::Balls),
      score(0),
      paddle(Vector2(Constants::Paddle::InitialX, Constants::Paddle::InitialY)),
      ball(CreateBall()),
      currentBall(1),
      paddleHits(0) {

    CreateBricks();
}

bool Game::InitializeWindow() {
    if (!SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO)) {
        SDL_Log("Error starting SDL3: %s", SDL_GetError());
        return false;
    }

    window = SDL_CreateWindow(
        Constants::Window::Title,
        Constants::Window::Width,
        Constants::Window::Height,
        0);
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

    scoreFont = std::make_unique<FontLoader>(Constants::Score::FontPath, Constants::Score::FontSize);

    return true;
}

void Game::Reset() {
    state = GameState::Playing;
    currentBall = 1;
    mTicksCount = SDL_GetTicks();
    score = 0;
    paddleHits = 0;
    ball = CreateBall();
    bricks.clear();
    CreateBricks();
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
                if (state == GameState::GameOver) {
                    if (event.key.key == SDLK_SPACE) {
                        Reset();
                    }
                    else {
                        continue;
                    }
                }
                break;
        }
        const bool* keys = SDL_GetKeyboardState(nullptr);
        if (keys[SDL_SCANCODE_LEFT]) {
            paddleDirection = -1;
        }
        else if (keys[SDL_SCANCODE_RIGHT]) {
            paddleDirection = 1;
        }
        else {
            paddleDirection = 0;
        }
    }
}

void Game::Update() {
    if (state == GameState::GameOver) {
        return;
    }
    Uint64 currentTicks = SDL_GetTicks();
    deltaTime = static_cast<float>(currentTicks - mTicksCount) / 1000.0f;
    mTicksCount = currentTicks;

    paddle.Move(deltaTime, paddleDirection);

    ball.Update(deltaTime);
    ball.CheckWallCollision(gameArea);
    if (ball.CheckPaddleCollision(paddle.GetRect())) {
        paddleHits++;
        if (paddleHits == 4) {
            ball.IncreaseSpeedPercentageBy(25.0f);
        }
        else if (paddleHits == 12) {
            ball.IncreaseSpeedPercentageBy(25.0f);
        }
    }
    CheckBrickCollision();

    if (ball.isMissed(gameArea)) {
        paddleHits = 0;
        if (currentBall + 1 > balls) {
            state = GameState::GameOver;
        }
        else {
            currentBall++;
            ball = CreateBall();
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

    paddle.Draw(renderer);

    ball.Draw(renderer);

    WriteScore();

    WriteCurrentBall();

    if (state == GameState::GameOver) {
        WriteGameOver();
    }

    SDL_RenderPresent(renderer);
}

SDL_FRect Game::CreateGameArea() {
    return SDL_FRect {
        Constants::GameArea::X,
        Constants::GameArea::Y,
        Constants::GameArea::Width,
        Constants::GameArea::Height
    };
}

void Game::DrawGameArea() {
    SDL_SetRenderDrawColor(renderer, black.r, black.g, black.b, black.a);
    SDL_RenderFillRect(renderer, &gameArea);
}

void Game::CreateBricks() {
    constexpr int rowsPerColor = 2;
    constexpr int columns = 12;

    for (int row = 0; row < Constants::Brick::Rows; row++) {
        const Color& color = *Brick::colors.at(row / rowsPerColor);
        for (int column = 0; column < columns; column++) {
            Vector2 position(Constants::GameArea::X + Constants::Brick::XOffset + column *
                (Constants::Brick::Width + Constants::Brick::XSpacing),
                             Constants::GameArea::Y + Constants::Brick::YOffset + row *
                (Constants::Brick::Height + Constants::Brick::YSpacing));
            bricks.emplace_back(position, color);
        }
    }
}

Ball Game::CreateBall() {
    return {GetRandomPosition(), BallDirection{GetRandomXDirection(), 1}};
}

int Game::GetRandomXDirection() {
    static std::mt19937 generator{std::random_device{}()};
    std::bernoulli_distribution coin(0.5);
    return coin(generator) ? 1 : -1;
}

Vector2 Game::GetRandomPosition() {
    static std::mt19937 generator{std::random_device{}()};
    std::uniform_real_distribution<float> distributionX(
        Constants::GameArea::X,
        Constants::GameArea::X + Constants::GameArea::Width - Constants::Ball::SquareSize);

    float y = Constants::GameArea::Y + Constants::GameArea::Height / 2.0f;
    return Vector2(distributionX(generator), y);
}

void Game::CheckBrickCollision() {
    bool collides = false;
    for (auto it = bricks.begin(); it != bricks.end(); ) {
        if (ball.CheckBrickCollision(*it)) {
            score += it->GetScore();
            it = bricks.erase(it);
            collides = true;
            if (it->GetScore() == 5 || it->GetScore() == 7) {
                ball.IncreaseSpeedPercentageBy(75.0f);
            }
            break;
        }
        ++it;
    }
    if (collides) {
        ball.BounceBallDown();
    }
}



void Game::WriteScore() {
    constexpr float margin = 5.0f;

    const float topRowY = Constants::GameArea::Y + Constants::Brick::YOffset;
    const float bottomY = topRowY - margin;
    const float textX = Constants::GameArea::X + margin;

    std::string text = std::to_string(score);
    if (text.size() < 3) {
        text.insert(0, 3 - text.size(), '0');
    }
    scoreFont->SetSize(48.0f);
    scoreFont->DrawText(renderer, text, textX, bottomY, white);
}

void Game::WriteCurrentBall() {
    constexpr float margin = 5.0f;
    const float bottomY = Constants::GameArea::Y + margin + static_cast<float>(scoreFont->GetHeight());
    scoreFont->DrawText(renderer, std::to_string(currentBall), 500.0f, bottomY, white);
}

void Game::WriteGameOver() {
    WriteTextCenter("Game Over", 48.0f, 500.0f);
    WriteTextCenter("Press SPACE to play again", 24.0f, 550.0f);
}

void Game::WriteTextCenter(const char* text, float size, float y) {
    scoreFont->SetSize(size);
    const float textWidth = scoreFont->MeasureTextWidth(text);
    const float x = Constants::GameArea::X + (Constants::GameArea::Width - textWidth) / 2.0f;
    scoreFont->DrawText(renderer, text, x, y, white);
}

Game::~Game() {
    bricks.clear();
    scoreFont.reset();
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}
