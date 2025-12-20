// world.h
#ifndef WORLD_H
    #define WORLD_H

    // Pixel size
    const int pixelSize = 5;

    // Size of the screen and the size of the world
    const int WINDOW_WIDTH  = 1500;
    const int WINDOW_HEIGHT = 1000;

    // For test the world is 3 times larger than the screen default
    const int COLS = WINDOW_WIDTH  / pixelSize * 3;
    const int ROWS = WINDOW_HEIGHT / pixelSize * 3;

    const int world_WIDTH  = COLS * pixelSize;
    const int world_HEIGHT = ROWS * pixelSize;

    enum WorldLayer {
        LAYER_GROUND = 0,
        LAYER_GROUND_DETAILS,
        LAYER_LOW_PROPS,
        LAYER_MID_PROPS,
        LAYER_HIGH_PROPS,
        LAYER_EFFECTS,
        LAYER_ENTITIES,
        LAYER_HITBOX,
        LAYER_FOG,
        LAYER_LIGHT,
        LAYER_LEAVES,
        LAYER_SPEECH,
        LAYER_BORDER,
        LAYER_TRIGGER,
        LAYER_COUNT   // for array sizing
    };

    // World[layers][colloms][rows]
    extern int world[LAYER_COUNT][COLS][ROWS]; // initialize the world

    // Toolbar and simulation control
    extern bool paused;          // Pause/play toggle
    extern int simulationSpeed;  // Delay in milliseconds per update
    const int TOOLBAR_HEIGHT = 55; // Height of the top toolbar

    void worldUpdate ( );
    void worldCreate ( );

    extern int screenW;
    extern int screenH;

#endif
