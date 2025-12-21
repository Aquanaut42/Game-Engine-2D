// window.h
#ifndef WINDOW_H
#define WINDOW_H

#include <SDL2/SDL.h>
#include "world.h"

// Declare extern so other files can access these
extern SDL_Window* window;
extern SDL_Renderer* renderer;

// Declare your init and cleanup functions
bool initWindow( const char* title );
void cleanupWindow();
void drawPixel(int x, int y, int r, int g, int b, int state);
void windowDraw();
void handleInput(SDL_Event& e);

// The size of the window
extern int winW;
extern int winH;

// The coords of the screen compared to the world
extern int screenCoordsX;
extern int screenCoordsY;
// Is the user resizing the screen
extern bool isResizing;

#endif
