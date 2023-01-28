#include "sprites.h"

// ---- Sprites ----

OBJ_ATTR shadowOAM[128];
AFFINE_MATRIX* affine = (AFFINE_MATRIX*) shadowOAM;

// Hides the specified sprite in the shadowOAM; Must DMA the shadowOAM into the OAM after calling this function
void hide(ANISPRITE* sprite) {
    sprite->attributes->attr0 = ATTR0_OM(HIDE);

} // hide

// Hides all sprites in the shadowOAM; Must DMA the shadowOAM into the OAM after calling this function
void hideSprites() {

    for (int i = 0; i < 128; i++) {
        shadowOAM[i].attr0 = ATTR0_OM(HIDE);
    
    } // for

} // hideSprites

// Chooses an affine matrix and sets its values
void setAffineMatrix(int matrix, u16 a, u16 b, u16 c, u16 d) {
    affine[matrix].a = a;
    affine[matrix].b = b;
    affine[matrix].c = c;
    affine[matrix].d = d;

} // setAffineMatrix

// DMAs the shadowOAM into OAM
void updateOAM() {
    DMANow(3, shadowOAM, OAM, 512);

} // updateOAM