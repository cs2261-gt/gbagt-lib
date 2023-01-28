#ifndef GBA_H 
#define GBA_H
// Mode 0 Scaffold

// Typedefs
typedef signed char s8;
typedef unsigned char u8;
typedef signed short s16;
typedef unsigned short u16;
typedef signed int s32;
typedef unsigned int u32;
typedef signed long long s64;
typedef unsigned long long u64;


// Miscellaneous Macros
#define OFFSET(x, y, width) ((y) * (width) + (x))

// Display Control Register Macros
#define REG_DISPCTL     (*(volatile unsigned short *)0x4000000)
#define MODE(x)         ((x) & 7)
#define DISP_BACKBUFFER (1<<4)
#define BG0_ENABLE      (1<<8)
#define BG1_ENABLE      (1<<9)
#define BG2_ENABLE      (1<<10)
#define BG3_ENABLE      (1<<11)
#define SPRITE_ENABLE   (1<<12)
#define SPRITE_MODE_2D  (0<<6)
#define SPRITE_MODE_1D  (1<<6)

// Display Status Registers
#define SCANLINECOUNTER (*(volatile unsigned short *)0x4000006)

// Display Constants
#define SCREENHEIGHT 160
#define SCREENWIDTH  240

// Video Buffer
extern volatile unsigned short *videoBuffer;

// ---- Color ----
#define BG_PALETTE       ((unsigned short *)0x5000000)
#define COLOR(r, g, b) (((r) & 31) | ((g) & 31) << 5 | ((b) & 31) << 10)

// Miscellaneous Functions
int collision(int colA, int rowA, int widthA, int heightA, int colB, int rowB, int widthB, int heightB);


// ---- Input ----

// Button Register
#define BUTTONS (*(volatile unsigned short *)0x04000130)

// Button Masks
#define BUTTON_A		(1<<0)
#define BUTTON_B		(1<<1)
#define BUTTON_SELECT	(1<<2)
#define BUTTON_START	(1<<3)
#define BUTTON_RIGHT	(1<<4)
#define BUTTON_LEFT		(1<<5)
#define BUTTON_UP		(1<<6)
#define BUTTON_DOWN		(1<<7)
#define BUTTON_R		(1<<8)
#define BUTTON_L		(1<<9)

// Variables for Button Macros
extern unsigned short oldButtons;
extern unsigned short buttons;

// Button Macros
#define BUTTON_HELD(key)    (~(BUTTONS) & (key))
#define BUTTON_PRESSED(key) (!(~(oldButtons) & (key)) && (~buttons & (key)))


// ---- Direct Memory Access (DMA) ----

// DMA Struct
typedef volatile struct {
    volatile const void *src;
    volatile void *dst;
    volatile unsigned int cnt;
} DMA;

// First DMA Register Address
extern DMA *dma;

// Destination Adjustment
#define DMA_DESTINATION_INCREMENT (0 << 21)
#define DMA_DESTINATION_DECREMENT (1 << 21)
#define DMA_DESTINATION_FIXED (2 << 21)
#define DMA_DESTINATION_RESET (3 << 21)

// Source Adjustment
#define DMA_SOURCE_INCREMENT (0 << 23)
#define DMA_SOURCE_DECREMENT (1 << 23)
#define DMA_SOURCE_FIXED (2 << 23)

// vBlank and hBlank Repeats
#define DMA_REPEAT (1 << 25)

// Chunk Size
#define DMA_16 (0 << 26)
#define DMA_32 (1 << 26)

// Timing Mode
#define DMA_AT_NOW (0 << 28)
#define DMA_AT_VBLANK (1 << 28)
#define DMA_AT_HBLANK (2 << 28)
#define DMA_AT_REFRESH (3 << 28)

// Trigger Interrupts
#define DMA_IRQ (1 << 30)

// Begin DMA
#define DMA_ON (1 << 31)

// DMA Functions
void DMANow(int channel, volatile const void *src, volatile void *dst, unsigned int cnt);


// ---- Timers ----

// Controllers
#define REG_TM0CNT *(volatile unsigned short*)0x4000102
#define REG_TM1CNT *(volatile unsigned short*)0x4000106
#define REG_TM2CNT *(volatile unsigned short*)0x400010A
#define REG_TM3CNT *(volatile unsigned short*)0x400010E

// Timer values
#define REG_TM0D *(volatile unsigned short*)0x4000100
#define REG_TM1D *(volatile unsigned short*)0x4000104
#define REG_TM2D *(volatile unsigned short*)0x4000108
#define REG_TM3D *(volatile unsigned short*)0x400010C

// Timer flags
#define TIMER_ON      (1<<7)
#define TIMER_OFF     (0<<7)
#define TM_IRQ        (1<<6)
#define TM_CASCADE    (1<<2)
#define TM_FREQ_1     0
#define TM_FREQ_64    1
#define TM_FREQ_256   2
#define TM_FREQ_1024  3


// ---- Interrupts ----

// Interrupt Registers
#define REG_IME *(unsigned short*)0x4000208 // Controller
#define REG_IE *(unsigned short*)0x4000200 // Enabler
#define REG_IF *(volatile unsigned short*)0x4000202 // Flag

// Interrupt Handler Function Pointer
typedef void (*ihp)(void);

// Interrupt Handler Register
#define REG_INTERRUPT *((ihp*)0x03007FFC)

// Display Status Register
#define REG_DISPSTAT *(unsigned short*)0x4000004

// Interrupt Settings
#define INT_VBLANK 1 << 0   
#define INT_TM0 1<<3    
#define INT_TM1 1<<4    
#define INT_TM2 1<<5    
#define INT_TM3 1<<6    
#define INT_BUTTON 1 << 12

#endif