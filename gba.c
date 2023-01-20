#include "gba.h"

// The start of the video memory
unsigned volatile short *videoBuffer = (unsigned short *)0x6000000;


// ---- Miscellaneous Functions ----
int collision(int colA, int rowA, int widthA, int heightA, int colB, int rowB, int widthB, int heightB) {
    return rowA <= rowB + heightB - 1 && rowA + heightA - 1 >= rowB && colA <= colB + widthB - 1 && colA + widthA - 1 >= colB;
}

void waitForVBlank() {
    while (SCANLINECOUNTER >= 160);
    while (SCANLINECOUNTER < 160);
}


// ---- DMA ----
// The start of DMA registers
DMA *dma = (DMA *)0x40000B0;

void DMANow(int channel, volatile const void *src, volatile void *dst, unsigned int cnt) {
    dma[channel].cnt = 0;
    dma[channel].src = src;
    dma[channel].dst = dst;
    dma[channel].cnt = cnt | DMA_ON;
}