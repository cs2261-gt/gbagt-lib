#include "mode4.h"
#include "font.h"

// Sets a pixel in mode 4
void setPixel4(int x, int y, u8 colorIndex) {
    // TODO Fill this function in from your Lab06
}

// Draws a rectangle in mode 4
void drawRect4(int x, int y, int width, int height, volatile u8 colorIndex) {
    // TODO Fill this function in from your Lab06
}

// Fills the screen in mode 4 using specified palette index
void fillScreen4(volatile u8 colorIndex) {
    // TODO Fill this function in from your Lab06
}

// Draws an image in mode 4
void drawImage4(int x, int y, int width, int height, const u16* image) {
    // TODO Fill this function in from your Lab06
}

// Draws a full-screen image in mode 4
void drawFullscreenImage4(const u16* image) {
    // TODO Fill this function in from your Lab06
}

// Draws the specified character at the specified location in Mode 4
void drawChar4(int x, int y, char ch, u8 colorIndex) {
    for (int c = 0; c < 6; c++) {
        for (int r = 0; r < 8; r++) {
            if (fontdata_6x8[(48 * ch + c + 6 * r)]) setPixel4(x + c, y + r, colorIndex);
        }
    }
}

// Draws the specified string at the specified location in Mode 3
void drawString4(int x, int y, char* str, u8 colorIndex) {
    while (*str) {
        drawChar4(x, y, *str, colorIndex);
        str++;
        x += 6;
    }
}

// Flips page being displayed and page being drawn to
void flipPages() {
    if (REG_DISPCTL & DISP_BACKBUFFER) {
        videoBuffer = BACKBUFFER;
    } else {
        videoBuffer = FRONTBUFFER;
    }
    REG_DISPCTL ^= DISP_BACKBUFFER;
}