#include "mode4.h"

void drawImage4(int col, int row, int width, int height, const unsigned short *image) {
    for (int i = 0; i < height; i++) {
        DMANow(3, &image[OFFSET(0, i, width / 2)], &videoBuffer[OFFSET(col, row + i, SCREENWIDTH) / 2], width / 2);
    }
}

void setPixel4(int col, int row, unsigned char colorIndex) {
    volatile unsigned short pixelData = videoBuffer[OFFSET(col, row, SCREENWIDTH) / 2];
    if (col & 1) {
        pixelData &= 0x00FF;
        pixelData |= colorIndex << 8;
    } else {
        pixelData &= 0xFF00;
        pixelData |= colorIndex;
    }
    videoBuffer[OFFSET(col, row, SCREENWIDTH) / 2] = pixelData;
}

void drawRect4(int col, int row, int width, int height, volatile unsigned char colorIndex) {
    volatile unsigned short pixelData = colorIndex | (colorIndex << 8);
    for (int r = 0; r < height; r++) {
        // Ensure we don't DMA 0 copies
        if (width == 1) {
            setPixel4(col, row + r, colorIndex);
        } else if (width == 2) {
            setPixel4(col, row + r, colorIndex);
            setPixel4(col + 1, row + r, colorIndex);
        } else if ((col & 1) && (width & 1)) /* Odd width odd col */ {
            setPixel4(col, row + r, colorIndex);
            DMANow(3, &pixelData, &videoBuffer[OFFSET(col + 1, row + r, SCREENWIDTH) / 2], DMA_SOURCE_FIXED | (width - 1) / 2);
        } else if (width & 1) /* Even col odd width */ {
            DMANow(3, &pixelData, &videoBuffer[OFFSET(col, row + r, SCREENWIDTH) / 2], DMA_SOURCE_FIXED | (width - 1) / 2);
            setPixel4(col + width - 1, row + r, colorIndex);
        } else if (col & 1) /* Odd col even width */ {
            setPixel4(col, row + r, colorIndex);
            DMANow(3, &pixelData, &videoBuffer[OFFSET(col + 1, row + r, SCREENWIDTH) / 2], DMA_SOURCE_FIXED | (width - 2) / 2);
            setPixel4(col + width - 1, row + r, colorIndex);
        } else /* Even col even width */ {
            DMANow(3, &pixelData, &videoBuffer[OFFSET(col, row + r, SCREENWIDTH) / 2], DMA_SOURCE_FIXED | width / 2);
        }
    }
}

void fillScreen4(volatile unsigned char colorIndex) {
    volatile unsigned short pixelData = colorIndex | (colorIndex << 8);
    DMANow(3, &pixelData, videoBuffer, DMA_SOURCE_FIXED | (SCREENWIDTH * SCREENHEIGHT) / 2);
}

void drawFullscreenImage4(const unsigned short *image) {
    DMANow(3, image, videoBuffer, SCREENWIDTH * SCREENHEIGHT / 2);
}

void flipPage() {
    if (REG_DISPCTL & DISP_BACKBUFFER) {
        videoBuffer = BACKBUFFER;
    } else {
        videoBuffer = FRONTBUFFER;
    }
    REG_DISPCTL ^= DISP_BACKBUFFER;
}