#ifndef GBA_SPRITES_H
#define GBA_SPRITES_H

#include "gba.h"

// Sprite Palette
#define SPRITE_PALETTE ((u16*) 0x5000200)

// Object Attribute Memory
#define OAM ((OBJ_ATTR*) 0x7000000)
extern OBJ_ATTR shadowOAM[];
extern AFFINE_MATRIX* affine;

// Sprite Constants
#define XPOSMASK 0xFF
#define YPOSMASK 0x1FF
#define TILEMASK 0x3FF

// Attribute 0
#define ATTR0_SPRITEX(x)   ((x) & XPOSMASK) // Row
#define ATTR0_OM(mode)     (((mode) & 3) << 8) // Object Mode
enum MODE { REGULAR, AFFINE, HIDE, DOUBLEAFFINE }; // Object Mode Options
#define ATTR0_ALPHA        (1 << 10) // Enable Alpha Blending
#define ATTR0_WINDOW       (1 << 11) // Enable Object Window Mode
#define ATTR0_MOSAIC       (1 << 12) // Enable Mosaic Effect
#define ATTR0_8BPP         (1 << 13) // 8 Bits Per Pixel
#define ATTR0_SHAPE(shape) (((shape) & 3) << 14) // Shape
enum SHAPE { SQUARE, WIDE, TALL }; // Shape Options (See Sprite Dimension Chart)
                                                
// Attribute 1
#define ATTR1_SPRITEY(y)      ((y) & YPOSMASK) // Column
#define ATTR1_HFLIP           (1 << 12) // Horizontal Flip
#define ATTR1_VFLIP           (1 << 13) // Vertical Flip
#define ATTR1_AFFINE(matrix)  (((matrix) & 31) << 9)
#define ATTR1_SIZE(size)      (((size) & 3) << 14) // Size
enum SIZE { TINY, SMALL, MEDIUM, LARGE }; // Size Options (See Sprite Dimension Chart)

// Attribute 2
#define ATTR2_TILEID(t)     ((t) & TILEMASK) // Tile ID (1D Memory Position)
#define ATTR2_TILEID(x, y)  OFFSET(((x) & 31), ((y) & 31), 32) // Tile ID (2D Grid Position)
#define ATTR2_PRIORITY(num) (((num) & 3) << 10) // Priority
#define ATTR2_PALROW(row)   (((row) & 15) << 12) // Palette Row

// Sprite Dimension Chart (In Tiles)
//        -------------------------------------
//        |  TINY  | SMALL  | MEDIUM | LARGE  |
// --------------------------------------------
// SQUARE |  8x8   | 16x16  | 32x32  | 64x64  |
// --------------------------------------------
//  WIDE  |  16x8  | 32x8   | 32x16  | 64x32  |
// --------------------------------------------
//  TALL  |  8x16  | 8x32   | 16x32  | 32x64  |
// --------------------------------------------

// Object Attribute Struct
typedef struct {

    u16 attr0;
    u16 attr1;
    u16 attr2;
    u16 fill;
    
} OBJ_ATTR;

// Affine Matrix Struct
typedef struct {

    u16 fill0[3];
    u16 a;

    u16 fill1[3];
    u16 b;

    u16 fill2[3];
    u16 c;

    u16 fill3[3];
    u16 d;
    
} AFFINE_MATRIX;

// Generic struct for animated sprite
typedef struct {

    int width;
    int height;

    int worldX;
    int dx;
    int worldY;
    int dy;
    
    int prevAniState;
    int aniState;
    int currFrame;
    int aniCounter;
    int numFrames;
    
    OBJ_ATTR* attributes;
    int hide;
    int affineMatrix;

} ANISPRITE;

// Sprite Functions
void hide(ANISPRITE* sprite);
void hideSprites();
void setAffineMatrix(int matrix, u16 a, u16 b, u16 c, u16 d);
void updateOAM();

#endif