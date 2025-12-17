// asset_manager.h
//#pragma once
#include <SDL.h>
#include <string>
#include <unordered_map>

// Simple asset manager for loading and caching textures
class AssetManager {
public:
    // Must be called once after renderer creation
    static void init(SDL_Renderer* renderer);

    // Load (or retrieve cached) texture
    static SDL_Texture* getTexture(const std::string& path);

    // Free all loaded assets
    static void cleanup();

private:
    static SDL_Renderer* s_renderer;
    static std::unordered_map<std::string, SDL_Texture*> s_textures;
};


// asset_manager.cpp
#include "asset_manager.h"
#include <iostream>

SDL_Renderer* AssetManager::s_renderer = nullptr;
std::unordered_map<std::string, SDL_Texture*> AssetManager::s_textures;

void AssetManager::init(SDL_Renderer* renderer) {
    s_renderer = renderer;
}

SDL_Texture* AssetManager::getTexture(const std::string& path) {
    // Already loaded
    auto it = s_textures.find(path);
    if (it != s_textures.end()) {
        return it->second;
    }

    if (!s_renderer) {
        std::cerr << "AssetManager not initialised!\n";
        return nullptr;
    }

    SDL_Surface* surface = SDL_LoadBMP(path.c_str());
    if (!surface) {
        std::cerr << "SDL_LoadBMP failed: " << SDL_GetError() << '\n';
        return nullptr;
    }

    SDL_Texture* texture = SDL_CreateTextureFromSurface(s_renderer, surface);
    SDL_FreeSurface(surface);

    if (!texture) {
        std::cerr << "SDL_CreateTextureFromSurface failed: " << SDL_GetError() << '\n';
        return nullptr;
    }

    SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_BLEND);

    s_textures[path] = texture;
    return texture;
}

void AssetManager::cleanup() {
    for (auto& pair : s_textures) {
        SDL_DestroyTexture(pair.second);
    }
    s_textures.clear();
}

/*
USAGE:

// After renderer creation
AssetManager::init(renderer);

// Load once, reuse everywhere
SDL_Texture* overlay = AssetManager::getTexture("assets/overlay.bmp");

// Draw in windowDraw()
SDL_Rect dst = { 0, 0, winW, winH };
SDL_RenderCopy(renderer, overlay, nullptr, &dst);

// On shutdown
AssetManager::cleanup();
*/
