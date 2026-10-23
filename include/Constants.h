//
// Created by Filho, Antonio on 21/10/2026.
//

#pragma once

namespace Constants {
    namespace Window {
        inline constexpr const char* Title = "SDL3 Breakout";
        inline constexpr int Width = 700;
        inline constexpr int Height = 900;
    }

    namespace GameArea {
        inline constexpr float X = 10.0f;
        inline constexpr float Y = 20.0f;
        inline constexpr float Width = Window::Width - 20.0f;
        inline constexpr float Height = Window::Height - 20.0f;
    }

    namespace Brick {
        inline constexpr float Width = 52.0f;
        inline constexpr float Height = 10.0f;
        inline constexpr float XOffset = 0.0f;
        inline constexpr float YOffset = 150.0f;
        inline constexpr float XSpacing = 5.0f;
        inline constexpr float YSpacing = 5.0f;
    }

    namespace Paddle {
        inline constexpr float Width = 40.0f;
        inline constexpr float Height = 10.0f;
        inline constexpr float InitialX = GameArea::X + (GameArea::Width - Width) / 2.0f;
        inline constexpr float InitialY = 800.0f;
        inline constexpr float Speed = 300.0f;
    }
}
