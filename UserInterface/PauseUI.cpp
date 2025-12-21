// PauseUI.cpp
// Created by manfed on 2025-12-20.
//

#include "PauseUI.h"
#include "Interface.h"
#include "../window.h"
#include "../world.h"
#include "UserInterface.h"

#include <vector>

const int PAUSE_WIDTH  = 250;
const int PAUSE_HEIGHT = 150;

const int startX = ((winW / pixelSize) - PAUSE_WIDTH) / 2;
const int startY = ((winH / pixelSize) - PAUSE_HEIGHT) / 2;

//===============================================
void PauseUIButtons () {

    std::string quitStr = "quit";
    int quitWidth = quitStr.length() * 6 + 3;

    const int quitStartX = (PAUSE_WIDTH / 2) - (quitWidth / 2) + startX;
    const int quitStartY = startY + PAUSE_HEIGHT - ( (PAUSE_HEIGHT - 5 * pixelSize) / 5 );

    button( quitStartX, quitStartY, "Quit");

    for (int i = startX; i < startX + PAUSE_WIDTH; i++) {
        for (int j = startY; j < startY + PAUSE_HEIGHT; j++) {

            // Button quit
            if ( i >= quitStartX && i < quitStartX + quitWidth &&
                 j >= quitStartY && j < quitStartY + BUTTON_FACE_HEIGHT) {
                userInterface[OPTION_Buttons][i][j] = BUTTON_Quit;
            }
        }
    }

}
//===============================================

//===============================================
/**
 * This function creates the pause menu
 */
void PauseUI( )
{
    for (int i = startX; i < startX + PAUSE_WIDTH; i++) {
        for (int j = startY; j < startY + PAUSE_HEIGHT; j++) {
            if ( i == startX || i == startX + PAUSE_WIDTH - 1 ||
                 j == startY || j == startY + PAUSE_HEIGHT - 1) {
                userInterface[OPTION_Pause][i][j] = COLOUR_BROWN1;
            } else {
                userInterface[OPTION_Pause][i][j] = COLOUR_BROWN4;
            }
        }
    }
}
//===============================================