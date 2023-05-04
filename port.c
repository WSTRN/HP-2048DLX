#include "port.h"
extern gglsurface s;
extern gglsurface rs;

int time_getTicks()
{
    return RTC_getTicks();
}

int RTC_getTicks() // 128hz
{
    return tmr_ticks() / (tmr_getsysfreq() / 128);
}

void Sleep(int ms)
{
    tmr_delayms(ms);
}

void ML_clear_vram()
{
    ggl_rect(&s, 0, 0, 127, 63, ggl_mkcolor(0));
}

void ML_display_vram()
{
    rs.y = 8;
    ggl_bitblt(&rs, &s, 128, 64);
}

// static uint8_t ggl_buff[128*64/2];
gglsurface t;
int gglbuff;
void ML_port()
{
    ggl_rect(&s, 0, 0, 127, 63, ggl_mkcolor(0));
    t.width = 128;
    gglbuff = (int)sys_phys_malloc(128 * 32 + 16);
    t.addr = (int *)((sys_map_v2p(gglbuff) + 15) & 0xfffffff0);
}
void ML_rectangle(int x1, int y1, int x2, int y2, int border_width, ML_Color border_color, ML_Color fill_color)
{

    // if((border_color!=-1)&&(border_width!=0))
    // {
    //     s.x=x1;
    //     s.y=y1;
    //     t.width=x2-x1;
    //     t.addr=ggl_buff;
    //     // ggl_rect(&t, 0, 0, x2-x1, y2-y1, ggl_mkcolor(border_color?15:0));
    //     ggl_rect(&t, 0, 0, x2-x1, y2-y1, ggl_mkcolor((border_color==0)?0:15));
    //     ggl_bitbltoper(&s, &t, x2-x1, y2-y1, (border_color==2)?LG_XOR:LG_DEFAULT,logic_operator);
    // }
    // if(fill_color!=-1)
    // {
    //     s.x=x1+border_width;
    //     s.y=y1+border_width;
    //     t.width=x2-x1-2*border_width;
    //     t.addr=ggl_buff;
    //     ggl_rect(&t, 0, 0, x2-x1-2*border_width, y2-y1-2*border_width, ggl_mkcolor((border_color==0)?0:15));
    //     ggl_bitbltoper(&s, &t, x2-x1-2*border_width, y2-y1-2*border_width,
    //     (fill_color==2)?LG_XOR:LG_DEFAULT,logic_operator);
    // }

    if (border_width == 0)
    {
        t.x = x1;
        t.y = y1;
        s.x = x1;
        s.y = y1;
        ggl_rect(&t, x1, y1, x2, y2, ggl_mkcolor((fill_color == 0) ? 0 : 15));
        ggl_bitbltoper(&s, &t, x2 - x1 + 1, y2 - y1 + 1, (fill_color == 2) ? 2 : 4, logic_operator);
        s.x = 0;
        s.y = 0;
    }
    else
    {
        ggl_rect(&s, x1, y1, x2, y2, ggl_mkcolor((border_color == 0) ? 0 : 15));
        ggl_rect(&s, x1 + border_width, y1 + border_width, x2 - border_width, y2 - border_width,
                 ggl_mkcolor((fill_color == 0) ? 0 : 15));
    }
}
void ML_horizontal_line(int y, int x1, int x2, ML_Color color)
{
    ggl_hline(&s, y, x1, x2, ggl_mkcolor((color == 0) ? 0 : 15));
}
void ML_vertical_line(int x, int y1, int y2, ML_Color color)
{
    ggl_vline(&s, x, y1, y2, ggl_mkcolor((color == 0) ? 0 : 15));
}
void ML_bmp_or(const unsigned char *bmp, int x, int y, int width, int height)
{

    int tmpwidth = width / 8;
    int w = (tmpwidth + ((width % 8 == 0) ? 0 : 1)) * 8;
    gglsurface tmp;
    tmp.addr = (int *)bmp;
    tmp.width = w;
    tmp.x = 0;
    tmp.y = 0;
    t.x = x;
    t.y = y;
    ggl_bitblt(&t, &tmp, w, height);

    s.x = x;
    s.y = y;
    ggl_bitbltoper(&s, &t, width, height, 1, logic_operator);
    s.x = 0;
    s.y = 0;
}

void ML_bmp_and(const unsigned char *bmp, int x, int y, int width, int height)
{

    int tmpwidth = width / 8;
    int w = (tmpwidth + ((width % 8 == 0) ? 0 : 1)) * 8;
    gglsurface tmp;
    tmp.addr = (int *)bmp;
    tmp.width = w;
    tmp.x = 0;
    tmp.y = 0;
    t.x = x;
    t.y = y;
    ggl_bitblt(&t, &tmp, w, height);

    s.x = x;
    s.y = y;
    ggl_bitbltoper(&s, &t, width, height, 0, logic_operator);
    s.x = 0;
    s.y = 0;
}
void ML_bmp_16_or(const unsigned char *bmp, int x, int y)
{
    ML_bmp_or(bmp, x, y, 16, 16);
}

void ML_bmp_16_and(const unsigned char *bmp, int x, int y)
{
    ML_bmp_and(bmp, x, y, 16, 16);
}




void Txt_Pixel(int x, int y, int v)
{
    int off=(y*s.width+x);
    register int *word_addr=(int *)s.addr+ (off>>3);
    // if(x&~127 || y&~63) return;
    if(v==1)      *(word_addr) |=  (0x0000000f<<(4*(off%8)));
    else if(v==2) *(word_addr) ^=  (0x0000000f<<(4*(off%8)));
    else          *(word_addr) &= ~(0x0000000f<<(4*(off%8)));
}

void Txt_Point(int x, int y, int v, int m)
{
  switch(m)
  {
    case TXT_OR:  if(v) Txt_Pixel(x,y,1); break;
    case TXT_ON:  Txt_Pixel(x,y,v); break;
    case TXT_AND: if(v) Txt_Pixel(x,y,0); break;
    case TXT_REV: Txt_Pixel(x,y,v?0:1); break;
    case TXT_XOR: if(v) Txt_Pixel(x,y,2); break;
  }
}

void Txt_Char(char c, int x, int y, int f, int w, int h, int m)
{
  unsigned int *font = Txt_Fonts[f];
  unsigned char a,b,v;
  int offbyte = (c*w*h)>>5;
  int offbit  = (c*w*h)&31;
  if(!font) return;

  for(b=0;b<h;b++)
  {
    for(a=0;a<w;a++)
    {
      v = (font[offbyte]&(1<<(31-offbit)))!=0;
      Txt_Point(x+a,y+b,v,m);
      if(offbit++==31) offbyte++, offbit=0;
    }
  }
}
void Txt_Text(const char *s, int x, int y, int f, int m)
{
  const unsigned char Txt_Widths[TXT_FONTS]  = { 3, 5, 5 };
  const unsigned char Txt_Heights[TXT_FONTS] = { 5, 7, 5 };
  const unsigned char w = Txt_Widths[f];
  const unsigned char h = Txt_Heights[f];
  char *p = (char *)s;
  int i;

  while(*p)
  {
    Txt_Char(*p,x,y,f,w,h,m);
    p++;
    x += w;
    if(*p) for(i=0;i<h;i++) Txt_Point(x,y+i,0,m);
    x++;
  }
}

void Read(int *Record, int *Score, int *TempsPartie, uint8_t Grille[4][4], uint8_t *MedaillesObtenues, uint8_t *Statistiques)
{
    ;
}

void Save(int Record, int Score, int TempsPartie, uint8_t **Grille, uint8_t *MedaillesObtenues, uint8_t *Statistiques)
{
    ;
}