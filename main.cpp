#include <iostream>
#include "window.h"
#include "world.h"
#include "UserInterface/UserInterface.h"
#include "UserInterface/Interface.h"
#include "handleInput.h"

int simulationSpeed = 20; // Start with 200 ms per update

bool runningState = true; // If the main loop is running

int main(int argc, char* argv[]) {

    // Create the window (With the title)
    if (!initWindow("Forest Fire Simulation")) {
        std::cerr << "Failed to initialize window\n";
        return 1;
    }

    // variables to control the start and the main loop
    SDL_Event event;

    // Initialize the UI, based on the screen size, so after SDL initialized
    initUI();

    worldCreate();

    // Main loop
    while (runningState) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                runningState = false;    // Close the program when the window closes
            }

            // Handle input
            handleInput(event);
        }

        // Update the mouse possition
        mouseTrack();

        if ( settings_Enable == 1 ) {
            // Pause menu
            UICreate( OPTION_Pause );
        } else {
            // main game
        }

        // Draw simulation
        windowDraw();

        //SDL_Delay(simulationSpeed);  // Use toolbar-controlled speed
    }

    // Destroy the window
    cleanupWindow();

    return 0;
}
