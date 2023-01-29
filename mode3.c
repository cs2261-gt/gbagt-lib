#include "mode3.h"

// Draws a rectangle in mode 3
void drawRect3(int x, int y, int width, int height, volatile unsigned short color) {
    for (int r = 0; r < height; r++) {
        DMANow(3, &color, &videoBuffer[OFFSET(x, y + r, SCREENWIDTH)], DMA_SOURCE_FIXED | width);
    }
}

// Fills the screen in mode 3
void fillScreen3(volatile unsigned short color) {
    unsigned short c = color;
    DMANow(3, &c, videoBuffer, DMA_SOURCE_FIXED | (SCREENWIDTH * SCREENHEIGHT));
}

// Draws an image in mode 3
void drawImage3(int x, int y, int width, int height, const unsigned short *image) {
    for (int r = 0; r < height; r++) {
        DMANow(3, &image[OFFSET(0, r, width)], &videoBuffer[OFFSET(x, y + r, SCREENWIDTH)], width);
    }
}

// Draws a full-screen image in mode 3
void drawFullscreenImage3(const unsigned short *image) {
    DMANow(3, image, videoBuffer, SCREENWIDTH * SCREENHEIGHT);
}