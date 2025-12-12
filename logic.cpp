// logic.cpp
#include "logic.h"
#include <iostream>
using namespace std;

int world[COLS][ROWS] = {}; // define the world

//===============================================
//  This function figures out the logic to update the world
//===============================================
void worldUpdate ( ) {

    for ( int i = 1 ; i < COLS - 1 ; i++ ) {
        for ( int j = 1 ; j < ROWS - 1 ; j++ ) {
            if ( rand() % 101 < 25 ) { // 25% chance to have a green spot
                world[i][j] = 1;
            }
        }
    }
    
}
//===============================================
