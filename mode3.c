#include "mode3.h"

void setPixel3(int col, int row, unsigned short color) {
    videoBuffer[OFFSET(col, row, SCREENWIDTH)] = color;
}

void drawRect3(int col, int row, int width, int height, volatile unsigned short color) {
    for (int r = 0; r < height; r++) {
        DMANow(3, &color, &videoBuffer[OFFSET(col, row + r, SCREENWIDTH)], DMA_SOURCE_FIXED | width);
    }
}

void fillScreen3(volatile unsigned short color) {
    unsigned short c = color;
    DMANow(3, &c, videoBuffer, DMA_SOURCE_FIXED | (SCREENWIDTH * SCREENHEIGHT));
}

void drawImage3(int col, int row, int width, int height, const unsigned short *image) {
    for (int r = 0; r < height; r++) {
        DMANow(3, &image[OFFSET(0, r, width)], &videoBuffer[OFFSET(col, row + r, SCREENWIDTH)], width);
    }
}

void drawFullscreenImage3(const unsigned short *image) {
    DMANow(3, image, videoBuffer, SCREENWIDTH * SCREENHEIGHT);
}