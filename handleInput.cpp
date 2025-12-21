// handleInput.cpp
// Created by manfed on 2025-12-21.
//

#include <SDL_events.h>
#include "UserInterface/UserInterface.h"
#include "window.h"

//===============================================
bool mousePressed = false;
int mouseX = 0;
int mouseY = 0;
/**
 *   This function handles user input and updates the screen size
 */
void handleInput(SDL_Event& e) {

    // Detect mouse press
    if (e.type == SDL_MOUSEBUTTONDOWN &&
        e.button.button == SDL_BUTTON_LEFT)
    {
        mousePressed = true;
        mouseX = e.button.x;
        mouseY = e.button.y;
    }

    // Detect mouse unpress
    if (e.type == SDL_MOUSEBUTTONUP &&
        e.button.button == SDL_BUTTON_LEFT)
    {
        mousePressed = false;
    }

    // Detect keyboard press
    const Uint8* state = SDL_GetKeyboardState(NULL);

    // Move character
    if ( !settings_Enable ) {
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
    }

    //Get settings window
    if (e.type == SDL_KEYDOWN && e.key.repeat == 0) {
        if (e.key.keysym.scancode == SDL_SCANCODE_ESCAPE) {
            settings_Enable = !settings_Enable;
            if (settings_Enable == 0) {
                UIRemove();
            }
        }
    }

    // Updates the window size variable when the window size changes
    if (e.type == SDL_WINDOWEVENT) {
        if (e.window.event == SDL_WINDOWEVENT_RESIZED) {
            isResizing = true;
            winW = e.window.data1;
            winH = e.window.data2;
        }

        if (e.window.event == SDL_WINDOWEVENT_SIZE_CHANGED) {
            winW = e.window.data1;
            winH = e.window.data2;
        }

        if (e.window.event == SDL_WINDOWEVENT_EXPOSED) {
            isResizing = false;
        }
    }

    // Clamp camera position inside the world
    if (!isResizing) {
        if (screenCoordsX > 0) screenCoordsX = 0;
        if (screenCoordsY > 0) screenCoordsY = 0;

        if (screenCoordsX < winW - world_WIDTH)
            screenCoordsX = winW - world_WIDTH;
        if (screenCoordsY < winH - world_HEIGHT)
            screenCoordsY = winH - world_HEIGHT;
    }
}
//===============================================
