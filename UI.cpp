// UI.cpp
// Created by manfed on 2025-12-19.
//

#include "asset_manager/asset_manager.h"
#include "UI.h"
#include "window.h"
using namespace std;

int settings_Enable = 0;

int UI_COLS = 0;
int UI_ROWS = 0;

std::vector<std::vector<std::vector<int>>> ui;

//===============================================
/**
 * This initializes the UI
 *
 * Run this after the after SDL inits
 */
void initUI()
{
    UI_COLS = screenW / pixelSize;
    UI_ROWS = screenH / pixelSize;

    ui.resize(OPTION_COUNT);

    for (int o = 0; o < OPTION_COUNT; ++o) {
        ui[o].resize(UI_COLS);
        for (int x = 0; x < UI_COLS; ++x) {
            ui[o][x].resize(UI_ROWS, 0);
        }
    }
}
//===============================================

//===============================================
/**
 * This function creates the pause menu
 */
void PauseUI()
{
    const int PAUSE_WIDTH  = 250;
    const int PAUSE_HEIGHT = 150;

    int startX = ((winW / pixelSize) - PAUSE_WIDTH) / 2;
    int startY = ((winH / pixelSize) - PAUSE_HEIGHT) / 2;

    for (int i = startX; i < startX + PAUSE_WIDTH; i++) {
        for (int j = startY; j < startY + PAUSE_HEIGHT; j++) {
            ui[OPTION_Pause][i][j] = 255;
        }
    }
}

//===============================================

//===============================================
/**
 * This function creates a test world right now (late will be part of creating a new world based on an algo)
*/
void UICreate ( int UIOption ) {

    if ( UIOption == OPTION_Pause ) {
        PauseUI();
    }

    for ( int c = 0 ; c < OPTION_COUNT ; c++ ) {
        for ( int i = 0 ; i < UI_COLS - 8 ; i++ ) {
            for ( int j = 0 ; j < UI_ROWS - 8 ; j++ ) {
                drawPixel(i * pixelSize,j * pixelSize,100,100,100,ui[c][i][j]) ;
            }
        }
    }

}
//===============================================

//===============================================
/**
 * This function figures out the logic to update the world
*/
void UIRemove ( ) {
    // Empty right now
    for ( int i = 0 ; i < UI_COLS - 1 ; i++ ) {
        for ( int j = 0 ; j < UI_ROWS - 1 ; j++ ) {
            ui[OPTION_Pause][i][j] = 0;
        }
    }

}
//===============================================
