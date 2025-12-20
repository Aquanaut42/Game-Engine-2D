// User_Interface.cpp
// Created by manfed on 2025-12-17.
//

#include "UserInterface.h"
#include "window.h"
#include "fonts/fonts.h"

#include <cstdint>
#include <string>

#define UWORD   uint16_t

//===============================================
/**
 *
 * @param Xpoint x
 * @param Ypoint y
 * @param Acsii_Char
 * @param state int
 * @return
 */
void DrawCharfont8(int x, int y, char c, int state)
{
    if (c < ' ' || c > '~') return;

    // Each character is 8 bytes tall
    uint16_t offset = (c - ' ') * 8;
    const uint8_t *glyph = &Font8_Table[offset];

    for (int row = 0; row < 8; row++) {
        uint8_t bits = glyph[row];

        for (int col = 0; col < 5; col++) {
            if (bits & (1 << (7 - col))) {
                drawPixel( (x + col) * pixelSize, (y + row) * pixelSize, 100, 100, 100, state);
            }
        }
    }
}
//===============================================
//===============================================
/**
 *
 * @param Xpoint x
 * @param Ypoint y
 * @param Acsii_Char
 * @param state int
 * @return
 */
void DrawCharfont12(int x, int y, char c, int state)
{
    if (c < ' ' || c > '~') return;

    // Each character is 8 bytes tall
    uint16_t offset = (c - ' ') * 12;
    const uint8_t *glyph = &Font12_Table[offset];

    for (int row = 0; row < 12; row++) {
        uint8_t bits = glyph[row];

        for (int col = 0; col < 7; col++) {
            if (bits & (1 << (7 - col))) {
                drawPixel( (x + col) * pixelSize, (y + row) * pixelSize, 100, 100, 100, state);
            }
        }
    }
}
//===============================================

//===============================================
/** This Function draws a string
 *
 * @param Xstart
 * @param Ystart
 * @param pString
 * @param Font
 * @param Color_Foreground
 * @param Color_Background
 */
void DrawStringFont12(int x, int y, const char *s, int state)
{
    while (*s) {
        DrawCharfont12(x, y, *s, state);
        x += 6; // 5 pixels + 1 space
        s++;
    }
}
//===============================================

//===============================================
/** This Function draws a string
 *
 * @param Xstart
 * @param Ystart
 * @param pString
 * @param Font
 * @param Color_Foreground
 * @param Color_Background
 */
void DrawStringFont8(int x, int y, const char *s, int state)
{
    while (*s) {
        DrawCharfont8(x, y, *s, state);
        x += 6; // 5 pixels + 1 space
        s++;
    }
}
//===============================================

//===============================================
/** This function creates a wooden button with the text at x, y
 *  returns true if success, else false
 *
 * @param text
 * @param x
 * @param y
 * @return bool
 */
bool button( int x, int y, std::string text) {
    const int FACE_HEIGHT = 13;
    const int THICKNESS   = 2;   // controls how “thick” the button looks

    int width = text.length() * 6 + 3;

    // ---- Thickness (draw first, behind the button) ----
    for (int t = 1; t <= THICKNESS; t++) {
        for (int i = 0; i < width; i++) {
            drawPixel((x + i) * pixelSize - pixelSize,     y * pixelSize + (FACE_HEIGHT + 1 + t) * pixelSize,            160, 90, 20, 255);
        }
        drawPixel(x * pixelSize - 2 * pixelSize,           y * pixelSize + (FACE_HEIGHT + 1 + t) * pixelSize - pixelSize,160, 90, 20, 255);
        drawPixel(x * pixelSize + (width - 1) * pixelSize, y * pixelSize + (FACE_HEIGHT + 1 + t) * pixelSize - pixelSize,160, 90, 20, 255);
    }

    // ---- Top & bottom border ----
    for (int i = 0; i < width; i++) {
        drawPixel((x + i) * pixelSize - pixelSize, y * pixelSize, 217, 124, 7, 255);

        drawPixel((x + i) * pixelSize - pixelSize, y * pixelSize + (FACE_HEIGHT + 1) * pixelSize, 217, 124, 7, 255);
    }

    // ---- Left & right border ----
    for (int j = 0; j < FACE_HEIGHT; j++) {
        drawPixel(x * pixelSize - pixelSize * 2, (y + j) * pixelSize + pixelSize, 217, 124, 7, 255);

        drawPixel(x * pixelSize + text.length() * 6 * pixelSize + 2 * pixelSize, (y + j) * pixelSize + pixelSize, 217, 124, 7, 255);
    }

    // ---- Face fill ----
    for (int i = 0; i < width; i++) {
        for (int j = 1; j <= FACE_HEIGHT; j++) {
            drawPixel((x + i) * pixelSize - pixelSize, y * pixelSize + j * pixelSize, 254, 188, 110, 255);
        }
    }

    // ---- Text (unchanged position) ----
    DrawStringFont12(x, y + 2, text.c_str(), 255);

    return true;
}
//===============================================