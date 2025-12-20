#include <iostream>
#include "window.h"
#include "world.h"
#include "UserInterface.h"
#include "UI.h"

int simulationSpeed = 20; // Start with 200 ms per update

int main(int argc, char* argv[]) {

    // Create the window (With the title)
    if (!initWindow("Forest Fire Simulation")) {
        std::cerr << "Failed to initialize window\n";
        return 1;
    }

    // variables to control the start and the main loop
    bool running = true;
    SDL_Event event;

    // Initialize the UI, based on the screen size, so after SDL initialized
    initUI();

    worldCreate();

    // Main loop
    while (running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = false;    // Close the program when the window closes
            }

            // Handle input
            handleInput(event);
        }

        if ( settings_Enable == 1 ) {
            UICreate( OPTION_Pause );
        } else {
            UIRemove();
        }

        // Draw simulation
        windowDraw();

        //SDL_Delay(simulationSpeed);  // Use toolbar-controlled speed
    }

    // Destroy the window
    cleanupWindow();

    return 0;
}
