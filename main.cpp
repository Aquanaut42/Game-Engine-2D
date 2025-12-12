#include <iostream>
#include "window.h"
#include "logic.h"

bool paused = false;
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

    worldUpdate();

    // Main loop
    while (running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {   
                running = false;    // Close the program when the window closes
            }

            // Handle input
            handleInput(event);
        }

        // Draw simulation
        windowLogic();

        SDL_Delay(simulationSpeed);  // Use toolbar-controlled speed
    }

    // Destroy the window
    cleanupWindow();

    return 0;
}
