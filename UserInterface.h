// User_Interface.h
// Created by manfed on 2025-12-17.
//

#ifndef GAME_ENGINE_2D_USER_INTERFACE_H
#define GAME_ENGINE_2D_USER_INTERFACE_H
#include <cstdint>
#include <string>

extern const uint8_t Font8_Table[];

void DrawCharFont8(int x, int y, char c, int state);
void DrawCharFont12(int x, int y, char c, int state);
void DrawStringFont8(int x, int y, const char *s, int state);
void DrawStringFont12(int x, int y, const char *s, int state);

bool button( int x, int y, std::string text);

#endif //GAME_ENGINE_2D_USER_INTERFACE_H
