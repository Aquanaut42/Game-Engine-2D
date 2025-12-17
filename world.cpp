// world.cpp
#include "world.h"
#include "asset_manager/asset_manager.h"
#include <iostream>
using namespace std;

int world[LAYER_COUNT][COLS][ROWS] = {}; // define the world

//===============================================
/**
 * This function creates a test world right now (late will be part of creating a new world based on an algo)
*/
void worldCreate ( ) {

    for ( int i = 0 ; i < COLS - 1 ; i++ ) {
        for ( int j = 0 ; j < ROWS - 1 ; j++ ) {
            world[LAYER_GROUND][i][j] = rand() % 200 + 55;
        }
    }

}
//===============================================

//===============================================
/**
 * This function figures out the logic to update the world
*/
void worldUpdate ( ) {
    // Empty right now
    for ( int i = 0 ; i < COLS - 1 ; i++ ) {
        for ( int j = 0 ; j < ROWS - 1 ; j++ ) {

        }
    }

}
//===============================================
