#ifndef UI_H
#define UI_H

#include <vector>

enum UI_OPTION {
    OPTION_Pause = 0,
    OPTION_Settings,
    OPTION_Quit,
    OPTION_COUNT
};

extern int UI_COLS;
extern int UI_ROWS;

extern std::vector<std::vector<std::vector<int>>> ui;

extern int settings_Enable;

void initUI();
void UICreate(int UIOption);
void UIRemove();

#endif
