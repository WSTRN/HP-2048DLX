
#include "ggl.h"
#include "ggl_extlib.h"
#include "keyb.h"
#include "sys.h"
#include <hpgcc3.h>
#include <stdint.h>
#include <time.h>
#include "port.h"

gglsurface s;
gglsurface rs;
// uint8_t surfacebuff[128 * 32 / 2];
int vbuff;
void app_2048_main();
int main()
{
    ggl_initscr(&rs);
    lcd_setmode(MODE_16GRAY, rs.addr);
    vbuff=(int)sys_phys_malloc( 128*32 + 16);
    s.addr = (int *)((sys_map_v2p(vbuff)+15)&0xfffffff0);
    s.width = 128;
    s.x=0;
    s.y=0;

    

    ML_port();
    app_2048_main();
    // ML_rectangle(64,0,127,63,2,1,0);
    // // ML_rectangle(20,20,107,43,0,0,2);
    // ML_bmp_or(P2[2],60,10,16,16);
    // ML_bmp_or(TexteMenu[3],50,40,59,7);
    // ML_display_vram();

    while(!keyb_isKeyPressed(KB_ON));
    return 0;
}
