#ifndef GBA_MODE3_H
#define GBA_MODE3_H

#include "gba.h"

#define SET_MODE3() (REG_DISPCTL = MODE(3) & BG2_ENABLE) // Sets REG_DISPCTL to mode 3

// Sets a pixel in mode 3
void setPixel3(int x, int y, unsigned short color) {
    videoBuffer[OFFSET(x, y, SCREENWIDTH)] = color;
}
#define SET_PIXEL3(x, y, color) (videoBuffer[OFFSET(x, y, SCREENWIDTH)] = color)

void setPixel3(int x, int y, unsigned short color);
void drawRect3(int x, int y, int width, int height, volatile unsigned short color);
void fillScreen3(volatile unsigned short color);
void drawImage3(int x, int y, int width, int height, const unsigned short *image);
void drawFullscreenImage3(const unsigned short *image);

#endif