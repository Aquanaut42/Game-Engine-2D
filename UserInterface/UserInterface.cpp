// UserInterface.cpp
// Created by manfed on 2025-12-17.
//

#include "UserInterface.h"
#include "../window.h"
#include "../fonts/fonts.h"
#include "../asset_manager/asset_manager.h"
#include "Interface.h"

#include <string>
#include <vector>

#define UWORD uint16_t

using namespace std;

int settings_Enable = 0;

int UI_COLS = 0;
int UI_ROWS = 0;

vector<std::vector<std::vector<int>>> userInterface;

const int BUTTON_FACE_HEIGHT = 13;

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
 * @return button width
 */
int button( int x, int y,int THICKNESS, std::string text) {

    int width = text.length() * 6 + 3;

    // ---- Thickness (draw first, behind the button) ----
    for (int t = 1; t <= THICKNESS; t++) {
        for (int i = 0; i < width; i++) {
            drawPixel((x + i) * pixelSize - pixelSize,     y * pixelSize + (BUTTON_FACE_HEIGHT + 1 + t) * pixelSize,            160, 90, 20, 255);
        }
        drawPixel(x * pixelSize - 2 * pixelSize,           y * pixelSize + (BUTTON_FACE_HEIGHT + 1 + t) * pixelSize - pixelSize,160, 90, 20, 255);
        drawPixel(x * pixelSize + (width - 1) * pixelSize, y * pixelSize + (BUTTON_FACE_HEIGHT + 1 + t) * pixelSize - pixelSize,160, 90, 20, 255);
    }

    // ---- Top & bottom border ----
    for (int i = 0; i < width; i++) {
        drawPixel((x + i) * pixelSize - pixelSize, y * pixelSize, 217, 124, 7, 255);

        drawPixel((x + i) * pixelSize - pixelSize, y * pixelSize + (BUTTON_FACE_HEIGHT + 1) * pixelSize, 217, 124, 7, 255);
    }

    // ---- Left & right border ----
    for (int j = 0; j < BUTTON_FACE_HEIGHT; j++) {
        drawPixel(x * pixelSize - pixelSize * 2, (y + j) * pixelSize + pixelSize, 217, 124, 7, 255);

        drawPixel(x * pixelSize + text.length() * 6 * pixelSize + 2 * pixelSize, (y + j) * pixelSize + pixelSize, 217, 124, 7, 255);
    }

    // ---- Face fill ----
    for (int i = 0; i < width; i++) {
        for (int j = 1; j <= BUTTON_FACE_HEIGHT; j++) {
            drawPixel((x + i) * pixelSize - pixelSize, y * pixelSize + j * pixelSize, 254, 188, 110, 255);
        }
    }

    // ---- Text (unchanged position) ----
    DrawStringFont12(x, y + 2, text.c_str(), 255);

    return width;
}
//===============================================

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

    userInterface.resize(OPTION_COUNT);

    for (int o = 0; o < OPTION_COUNT; ++o) {
        userInterface[o].resize(UI_COLS);
        for (int x = 0; x < UI_COLS; ++x) {
            userInterface[o][x].resize(UI_ROWS, 0);
        }
    }

    for ( int c = 0 ; c < OPTION_COUNT - 1 ; c++ ) {
        for ( int i = 1 ; i < UI_COLS - 8 ; i++ ) {
            for ( int j = 1 ; j < UI_ROWS - 8 ; j++ ) {
                userInterface[c][i][j] = 0;
            }
        }
    }
}
//===============================================

//===============================================
/**
 * This function creates a test world right now (late will be part of creating a new world based on an algo)
*/
void UICreate ( int UIOption ) {

    // Create the interface
    if ( UIOption == OPTION_Pause ) {
        PauseUI();
    }

    int jitter = 1; // for some randomness
    // Draw the interface
    for ( int c = 0 ; c < OPTION_COUNT - 1 ; c++ ) {
        for ( int i = 1 ; i < UI_COLS - 8 ; i++ ) {
            for ( int j = 1 ; j < UI_ROWS - 8 ; j++ ) {

                jitter = rand() % 10;
                if ( userInterface[c][i][j] == COLOUR_BROWN1 ) {
                    drawPixel(i * pixelSize,j * pixelSize,160,90, 20, 255) ;
                } else if ( userInterface[c][i][j] == COLOUR_BROWN2 ) {
                    drawPixel(i * pixelSize,j * pixelSize,217,124,7,  255) ;
                } else if ( userInterface[c][i][j] == COLOUR_BROWN4 ) {
                    drawPixel(i * pixelSize,j * pixelSize,200 + jitter ,150 + jitter,100 + jitter,255) ;
                }

            }
        }
    }

    // Draw the buttons
    if ( UIOption == OPTION_Pause ) {
        PauseUIButtons();
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
            userInterface[OPTION_Pause][i][j] = 0;
        }
    }

}
//===============================================
