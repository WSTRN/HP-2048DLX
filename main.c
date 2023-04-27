#include "include/main.h"
#include "ggl.h"
#include "ggl_extlib.h"
#include "keyb.h"
#include "sys.h"
#include <hpgcc3.h>

gglsurface s;
int main()
{
    int Score = 0;
    int Record = 0;
    int AffTxt;
    int ChoixMode;
    int Direction;
    int X;
    int Y;
    int X2;
    int Y2;
    int I;
    int J;
    int NbrDeplacement;
    int M;
    int E;
    int Case1;
    int Case2;
    int TestCoups;
    int Z;
    int Z2;
    int TestCase;
    int Apparition;
    int Gagne;
    int ChoixAnimation = 1;
    ggl_initscr(&s);
    lcd_setmode(MODE_16GRAY, s.addr);
    ggl_rect(&s, 0, 0, 64, 62, ggl_mkcolor(15));
    ggl_rect(&s, 1, 1, 63, 61, ggl_mkcolor(0));
    ggl_rect(&s, 65, 0, 127, 62, ggl_mkcolor(15));
    ggl_rect(&s, 66, 1, 126, 61, ggl_mkcolor(0));
    ggl_hline(&s, 63, 0, 127, ggl_mkcolor(15));
    ggle_bmp(&s, 66, 1, P2[2], 16, 16);
    ggle_bmp(&s, 81, 1, Im0, 16, 16);
    ggle_bmp(&s, 96, 1, P2[3], 16, 16);
    ggle_bmp(&s, 111, 1, P2[4], 16, 16);
    ggle_bmp_logic(&s, 67, 17, DELUX, 64, 12, LG_OR);
    ggle_bmp_logic(&s, 66, 30, ImRecord, 64, 7, LG_OR);
    ggle_bmp_logic(&s, 67, 48, Kirafi, 64, 13, LG_OR);
    AffTxt = Record;
    if (AffTxt == 0)
        ggle_bmp_logic(&s, 93, 39,Chiffres[0], 8, 7, LG_OR);
    for (Z = 93 + 3 * (int)(log10(AffTxt)); AffTxt; Z -= 6)
    {
        ggle_bmp_logic(&s, Z, 39,Chiffres[AffTxt % 10], 8, 7, LG_OR);
        AffTxt /= 10;
    }
    X = 1; //"Continuer" est selectionn� par d�faut
    X2 = X;

    /*for (int i = 0; i < 4; i++)*/
    /*{*/
        /*for (int j = 0; j < 4; j++)*/
        /*{*/
            /*ggle_bmp(&s, 1 + j * 15, 1 + i * 15, P2[4 * i + j], 16, 16);*/
        /*}*/
    /*}*/

    ///////////////////////////
    unsigned int keys;
    while (1)
    {
		ggl_rect(&s, 1, 1, 63, 61, ggl_mkcolor(0));
		for(Z=4;Z<55;Z+=10)ggle_bmp(&s,13,Z,TexteMenu[((Z-4)/10)*2],40,5);
		ggl_rect(&s, 13,4+X*10,51,8+X*10,ggl_mkcolor(0));
		ggle_bmp_logic(&s, 4, 3+X*10, TexteMenu[X*2+1], 64, 7, LG_OR);
        keys = keyb_getmsg();
        if (keys == (KB_ON | KM_KEYDN))
            return 0;
        if (keys == (KB_UP | KM_PRESS))
			X--;
        else if (keys == (KB_DN | KM_PRESS))
			X++;
        /*else if (keys == (KB_LF | KM_PRESS))*/
			/*;*/
        /*else if (keys == (KB_RT | KM_PRESS))*/
			/*;*/
		if(X<0)X=5;
		if(X>5)X=0;
        tmr_delayms(50);
    }
    return 0;
}
