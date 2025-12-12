// window.cpp
#include "window.h"
#include "logic.h"
#include <iostream>

SDL_Window* window = nullptr;
SDL_Renderer* renderer = nullptr;

int screenCoordsX = 0;
int screenCoordsY = 0;

//===============================================
//  This functions initialises the window
//===============================================
bool initWindow(const char* title) {

    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        std::cerr << "SDL_Init Error: " << SDL_GetError() << "\n";
        return false;
    }

    window = SDL_CreateWindow(
        title,
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        WINDOW_WIDTH,
        WINDOW_HEIGHT,
        SDL_WINDOW_RESIZABLE//SDL_WINDOW_SHOWN
    );

    if (!window) {
        std::cerr << "SDL_CreateWindow Error: " << SDL_GetError() << "\n";
        SDL_Quit();
        return false;
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        std::cerr << "SDL_CreateRenderer Error: " << SDL_GetError() << "\n";
        SDL_DestroyWindow(window);
        SDL_Quit();
        return false;
    }

    return true;
}
//===============================================

//===============================================
//  This functions cleans the window by destroying it
//===============================================
void cleanupWindow() {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}
//===============================================

//===============================================
//  This functions draws a square in the coords
//===============================================
void drawSquare(int x, int y, int state) {
    
    if (x  >= WINDOW_WIDTH || y  >= WINDOW_HEIGHT
        || x < 0 || y < 0 ) {
        return; // Out of bounds
    }
    SDL_Rect rect = { x * pixelSize + screenCoordsX , y * pixelSize + screenCoordsY , pixelSize, pixelSize };
    if (state > 0 && state <= 100) {
        // Growing tree stages - shades of green
        int greenValue = 255 - (state * 100 / 100); // from 155 to 255
        SDL_SetRenderDrawColor(renderer, 34, greenValue, 34, 255);
    } else if (state > 100 && state <= 110) {
        // Burning tree stages - shades of red
        int redValue = 255 - ((state - 101) * 20); // from 255 to 55
        SDL_SetRenderDrawColor(renderer, redValue, 0, 0, 255);
    } else {
        // Dirt - brown
        SDL_SetRenderDrawColor(renderer, 139, 69, 19, 255);
    }
    
    SDL_RenderFillRect(renderer, &rect);
}
//===============================================

//===============================================
//  This function runs the main logic of the window
//
//  In other words it draws the entire world
//===============================================
void windowLogic( ) {

    for ( int i = 0 ; i < COLS ; i++ ) {
        for ( int j = 0 ; j < ROWS ; j++ ) {
            drawSquare( i, j, world[i][j] );
        }
    }
    
    SDL_RenderPresent(renderer);

}
//===============================================

//===============================================
//  This function handles arrows input
//===============================================
void handleInput(SDL_Event& e) {
    if (e.type == SDL_KEYDOWN) {
        switch (e.key.keysym.sym) {
            case SDLK_LEFT:
                screenCoordsX += 10;
                break;
            case SDLK_RIGHT:
                screenCoordsX -= 10;
                break;
            case SDLK_UP:
                screenCoordsY += 10;
                break;
            case SDLK_DOWN:
                screenCoordsY -= 10;
                break;
        }
    }

    // Clamp camera position inside the world
    if (screenCoordsX > 0) screenCoordsX = 0;
    if (screenCoordsY > 0) screenCoordsY = 0;

    if (screenCoordsX < WINDOW_WIDTH  - world_WIDTH)
        screenCoordsX = WINDOW_WIDTH  - world_WIDTH;
    if (screenCoordsY < WINDOW_HEIGHT - world_HEIGHT)
        screenCoordsY = WINDOW_HEIGHT - world_HEIGHT;
}

//===============================================
