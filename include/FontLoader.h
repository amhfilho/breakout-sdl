#pragma once

#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <string>

#include "Colors.h"

// Loads a TTF font and draws text with it. The rendered texture is cached
// and only rebuilt when the text changes.
class FontLoader {
public:
    // path is relative to the executable's directory
    FontLoader(const std::string& path, float size);
    ~FontLoader();

    FontLoader(const FontLoader&) = delete;
    FontLoader& operator=(const FontLoader&) = delete;

    bool IsLoaded() const { return font != nullptr; }

    int GetHeight() const { return font ? TTF_GetFontHeight(font) : 0; }

    // Changes the point size used by subsequent DrawText calls
    void SetSize(float size);

    // Draws text with its bottom edge at bottomY
    void DrawText(SDL_Renderer* renderer, const std::string& text, float x, float bottomY, const Color& color);

    float GetTextureWidth() const;

    // Width in pixels the text would occupy at the current size
    float MeasureTextWidth(const std::string& text) const;

private:
    TTF_Font* font = nullptr;
    SDL_Texture* texture = nullptr;
    std::string cachedText;
    Color cachedColor{0, 0, 0};

    float textureWidth;
    float textureHeight;

    void ClearTexture();
};
