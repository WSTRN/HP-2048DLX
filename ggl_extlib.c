#include "ggl_extlib.h"
#include <stdint.h>
#include <string.h>

unsigned int logic_operator(unsigned int dest, unsigned int source, int param)
{
	switch(param)
	{
	case LG_AND:
		return dest & source;
	case LG_OR:
		return dest | source;
	case LG_XOR:
		return dest ^ source;
	case LG_NOT:
		return ~source;
	default:
		return source;
	}

}
void ggle_bmp(gglsurface *dest, int x, int y, const uint8_t* bmp, int w, int h)
{
	gglsurface tmp;
	tmp.addr = (int*)bmp;
	tmp.width = w;
	tmp.x = 0;
	tmp.y = 0;
	dest->x = x;
	dest->y = y;
	ggl_bitblt(dest, &tmp, w, h);
	dest->x = 0;
	dest->y = 0;
}
void ggle_bmp_logic(gglsurface *dest, int x, int y, const uint8_t* bmp, int w, int h, int logic)
{
	gglsurface tmp;
	tmp.addr = (int*)bmp;
	tmp.width = w;
	tmp.x = 0;
	tmp.y = 0;
	dest->x = x;
	dest->y = y;
	ggl_bitbltoper(dest, &tmp, w, h, logic, logic_operator);
	dest->x = 0;
	dest->y = 0;
}
