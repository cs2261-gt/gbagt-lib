#ifndef GBA_MODE3_H
#define GBA_MODE3_H

#include "gba.h"

#define SET_MODE3() (REG_DISPCTL = MODE(3) & BG2_ENABLE)

// Mode 3 Drawing Functions
void setPixel3(int col, int row, unsigned short color);
void drawRect3(int col, int row, int width, int height, volatile unsigned short color);
void fillScreen3(volatile unsigned short color);
void drawImage3(int col, int row, int width, int height, const unsigned short *image);
void drawFullscreenImage3(const unsigned short *image);
void waitForVBlank();

#endif