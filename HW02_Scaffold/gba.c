#include "gba.h"

volatile unsigned short* videoBuffer = (volatile unsigned short*) 0x6000000;

void drawHorizontalLine(int y, int x1, int x2, volatile u16 color) {
    for (int i = x1; i <= x2; i++) {
        setPixel(i, y, color);
    }
}

void drawVerticalLine(int x, int y1, int y2, volatile u16 color) {
    for (int i = y1; i <= y2; i++) {
        setPixel(x, i, color);
    }
}

void drawRectangle(int x, int y, int width, int height, volatile u16 color) {
    for (int i = 0; i < width; i++) {
        for (int j = 0; j < height; j++) {
            setPixel(x + i, y + j, color);
        }
    }
}

void fillScreen(volatile u16 color) {
    for (int i = 0; i < (240*160); i++){
        videoBuffer[i] = color;
    }
}

void waitForVBlank() {
    while (REG_VCOUNT >= 160);
    while (REG_VCOUNT < 160);
}

int collision(int x1, int y1, int width1, int height1, int x2, int y2, int width2, int height2) {
        return ((y1 < y2 + height2)
        && (y1 + height1 > y2)
        && (x1 < x2 + width2)
        && (x1 + width1 > x2)); 
}