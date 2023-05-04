#pragma once
#include <hpgcc3.h>
#include "ggl.h"

enum{
	LG_AND,
	LG_OR,
	LG_XOR,
	LG_NOT,
	LG_DEFAULT
};

#define TXT_FONTS 3
#define TXT_OR  0x01
#define TXT_ON  0x02
#define TXT_AND 0x04
#define TXT_REV 0x08
#define TXT_XOR 0x10
#define TXT_MINISD    0
#define TXT_SYSTEM    1
#define TXT_ARCADIUM  2
#define FONT_MINISD   0x01
#define FONT_SYSTEM   0x02
#define FONT_ARCADIUM 0x04
const unsigned int Txt_Fonts[TXT_FONTS][140];
void ggle_bmp(gglsurface *dest, int x, int y, const uint8_t* bmp, int w, int h);
void ggle_bmp_logic(gglsurface *dest, int x, int y, const uint8_t* bmp, int w, int h, int logic);
unsigned int logic_operator(unsigned int dest, unsigned int source, int param);
void ggle_Text(gglsurface *dest, const char *s, int x, int y, int f);
void ggle_Pixel(gglsurface *dest, int x, int y, int v);
