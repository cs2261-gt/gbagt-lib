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

//TODO: Add this function from Lab03
void fillScreen(volatile u16 color) {

}

void waitForVBlank() {
    while (REG_VCOUNT >= 160);
    while (REG_VCOUNT < 160);
}