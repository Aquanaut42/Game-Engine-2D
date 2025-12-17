// window.cpp
#include "window.h"
#include "world.h"
#include "asset_manager/asset_manager.h"
#include <iostream>

SDL_Window* window = nullptr;
SDL_Renderer* renderer = nullptr;

int screenCoordsX = 0;
int screenCoordsY = 0;

int winW = WINDOW_WIDTH;
int winH = WINDOW_HEIGHT;

//===============================================
/**
 *  This functions initialises the window
 */
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
        SDL_WINDOW_RESIZABLE
    );

    // Set the maximum window size to the size of the world ( full screen can still be too big )
    SDL_SetWindowMaximumSize(window, COLS*pixelSize, ROWS*pixelSize);

    if (!window) {
        std::cerr << "SDL_CreateWindow Error: " << SDL_GetError() << "\n";
        SDL_Quit();
        return false;
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    // Give the option to blend several colour
    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);

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
/**
 *  This functions cleans the window by destroying it
 */
void cleanupWindow() {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}
//===============================================

//===============================================
/**
 * Draw a pixel at the given grid coordinates.
 *
 * @param x Grid X coordinate
 * @param y Grid Y coordinate
 * @param r Red   (0–255)
 * @param g Green (0–255)
 * @param b Blue  (0–255)
 * @param state Alpha/opacity (0–255)
 *
 * Draws a single pixel-sized rectangle at (x, y) using the renderer.
 */
void drawPixel(int x, int y, int r, int g, int b, int state) {

    // the pixel, it's size, shape, colour and transparancy
    SDL_Rect rect = { x, y, pixelSize, pixelSize };
    SDL_SetRenderDrawColor(renderer, r, g, b, state);

    // Draw the pixel
    SDL_RenderFillRect(renderer, &rect);
}
//===============================================

//===============================================
/**
 * This function redraws the window
 *
 * In other words it draws the entire world
 */
void windowDraw( ) {

    // Clear the window
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    // Draw the whole world
    for ( int i = 0 ; i < COLS ; i++ ) {
        for ( int j = 0 ; j < ROWS ; j++ ) {
            drawPixel( i * pixelSize + screenCoordsX, j * pixelSize + screenCoordsY, 0, 0, 200, world[LAYER_GROUND][i][j] );
        }
    }

    SDL_RenderPresent(renderer);

}
//===============================================

//===============================================
/**
 *   This function handles user input and updates the screen size
 */
void handleInput(SDL_Event& e) {

    const Uint8* state = SDL_GetKeyboardState(NULL);

    if (state[SDL_SCANCODE_LEFT]) {
        screenCoordsX += pixelSize / 2;
    }
    if (state[SDL_SCANCODE_RIGHT]) {
        screenCoordsX -= pixelSize / 2;
    }
    if (state[SDL_SCANCODE_UP]) {
        screenCoordsY += pixelSize / 2;
    }
    if (state[SDL_SCANCODE_DOWN]) {
        screenCoordsY -= pixelSize / 2;
    }

    // Updates the window size variable when the window size changes
    if (e.type == SDL_WINDOWEVENT && e.window.event == SDL_WINDOWEVENT_SIZE_CHANGED) {
        winW = e.window.data1;
        winH = e.window.data2;
    }

    // Clamp camera position inside the world
    if (screenCoordsX > 0) screenCoordsX = 0;
    if (screenCoordsY > 0) screenCoordsY = 0;

    if (screenCoordsX < winW  - world_WIDTH)
        screenCoordsX = winW  - world_WIDTH;
    if (screenCoordsY < winH - world_HEIGHT)
        screenCoordsY = winH - world_HEIGHT;
}
//===============================================
