// interface.h
// Created by manfed on 2025-12-20.
//

#ifndef GAME_ENGINE_2D_INTERFACE_H
#define GAME_ENGINE_2D_INTERFACE_H

#include <vector>

enum UI_OPTION {
    OPTION_Pause = 0,
    OPTION_Settings,
    OPTION_Quit,
    OPTION_Buttons,
    OPTION_COUNT
};

enum BUTTONCODE {
    BUTTON_Quit = 1,
    BUTTON_COUNT
};

enum COLOUR_PAINT {
    COLOUR_BROWN1 = 1, // r:160 g:90 b:20
    COLOUR_BROWN2, // r:217 g:124 b: 7
    COLOUR_BROWN3, // r:254 g:188 b:110
    COLOUR_BROWN4, // r200 g: 100 b: 80
};

extern std::vector<std::vector<std::vector<int>>> userInterface;

void PauseUI();
void PauseUIButtons();

#endif //GAME_ENGINE_2D_INTERFACE_H
