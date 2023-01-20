#ifndef GBA_MODE4_H
#define GBA_MODE4_H

#include "gba.h"

#define FRONTBUFFER ((unsigned short *)0x6000000)
#define BACKBUFFER  ((unsigned short *)0x600A000)

void flipPage();
void setPixel4(int col, int row, unsigned char colorIndex);
void drawRect4(int col, int row, int width, int height, volatile unsigned char colorIndex);
void fillScreen4(volatile unsigned char colorIndex);
void drawImage4(int col, int row, int width, int height, const unsigned short *image);
void drawFullscreenImage4(const unsigned short *image);

#endif