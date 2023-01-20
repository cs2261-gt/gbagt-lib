#include "sprites.h"

// ---- Sprites ----
// Hides all sprites in the shadowOAM; Must DMA the shadowOAM into the OAM after calling this function
void hideSprites() {
    for (int i = 0; i < 128; i++) {
        shadowOAM[i].attr0 = oam.attr0.hide;
    }
}