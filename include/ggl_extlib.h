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
void ggle_bmp(gglsurface *dest, int x, int y, const uint8_t* bmp, int w, int h);
void ggle_bmp_logic(gglsurface *dest, int x, int y, const uint8_t* bmp, int w, int h, int logic);
unsigned int logic_operator(unsigned int dest, unsigned int source, int param);