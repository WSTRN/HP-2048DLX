#pragma once

#include <hpgcc3.h>
#include "ggl.h"
#include "ggl_extlib.h"



int time_getTicks();
int RTC_getTicks();
void Sleep(int ms);

void ML_port();
void ML_clear_vram();
void ML_display_vram();
typedef enum {ML_TRANSPARENT=-1, ML_WHITE, ML_BLACK, ML_XOR, ML_CHECKER} ML_Color;
void ML_rectangle(int x1, int y1, int x2, int y2, int border_width, ML_Color border_color, ML_Color fill_color);
void ML_horizontal_line(int y, int x1, int x2, ML_Color color);
void ML_vertical_line(int x, int y1, int y2, ML_Color color);
void ML_bmp_or(const unsigned char *bmp, int x, int y, int width, int height);
void ML_bmp_and(const unsigned char *bmp, int x, int y, int width, int height);
void ML_bmp_16_or(const unsigned char *bmp, int x, int y);
void ML_bmp_16_and(const unsigned char *bmp, int x, int y);

void Txt_Point(int x, int y, int v, int m);
void Txt_Text(const char *s, int x, int y, int f, int m);

void Read(int *Record, int *Score, int *TempsPartie, uint8_t Grille[4][4], uint8_t *MedaillesObtenues, uint8_t *Statistiques);
void Save(int Record, int Score, int TempsPartie, uint8_t **Grille, uint8_t *MedaillesObtenues, uint8_t *Statistiques);
