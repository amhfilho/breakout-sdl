#include "FontLoader.h"

FontLoader::FontLoader(const std::string& path, float size) {
    if (!TTF_Init()) {
        SDL_Log("Error starting SDL3_ttf: %s", SDL_GetError());
        return;
    }

    const char* basePath = SDL_GetBasePath();
    const std::string fullPath = std::string(basePath ? basePath : "") + path;

    font = TTF_OpenFont(fullPath.c_str(), size);
    if (!font) {
        SDL_Log("Error loading font %s: %s", fullPath.c_str(), SDL_GetError());
    }
}

FontLoader::~FontLoader() {
    ClearTexture();
    if (font) {
        TTF_CloseFont(font);
    }
    TTF_Quit();
}

void FontLoader::ClearTexture() {
    if (texture) {
        SDL_DestroyTexture(texture);
        texture = nullptr;
    }
}

void FontLoader::DrawText(SDL_Renderer* renderer, const std::string& text, float x, float bottomY, const Color& color) {
    if (!font) {
        return;
    }

    if (!texture || text != cachedText || color.r != cachedColor.r || color.g != cachedColor.g ||
        color.b != cachedColor.b || color.a != cachedColor.a) {
        ClearTexture();
        const SDL_Color sdlColor{color.r, color.g, color.b, color.a};
        SDL_Surface* surface = TTF_RenderText_Blended(font, text.c_str(), text.size(), sdlColor);
        if (!surface) {
            SDL_Log("Error rendering text: %s", SDL_GetError());
            return;
        }
        texture = SDL_CreateTextureFromSurface(renderer, surface);
        SDL_DestroySurface(surface);
        if (!texture) {
            SDL_Log("Error creating text texture: %s", SDL_GetError());
            return;
        }
        cachedText = text;
        cachedColor = color;
    }

    SDL_FRect dst{x, bottomY - static_cast<float>(texture->h), static_cast<float>(texture->w),
                  static_cast<float>(texture->h)};
    SDL_RenderTexture(renderer, texture, nullptr, &dst);
}
