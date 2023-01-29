#ifndef GBA_SPRITES_H
#define GBA_SPRITES_H

#include "gba.h"

// Sprite Palette
#define SPRITE_PAL ((u16 *)0x5000200)

// Object Attribute Struct
typedef struct {
  u16 attr0;
  u16 attr1;
  u16 attr2;
  u16 fill;
} OBJ_ATTR;

// Object Attribute Memory
#define OAM ((OBJ_ATTR*)(0x7000000))
extern OBJ_ATTR shadowOAM[128];

struct attr0 {
  u16 regular;       // Normal Rendering (default)
  u16 affine;        // Affine Rendering
  u16 hide;          // Hidden
  u16 double_affine; // Double Affine Rendering
  u16 enable_alpha;  // Enable Alpha Blending
  u16 enable_window; // Object Window Mode (see GBATek)
  u16 enable_mosaic; // Enable Mosaic Effect
  u16 fourBpp;       // 4 Bits Per Pixel (default)
  u16 eightBpp;      // 8 Bits Per Pixel
  u16 square;        // Square Shape (default)
  u16 wide;          // Wide Shape
  u16 tall;          // Tall Shape
};

struct attr1 {
  u16 hflip;  // Flip horizontally
  u16 vflip;  // Flip Vertically
  u16 tiny;   // See Size Chart
  u16 small;  // See Size Chart
  u16 medium; // See Size Chart
  u16 large;  // See Size Chart
};

struct oam_attrs {
  struct attr0 attr0;
  struct attr1 attr1;
};

// OAM Attributes
// Attribute 0:
//    Bits 0-7: Y coordinate
//    Bits 8-9: Object mode
//    Bits A-B: GFX mode
//    Bit C:    Mosaic mode
//    Bit D:    Color mode (bpp)
//    Bits E-F: Sprite shape
// Attribute 1:
//    Bits 0-8: X coordinate
//    Bits 9-D: Affine entry (ONLY IF affine is turned on in attr0 bit 8)
//    Bit C:    Horizontal flip
//    Bit D:    Vertical flip
//    Bits E-F: Sprite size
// Attribute 2:
//    Bits 0-9: Tile ID
//    Bits A-B: Priority
//    Bits C-F: Palette row
static struct oam_attrs oam = {
  .attr0 = {
    .regular = (0 << 8),
    .affine = (1 << 8),
    .hide = (2 << 8),
    .double_affine = (3 << 8),
    .enable_alpha = (1 << 10),
    .enable_window = (1 << 11),
    .enable_mosaic = (1 << 12),
    .fourBpp = (0 << 13),
    .eightBpp = (1 << 13),
    .square = (0 << 14),
    .wide = (1 << 14),
    .tall = (1 << 15),
  },
  .attr1 = {
    .hflip = (1 << 12),
    .vflip = (1 << 13),
    .tiny = (0 << 14),
    .small = (1 << 14),
    .medium = (2 << 14),
    .large = (3 << 14)
  }
};

// ----------- Sprite Size Chart --------------
// --------------------------------------------
// --------------------------------------------
// SQUARE |  8x8   | 16x16 | 32x32  | 64x64  |
// --------------------------------------------
//  WIDE  |  16x8  | 32x8  | 32x16  | 64x32  |
// --------------------------------------------
//  TALL  |  8x16  | 8x32  | 16x32  | 32x64  |
// --------------------------------------------



// Attribute 2
#define ATTR2_TILEID(x, y) (((y)*32+(x)) & 0x3FF)
#define ATTR2_PRIORITY(num)    (((num) & 3) << 10)
#define ATTR2_PALROW(y)      (((y) & 0xF) <<12)

// Sprite Functions
void hideSprites();

#define SPRITE_Y(y)    ((y) & 0xFF)
#define SPRITE_X(x)    ((x) & 0x1FF)
#define SPRITE_TILE(t) ((t) & 0x3FF)

// Generic struct for animated sprite
typedef struct {
    int worldX;
    int worldY;
    int xVelocity;
    int yVelocity;
    int width;
    int height;
    int framesPassed;
    int direction; // direction struct has up down left right
    int aniState; // in lab09, anistate struct only has walking
    int aniFrame;
    int numFrames;
    int hide;
} ANISPRITE;

#endif