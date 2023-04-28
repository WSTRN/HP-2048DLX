#include "include/main.h"
#include "ggl.h"
#include "ggl_extlib.h"
#include "keyb.h"
#include "sys.h"
#include <hpgcc3.h>
#include <stdint.h>
#include <time.h>

gglsurface s;
gglsurface rs;
uint8_t surfacebuff[131 * 40];
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
    int i;
    int j;
    int Chance;
    unsigned char TestFusion1[] = {0, 0, 0, 0, 0, 0, 0, 0};
    unsigned char TestFusion2[] = {0, 0, 0, 0, 0, 0, 0, 0};
    int NbrFusion;
    int NbrCombo;
    int NbrSuite;
    int TestSuite;
    int NbrDesordonne;
    int TestArtistique;
    int TestDernierSucce;
    int Secondes;
    int Minutes;
    int Heures;
    int TempsPartie;
    int TempsSession;
    int TempsReference;
    int TempsActuel;
    int ChoixSucceOrganisation;
    int Defilement;
    int Ralentissement;
    char buffer[16];
    uint8_t Grille[4][4] = {{0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}};
    unsigned char Boleens1[] = {0, 0, 0, 0};
    unsigned char Boleens2[] = {0, 0, 0, 0};
    unsigned int Statistiques[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    unsigned char MedaillesObtenues[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                         0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

    ggl_initscr(&rs);
    lcd_setmode(MODE_16GRAY, rs.addr);
    s.addr = (int *)surfacebuff;
    s.x = 0;
    s.y = 0;
    s.width = 131;

    ggl_rect(&s, 0, 0, 130, 79, ggl_mkcolor(0));
    ggle_bmp(&s, 0, 0, fill, 127, 2);
    ggle_bmp(&s, 0, 2, fill, 127, 2);
    ggle_bmp(&s, 0, 4, fill, 127, 2);
    ggle_bmp(&s, 0, 6, fill, 127, 2);
    ggl_rect(&s, 0, 73, 20, 79, ggl_mkcolor(15));
    ggl_rect(&s, 22, 73, 42, 79, ggl_mkcolor(15));
    ggl_rect(&s, 44, 73, 64, 79, ggl_mkcolor(15));
    ggl_rect(&s, 66, 73, 86, 79, ggl_mkcolor(15));
    ggl_rect(&s, 88, 73, 108, 79, ggl_mkcolor(15));
    ggl_rect(&s, 110, 73, 130, 79, ggl_mkcolor(15));
    ggl_rect(&s, 0, 8, 64, 70, ggl_mkcolor(15));
    ggl_rect(&s, 1, 9, 63, 69, ggl_mkcolor(0));
    ggl_rect(&s, 65, 8, 127, 70, ggl_mkcolor(15));
    ggl_rect(&s, 66, 9, 126, 69, ggl_mkcolor(0));
    ggl_hline(&s, 71, 0, 127, ggl_mkcolor(15));
    ggle_bmp(&s, 66, 9, P2[2], 16, 16);
    ggle_bmp(&s, 81, 9, Im0, 16, 16);
    ggle_bmp(&s, 96, 9, P2[3], 16, 16);
    ggle_bmp(&s, 111, 9, P2[4], 16, 16);
    ggle_bmp_logic(&s, 67, 25, DELUX, 64, 12, LG_OR);
    ggle_bmp_logic(&s, 66, 38, ImRecord, 64, 7, LG_OR);
    ggle_bmp_logic(&s, 67, 56, Kirafi, 64, 13, LG_OR);
    AffTxt = Record;
    if (AffTxt == 0)
        ggle_bmp_logic(&s, 93, 47, Chiffres[0], 8, 7, LG_OR);
    for (Z = 93 + 3 * (int)(log10(AffTxt)); AffTxt; Z -= 6)
    {
        ggle_bmp_logic(&s, Z, 47, Chiffres[AffTxt % 10], 8, 7, LG_OR);
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
    srand(tmr_ticks());
    while (1)
    {
        for (Z = 12; Z < 63; Z += 10)
            ggle_bmp(&s, 13, Z, TexteMenu[((Z - 4) / 10) * 2], 40, 5);
        ggl_rect(&s, 13, 12 + X * 10, 51, 16 + X * 10, ggl_mkcolor(0));
        ggle_bmp_logic(&s, 4, 11 + X * 10, TexteMenu[X * 2 + 1], 64, 7, LG_OR);
        /*keys = keyb_getmsg();*/
        /*if (keys == (KB_ON | KM_KEYDN))*/
        /*return 0;*/
        /*if (keys == (KB_UP | KM_PRESS))*/
        /*X--;*/
        /*else if (keys == (KB_DN | KM_PRESS))*/
        /*X++;*/
        /*else if (keys == (KB_ENT | KM_PRESS))*/
        /*break;*/
        /*else if (keys == (KB_LF | KM_PRESS))*/
        /*;*/
        /*else if (keys == (KB_RT | KM_PRESS))*/
        /*;*/
        ggl_bitblt(&rs, &s, 131, 80);
        while (keyb_isKeyPressed(KB_ENT) || keyb_isKeyPressed(KB_UP) || keyb_isKeyPressed(KB_DN))
            ;
        X2 = X;
        while (X2 == X)
        {
            if (keyb_isKeyPressed(KB_ON))
                return 0;
            if (keyb_isKeyPressed(KB_UP))
                X--;
            if (keyb_isKeyPressed(KB_DN))
                X++;
            if (keyb_isKeyPressed(KB_ENT))
                break;
        }
        if (X < 0)
            X = 5;
        if (X > 5)
            X = 0;
        tmr_delayms(50);
        ggl_rect(&s, 1, 9, 63, 69, ggl_mkcolor(0));
        if (keyb_isKeyPressed(KB_ENT))
            break; // EXE pour valider
    }
    ChoixMode = X;
    /*ggle_bmp(&s, 1, 9, P2[ChoixMode], 16, 16);*/
    while (keyb_isKeyPressed(KB_ENT))
        ;
    if (ChoixMode < 2)
    {
        X = 0;
        while (1)
        {
            ggl_rect(&s, 1, 34 + X * 9, 63, 42 + X * 9, ggl_mkcolor(15));
            for (Z = 0; Z < 4; Z++)
                ggle_bmp_logic(&s, 2, 35 + Z * 9, ImTexteSucces[Z + 4], 64, 7, LG_XOR);
            /*ML_display_vram();*/
            ggl_bitblt(&rs, &s, 131, 80);
            while (keyb_isKeyPressed(KB_ENT) || keyb_isKeyPressed(KB_UP) || keyb_isKeyPressed(KB_DN))
                ;
            X2 = X;
            while (X2 == X)
            {
                if (keyb_isKeyPressed(KB_ON))
                    return 0;
                if (keyb_isKeyPressed(KB_UP))
                    X--;
                if (keyb_isKeyPressed(KB_DN))
                    X++;
                if (keyb_isKeyPressed(KB_ENT))
                    break;
            }
            if (X < 0)
                X = 3;
            if (X > 3)
                X = 0;
            ggl_rect(&s, 1, 34, 63, 69, ggl_mkcolor(0));
            if (keyb_isKeyPressed(KB_ENT))
                break;
        }
        ChoixSucceOrganisation = X;
        while (keyb_isKeyPressed(KB_ENT))
            ;

        if (ChoixMode == 0)
        {
            // Si nouvelle partie, teste si l'ancien score est plus �lev� que le record
            if (Score > Record)
            {                   // Nouveau record
                Record = Score; // Le record prend la valeur du score
                                /*Save(Record, Score, TempsPartie, Grille, MedaillesObtenues,Statistiques);*/
            }
            Score = 0; // R�initialisation du score � z�ro
        }

        while (1) // play
        {
            ggl_rect(&s, 0, 8, 127, 71, ggl_mkcolor(0));
            ggl_rect(&s, 0, 8, 62, 70, ggl_mkcolor(15));        // Rectangle de gauche
            ggl_rect(&s, 1, 9, 61, 69, ggl_mkcolor(0));         // Rectangle de gauche
            ggl_rect(&s, 63, 8, 127, 70, ggl_mkcolor(15));      // Rectangle de Droite
            ggl_rect(&s, 64, 9, 126, 69, ggl_mkcolor(0));       // Rectangle de Droite
            ggl_hline(&s, 71, 0, 127, ggl_mkcolor(15));         // Ligne du bas de l'�cran
            ggl_rect(&s, 64, 28, 126, 29, ggl_mkcolor(15));     // Rectangle de Droite
            ggl_rect(&s, 64, 49, 126, 50, ggl_mkcolor(15));     // Rectangle de Droite
            ggle_bmp_logic(&s, 66, 10, ImScore1, 64, 7, LG_OR); // Score
            ggle_bmp_logic(&s, 65, 31, ImRecord, 64, 7, LG_OR); // Score
            ggle_bmp_logic(&s, 83, 52, ImTime, 32, 7, LG_OR);   // Score
                                                                // Dessin du score
            AffTxt = Score;
            if (AffTxt == 0)
                ggle_bmp_logic(&s, 92, 19, Chiffres[0], 8, 7, LG_OR);
            for (Z = 92 + 3 * (int)(log10(AffTxt)); AffTxt; Z -= 6)
            {
                ggle_bmp_logic(&s, Z, 19, Chiffres[AffTxt % 10], 8, 7, LG_OR);
                AffTxt /= 10;
            }

            AffTxt = Record;
            if (AffTxt == 0)
                ggle_bmp_logic(&s, 92, 40, Chiffres[0], 8, 7, LG_OR);
            for (Z = 92 + 3 * (int)(log10(AffTxt)); AffTxt; Z -= 6)
            {
                ggle_bmp_logic(&s, Z, 40, Chiffres[AffTxt % 10], 8, 7, LG_OR);
                AffTxt /= 10;
            }
            if (Score == 0)
            {
                TempsPartie = 0;   // Initialisation du temps � 00:00:00
                Statistiques[0]++; // Sauvegarde du nombre de partie cr��

                // Initialisation des donn�es de la grille
                for (X = 0; X < 4; X++)
                    for (Y = 0; Y < 4; Y++)
                        Grille[Y][X] = 0; // Inisialisation de la grille
                for (X = 0; X < 4; X++)
                    for (Y = 0; Y < 4; Y++)
                        ggle_bmp_logic(&s, X * 15 + 1, Y * 15 + 9, P2[1], 16, 16, LG_OR);

                ggl_bitblt(&rs, &s, 131, 80);
                // Cr�ation al�atoire des coordonn�es des premiers chiffres
                for (Z = 0; Z < 2; Z++)
                {
                    while (Grille[Y][X])
                    {
                        X = rand() % 4;
                        Y = rand() % 4;
                    }
                    Apparition = rand() % 10; // 90%=2 ou 10%=4
                    if (Apparition)
                        Grille[Y][X] = 1;
                    else
                        Grille[Y][X] = 2;
                    /*ggle_bmp_logic(&s, X * 15 + 1, Y * 15 + 9, P2[0], 16, 16, LG_AND);*/
                }
                ggl_bitblt(&rs, &s, 131, 80);
                tmr_delayms(150);
            }
            for (X = 0; X < 4; X++)
                for (Y = 0; Y < 4; Y++)
                    ggle_bmp(&s, X * 15 + 1, Y * 15 + 9, P2[Grille[Y][X] + 1], 16, 16);

            ggl_bitblt(&rs, &s, 131, 80);

            if (Score >= 20084)
                Gagne = 2; // Test si le joueur a d�j� obtenu un 2048 (en fonction de son score)
            else
                Gagne = 0;

            // Initialisation variable de test des succ�s
            Chance = 0;
            for (Z = 0; Z < 8; Z++)
                TestFusion1[Z] = 0;
            for (Z = 0; Z < 8; Z++)
                TestFusion2[Z] = 0;
            NbrFusion = 0;
            NbrCombo = 0;
            NbrSuite = 0;
            TestSuite = 0;
            NbrDesordonne = 0;
            TestArtistique = 0;
            Secondes = TempsPartie % 60;
            Minutes = (TempsPartie / 60) % 60;
            Heures = (TempsPartie / 3600) % 24;
            TempsReference = tmr_ticks() / tmr_getsysfreq();

            ggle_bmp_logic(&s, 71, 61, ImTempsNul, 48, 7, LG_OR);
            ggl_rect(&s, 107, 61, 117, 67, ggl_mkcolor(0)); // Effa�age des secondes
            ggle_bmp_logic(&s, 112, 61, Chiffres[Secondes % 10], 8, 7, LG_OR);
            ggle_bmp_logic(&s, 106, 61, Chiffres[Secondes / 10], 8, 7, LG_OR);
            ggl_rect(&s, 89, 61, 99, 67, ggl_mkcolor(0)); // Effa�age des minutes
            ggle_bmp_logic(&s, 94, 61, Chiffres[Minutes % 10], 8, 7, LG_OR);
            ggle_bmp_logic(&s, 88, 61, Chiffres[Minutes / 10], 8, 7, LG_OR);
            ggl_rect(&s, 71, 61, 81, 67, ggl_mkcolor(0)); // Effa�age des heures
            ggle_bmp_logic(&s, 76, 61, Chiffres[Heures % 10], 8, 7, LG_OR);
            ggle_bmp_logic(&s, 70, 61, Chiffres[Heures / 10], 8, 7, LG_OR);

            while (1)
            {
                /*while (keyb_isKeyPressed(KB_UP) || keyb_isKeyPressed(KB_DN) || keyb_isKeyPressed(KB_LF) ||*/
                       /*keyb_isKeyPressed(KB_RT))*/
                /*{*/
                    /*TempsPartie = tmr_ticks() / tmr_getsysfreq() - TempsReference;*/
                    /*Secondes = TempsPartie % 60;*/
                    /*Minutes = (TempsPartie / 60) % 60;*/
                    /*Heures = (TempsPartie / 3600) % 24;*/
                    /*ggl_rect(&s, 64, 51, 126, 69, ggl_mkcolor(0)); // Effaÿage du succÿ*/
                                                                   /*//*/
                    /*[>ggle_bmp_logic(&s, 83, 52, ImTime, 32, 7, LG_OR);<]*/
                    /*[>ggle_bmp_logic(&s, 71, 61, ImTempsNul, 56, 7, LG_OR);<]*/

                    /*ggl_rect(&s, 107, 61, 117, 67, ggl_mkcolor(0));*/
                    /*ggle_bmp_logic(&s, 112, 61, Chiffres[Secondes % 10], 8, 7, LG_OR);*/
                    /*ggle_bmp_logic(&s, 106, 61, Chiffres[Secondes / 10], 8, 7, LG_OR);*/
                    /*ggl_rect(&s, 89, 61, 99, 67, ggl_mkcolor(0));*/
                    /*ggle_bmp_logic(&s, 94, 61, Chiffres[Minutes % 10], 8, 7, LG_OR);*/
                    /*ggle_bmp_logic(&s, 88, 61, Chiffres[Minutes / 10], 8, 7, LG_OR);*/
                    /*ggl_rect(&s, 71, 61, 81, 67, ggl_mkcolor(0));*/
                    /*ggle_bmp_logic(&s, 76, 61, Chiffres[Heures % 10], 8, 7, LG_OR);*/
                    /*ggle_bmp_logic(&s, 70, 61, Chiffres[Heures / 10], 8, 7, LG_OR);*/
                /*}*/
                Direction = 0; // Rÿinitialisation de la direction
                while (Direction == 0)
                {
                    do
                    {
                        if (keyb_isKeyPressed(KB_LF))
                            Direction = 1;
                        if (keyb_isKeyPressed(KB_RT))
                            Direction = 3;
                        if (keyb_isKeyPressed(KB_UP))
                            Direction = 8;
                        if (keyb_isKeyPressed(KB_DN))
                            Direction = 5;
                        if (keyb_isKeyPressed(KB_ON))
                            Direction = 10; // Touche [MENU] pour retourner au menu
                        if (keyb_isKeyPressed(KB_C))
                            Direction = 11;
                        {
                            if (ChoixAnimation)
                                ChoixAnimation = 0;
                            else
                                ChoixAnimation = 1;
                            while (keyb_isKeyPressed(KB_C))
                                ;
                        }
                        if (TempsActuel != (tmr_ticks() / tmr_getsysfreq()))
                        {
                            TempsActuel = tmr_ticks() / tmr_getsysfreq();
                            TempsPartie = TempsActuel - TempsReference;
                            Secondes = TempsPartie % 60;
                            Minutes = (TempsPartie / 60) % 60;
                            Heures = (TempsPartie / 3600) % 24;
                            ggl_rect(&s, 107, 61, 117, 67, ggl_mkcolor(0));
                            ggle_bmp_logic(&s, 112, 61, Chiffres[Secondes % 10], 8, 7, LG_OR);
                            ggle_bmp_logic(&s, 106, 61, Chiffres[Secondes / 10], 8, 7, LG_OR);
                            ggl_rect(&s, 89, 61, 99, 67, ggl_mkcolor(0));
                            ggle_bmp_logic(&s, 94, 61, Chiffres[Minutes % 10], 8, 7, LG_OR);
                            ggle_bmp_logic(&s, 88, 61, Chiffres[Minutes / 10], 8, 7, LG_OR);
                            ggl_rect(&s, 71, 61, 81, 67, ggl_mkcolor(0));
                            ggle_bmp_logic(&s, 76, 61, Chiffres[Heures % 10], 8, 7, LG_OR);
                            ggle_bmp_logic(&s, 70, 61, Chiffres[Heures / 10], 8, 7, LG_OR);
                            ggl_bitblt(&rs, &s, 131, 80);
                        }
                    } while (!Direction);
                    if (Direction)
                        break;
                }
                if (Direction == 10)
                {
                    TempsSession = Secondes + Minutes * 100 + Heures * 10000;
                    Statistiques[1] += TempsSession - TempsPartie;
                    TempsPartie = TempsSession;
                    if (Statistiques[1] % 100 > 59)
                        Statistiques[1] += 40;
                    if (Statistiques[1] % 10000 / 100 > 59)
                        Statistiques[1] += 4000;
                    /*Save(Record, Score, TempsPartie, Grille, MedaillesObtenues, Statistiques);*/
                    break;
                }
                if (Direction != 10)
                {
                    TestCoups = 0;
                    for (Z = 0; Z < 4; Z++)
                    { // Rÿinitialisation les collisions ÿ zÿro
                        Boleens1[Z] = 0;
                        Boleens2[Z] = 0;
                    }
                    for (NbrDeplacement = 0; NbrDeplacement < 3; NbrDeplacement++)
                    { // Le nombre de dÿplacement
                        for (Z = 0; Z < 4; Z++)
                            Boleens1[Z] = Boleens2[Z];
                        for (I = 1; I < 4; I++)
                        { // Parcourt la grille
                            for (J = 0; J < 4; J++)
                            { // Parcourt la grille
                                E = Boleens1[J] + I;
                                if (E < 4)
                                {
                                    if (Direction == 1)
                                        X = E; // Coordonnÿes de la case ÿ dÿplacer
                                    if (Direction == 3)
                                        X = 3 - E;
                                    if (Direction < 4)
                                        Y = J;
                                    if (Direction == 8)
                                        Y = E;
                                    if (Direction == 5)
                                        Y = 3 - E;
                                    if (Direction > 4)
                                        X = J;
                                    X2 = X;
                                    Y2 = Y;
                                    if (Direction == 1)
                                        X2 = X - 1; // Coordonnÿes de la case visÿ
                                    if (Direction == 3)
                                        X2 = X + 1;
                                    if (Direction == 8)
                                        Y2 = Y - 1;
                                    if (Direction == 5)
                                        Y2 = Y + 1;
                                    Case1 = Grille[Y][X];   // Case ÿ dÿplacer
                                    Case2 = Grille[Y2][X2]; // Case visÿ
                                    if (Case1)
                                    { // Si il y a un nombre dans la case ÿ dÿplacer
                                        if (!Case2)
                                        { // Si il n'y a rien dans la case visÿ, on y dÿplace le nombre K
                                            Grille[Y2][X2] = Case1;
                                            Grille[Y][X] = 0;
                                            if (ChoixAnimation)
                                            {
                                                ggle_bmp_logic(&s, X * 15 + 1, Y * 15 + 9, P2[1], 16, 16, LG_OR);
                                                ggle_bmp_logic(&s, X2 * 15 + 1, Y2 * 15 + 9, P2[Grille[Y2][X2] + 1], 16,
                                                               16, LG_AND);
                                            }
                                            TestCoups = 1; // Un coup viens d'ÿtre jouÿ
                                        }
                                        if (Case2 == Case1)
                                        {                    // Si les 2 nombres sont les mÿme, ÿa fusionne
                                            Boleens2[J] = E; // Paramÿtres anti-double-fusion
                                            Case2++;
                                            if (Case2 == 11 && !Gagne)
                                                Gagne = 1; // Le 2048 apparait !
                                            Grille[Y2][X2] = Case2;
                                            Grille[Y][X] = 0;
                                            if (ChoixAnimation)
                                            {
                                                ggle_bmp_logic(&s, X * 15 + 1, Y * 15 + 9, P2[1], 16, 16, LG_OR);
                                                ggle_bmp_logic(&s, X2 * 15 + 1, Y2 * 15 + 9, P2[1], 16, 16, LG_OR);
                                                ggle_bmp_logic(&s, X2 * 15 + 1, Y2 * 15 + 9, P2[0], 16, 16, LG_AND);
                                                ggle_bmp_logic(&s, X2 * 15 + 1, Y2 * 15 + 9, P2[Grille[Y2][X2] + 1], 16,
                                                               16, LG_AND);
                                            }
                                            TestCoups = 1;
                                            Score += pow(2, Case2); // Augmentation du score
                                            ggle_bmp_logic(&s, 66, 10, ImScore2, 64, 7, LG_OR);

                                            for (Z = 3; Z < 6; Z++)
                                                if (Case2 == Z + 7 && !MedaillesObtenues[Z])
                                                    MedaillesObtenues[Z] =
                                                        2; // Test si les succÿs de Fusion sont rÿalisÿes

                                            Statistiques[Case2 +
                                                         3]++; // Sauvegarde du nombre crÿÿ dans les statistiques
                                            TestFusion1[NbrFusion] = Case2; // Enregistrement des nombres de fusion
                                            NbrFusion++; // Enregistrement du nombre de fusion rÿalisÿ pour ce coups
                                        }
                                    }
                                }
                            }
                            if (ChoixAnimation)
                            {
                                ggl_bitblt(&rs, &s, 131, 80);
                                tmr_delayms(20);
                            }
                        }
                    } // Fin du dÿplacement des cases

                    TestCase = 1;
                    if (TestCoups)
                    {                                                // Si un coups viens d'ÿtre jouÿ
                        tmr_delayms(2);                              // Truc anti-bug d'affichage...
                        ggl_rect(&s, 0, 8, 62, 70, ggl_mkcolor(15)); // Rectangle de gauche
                        ggl_rect(&s, 1, 9, 61, 69, ggl_mkcolor(0));  // Rectangle de gauche
                        for (X = 0; X < 4; X++)
                            for (Y = 0; Y < 4; Y++)
                                /*ML_bmp_16_or(P2[Grille[Y][X] + 1], X * 15 + 1, Y * 15 + 1); // Dessin de la grille*/
                                ggle_bmp_logic(&s, X * 15 + 1, Y * 15 + 9, P2[Grille[Y][X] + 1], 16, 16, LG_OR);

                        /*ML_rectangle(64, 10, 126, 18, 1, 0, 0); // Effaÿage du score*/
                        ggl_rect(&s, 64, 18, 126, 26, ggl_mkcolor(0)); // Rectangle de gauche
                        AffTxt = Score;
                        if (AffTxt == 0)
                            /*ML_bmp_or(Chiffres[0], 92, 11, 7, 7); // Si Score=0, Dessine un 0*/
                            ggle_bmp_logic(&s, 92, 19, Chiffres[0], 8, 7, LG_OR);
                        for (Z = 92 + 3 * (int)(log10(AffTxt)); AffTxt; Z -= 6)
                        {
                            /*ML_bmp_or(Chiffres[AffTxt % 10], Z, 11, 7, 7); // Dessin de chaque chiffre du score*/
                            ggle_bmp_logic(&s, Z, 19, Chiffres[AffTxt % 10], 8, 7, LG_OR);
                            AffTxt /= 10;
                        }

                        if (Gagne == 1)
                        {
                            if (!MedaillesObtenues[28] && Secondes + Minutes * 100 + Heures * 10000 == 642)
                                MedaillesObtenues[28] = 2; // Test du succÿ 42
                            /*ML_rectangle(64, 43, 126, 61, 0, 0, 0); // Effaÿage de la 3ÿme zone d'ÿcriture*/
                            ggl_rect(&s, 64, 51, 126, 69, ggl_mkcolor(0));
                            /*ML_bmp_or(ImGagne, 65, 44, 61, 16); // Dessin du message de victoire "Gagnÿ"*/
                            ggle_bmp_logic(&s, 65, 52, ImGagne, 64, 16, LG_OR);
                        }
                        /*ML_display_vram(); // Affichage du jeu*/
                        ggl_bitblt(&rs, &s, 131, 80);

                        if (Gagne == 1)
                        {
                            while (!keyb_isKeyPressed(KB_ENT))
                                ; // Attend l'appuis de [EXE] pour continuer ÿ jouer
                            while (keyb_isKeyPressed(KB_ENT))
                                ;      // Attend que [EXE] soit relachÿ
                            Gagne = 2; // Change la valeur pour que le joueur ne gagne pas plusieurs fois
                            /*ML_rectangle(64, 43, 126, 61, 0, 0, 0); // Effaÿage de la 3ÿme zone d'ÿcriture*/
                            ggl_rect(&s, 64, 51, 126, 69, ggl_mkcolor(0));
                            if (Secondes + Minutes * 100 + Heures * 10000 < Statistiques[2] || !Statistiques[2])
                            {
                                Statistiques[2] = Secondes + Minutes * 100 + Heures * 10000; // Meilleur temps victoire
                                /*ML_bmp_or(TexteMenu[1], 67, 44, 57, 7);                      // Dessin de "Nouveau"*/
                                ggle_bmp_logic(&s, 67, 52, TexteMenu[1], 64, 7, LG_OR);
                                /*ML_bmp_or(ImTime, 83, 53, 25, 7); // Dessin de "TIME"*/
                                ggle_bmp_logic(&s, 83, 61, ImTime, 32, 7, LG_OR);
                                /*ML_display_vram();*/
                                ggl_bitblt(&rs, &s, 131, 80);
                                while (!keyb_isKeyPressed(KB_ENT))
                                    ; // Attend l'appuis de [EXE] pour continuer ÿ jouer
                                while (keyb_isKeyPressed(KB_ENT))
                                    ; // Attend que [EXE] soit relachÿ
                                /*ML_rectangle(64, 43, 126, 61, 0, 0, 0); // Effaÿage de la 3ÿme zone d'ÿcriture*/
                                ggl_rect(&s, 64, 51, 126, 69, ggl_mkcolor(0));
                            }
                            /*ML_bmp_or(ImTime, 83, 44, 25, 7); // Time*/
                            ggle_bmp_logic(&s, 83, 52, ImTime, 32, 7, LG_OR);
                            /*ML_bmp_or(ImTempsNul, 71, 53, 47, 7);              // Temps ÿ 00 : 00 : 00*/
                            ggle_bmp_logic(&s, 71, 61, ImTempsNul, 56, 7, LG_OR);
                            //
                            ggl_rect(&s, 107, 61, 117, 67, ggl_mkcolor(0));
                            ggle_bmp_logic(&s, 112, 61, Chiffres[Secondes % 10], 8, 7, LG_OR);
                            ggle_bmp_logic(&s, 106, 61, Chiffres[Secondes / 10], 8, 7, LG_OR);
                            ggl_rect(&s, 89, 61, 99, 67, ggl_mkcolor(0));
                            ggle_bmp_logic(&s, 94, 61, Chiffres[Minutes % 10], 8, 7, LG_OR);
                            ggle_bmp_logic(&s, 88, 61, Chiffres[Minutes / 10], 8, 7, LG_OR);
                            ggl_rect(&s, 71, 61, 81, 67, ggl_mkcolor(0));
                            ggle_bmp_logic(&s, 76, 61, Chiffres[Heures % 10], 8, 7, LG_OR);
                            ggle_bmp_logic(&s, 70, 61, Chiffres[Heures / 10], 8, 7, LG_OR);
                        }

                        while (Grille[Y][X])
                        {
                            X = rand() % 4; // Crÿation alÿatoire des coordonnÿes du nouveau chiffre de la grille
                            Y = rand() % 4;
                        }
                        Apparition = rand() % 10; // 90%=2 ou 10%= 4
                        if (!Apparition)
                        {
                            Grille[Y][X] = 2;
                            Chance++;
                        }
                        else
                        {
                            Grille[Y][X] = 1;
                            Chance = 0;
                        }
                        Statistiques[Grille[Y][X] + 3]++; // Sauvegarde du nombre crÿÿ dans les statistiques
                        /*ML_bmp_16_and(P2[0], X * 15 + 1, Y * 15 + 1); // Dessin du nouveau chiffres*/
                        ggle_bmp_logic(&s, 83, 52, ImTime, 32, 7, LG_OR);

                        /*ML_display_vram();                            // Affichage du nouveau chiffre*/
                        ggl_bitblt(&rs, &s, 131, 80);
                        tmr_delayms(100); // Latence du ÿ l'animation d'apparition du nouveau chiffre
                        /*ML_bmp_16_or(P2[1], X * 15 + 1, Y * 15 + 1);*/
                        ggle_bmp_logic(&s, X * 15 + 1, Y * 15 + 9, P2[1], 16, 16, LG_OR);
                        /*ML_bmp_16_and(P2[Grille[Y][X] + 1], X * 15 + 1, Y * 15 + 1); // Dessin des chiffres
                         * alÿatoire*/
                        ggle_bmp_logic(&s, X * 15 + 1, Y * 15 + 9, P2[Grille[Y][X] + 1], 16, 16, LG_AND);
                        /*ML_bmp_and(ImScore1, 66, 2, 59, 7);                          // Dessin du score*/
						ggl_rect(&s, 66, 10, 125, 17, ggl_mkcolor(0));
                        ggle_bmp_logic(&s, 66, 10, ImScore1, 64, 7, LG_OR);

                        /*ML_display_vram(); // Affichage de la grille*/
                        ggl_bitblt(&rs, &s, 131, 80);

                        TestCase = 0; // Test si le joueur a perdu
                        for (X = 0; X < 4; X++)
                            for (Y = 0; Y < 4; Y++)
                                if (!Grille[Y][X])
                                    TestCase++; // Test si il reste des cases vides sur la grille
                        if (!TestCase)
                        { // Si il n'y a pas de case vide...
                            for (X = 0; X < 4; X++)
                                for (Y = 0; Y < 3; Y++)
                                    if (Grille[Y][X] == Grille[Y + 1][X])
                                        TestCase++; // Test si il y a 2 cases adjacentes ayant le mÿme nombre sur l'axe
                                                    // Y
                            for (Y = 0; Y < 4; Y++)
                                for (X = 0; X < 3; X++)
                                    if (Grille[Y][X] == Grille[Y][X + 1])
                                        TestCase++; // Test si il y a 2 cases adjacentes ayant le mÿme nombre sur l'axe
                                                    // X
                        }

                        // Test de validation des succÿs avec fusion
                        if (NbrFusion)
                        { // Si il y a au moins une fusion
                            NbrCombo++;
                            if (TestFusion2[0])
                            {
                                for (Z2 = 0; Z2 < NbrFusion; Z2++)
                                    for (Z = 0; Z < 8; Z++)
                                        if (TestFusion1[Z2] - 1 == TestFusion2[Z])
                                            TestSuite++;
                                if (TestSuite)
                                {
                                    NbrSuite++;
                                    NbrDesordonne = 1;
                                }
                                else
                                {
                                    NbrDesordonne++;
                                    NbrSuite = 1;
                                }
                            }
                            if (!TestFusion2[0])
                            {
                                NbrSuite = 1;
                                NbrDesordonne = 1;
                            }
                            for (Z = 0; Z < NbrFusion; Z++)
                                TestFusion2[Z] = TestFusion1[Z];
                        }
                        else
                        {
                            for (Z = 0; Z < 8; Z++)
                                TestFusion2[Z] = 0; // Rÿinitialisation des variable qui valide les succÿs avec fusion
                                                    // si aucune fusion n'est rÿalisÿ
                            NbrCombo = 0;
                            NbrSuite = 0;
                            NbrDesordonne = 0;
                        }

                        // Test de tout les succÿ
                        for (Z = 0; Z < 30; Z++)
                            if (MedaillesObtenues[Z] != 1)
                            {
                                Z2 = 0; // Boleen pour savoir si succÿ rÿalisÿ

                                if (Z == 0 &&
                                    Statistiques[1] + (Secondes + Minutes * 100 + Heures * 10000 - TempsPartie) > 3000)
                                    Z2 = 1; // Addiction 1
                                if (Z == 1 &&
                                    Statistiques[1] + (Secondes + Minutes * 100 + Heures * 10000 - TempsPartie) > 13000)
                                    Z2 = 1; // Addiction 2
                                if (Z == 2 &&
                                    Statistiques[1] + (Secondes + Minutes * 100 + Heures * 10000 - TempsPartie) > 43000)
                                    Z2 = 1; // Addiction 3

                                if (Z >= 3 && Z <= 5 && MedaillesObtenues[Z] == 2)
                                    Z2 = 1; // Fusion

                                if (Z == 6 && Score > 7000)
                                    Z2 = 1; // Survie 1
                                if (Z == 7 && Score > 42000)
                                    Z2 = 1; // Survie 2
                                if (Z == 8 && Score > 77000)
                                    Z2 = 1; // Survie 3

                                if (Z == 9 && !TestCase && Score > 300 && Score <= 600)
                                    Z2 = 1; // Kamikaze 1
                                if (Z == 10 && !TestCase && Score > 150 && Score <= 300)
                                    Z2 = 1; // Kamikaze 2
                                if (Z == 11 && !TestCase && Score <= 150)
                                    Z2 = 1; // Kamikaze 3

                                if (ChoixSucceOrganisation == 0 && Z >= 12 && Z <= 14 && NbrCombo == 5 + (Z - 12) * 3)
                                    Z2 = 1; // Combo

                                if (ChoixSucceOrganisation == 1 && Z >= 15 && Z <= 17 && NbrSuite == 3 + (Z - 15) * 3)
                                    Z2 = 1; // Suite

                                if (ChoixSucceOrganisation == 2 && Z >= 18 && Z <= 20 && NbrDesordonne == 3 + (Z - 18))
                                    Z2 = 1; // Dÿsordonnÿ

                                if (ChoixSucceOrganisation == 3 && Z >= 21 && Z <= 23 && NbrFusion == 2 + (Z - 21) * 2)
                                    Z2 = 1; // Eliminiation

                                if (Z >= 24 && Z <= 26)
                                { // Teste Succÿ Artistiques
                                    TestArtistique = 0;
                                    for (X = 0; X < 16; X++)
                                        if (Grille[X / 4][X % 4])
                                            TestArtistique +=
                                                pow(2, X); // Analyse la grille pour les succÿs artistiques
                                    if (Z == 24 && (TestArtistique == 4095 || TestArtistique == 30583 ||
                                                    TestArtistique == 61166 || TestArtistique == 65520))
                                        Z2 = 1; // Artistique 1
                                    if (Z == 25 && (TestArtistique == 4991 || TestArtistique == 36079 ||
                                                    TestArtistique == 63281 || TestArtistique == 65224))
                                        Z2 = 1; // Artistique 2
                                    if (Z == 26 && (TestArtistique == 51 || TestArtistique == 204 ||
                                                    TestArtistique == 13056 || TestArtistique == 52224))
                                        Z2 = 1; // Artistique 3
                                }

                                if (Z == 27 && Chance == 2)
                                    Z2 = 1; // Autre (chance)
                                if (Z == 28 && MedaillesObtenues[28] == 2)
                                    Z2 = 1; // Autre (42)
                                if (Z == 29)
                                { // Autre (rÿussir tout les succÿs)
                                    TestDernierSucce = 0;
                                    for (i = 0; i < 29; i++)
                                        if (!MedaillesObtenues[i])
                                            TestDernierSucce++;
                                    if (!TestDernierSucce)
                                        Z2 = 2;
                                }

                                if (Z2)
                                {
                                    MedaillesObtenues[Z] = 1; // Dÿbloquage du succÿ
                                    Statistiques[3]++;        // Sauvegarde du nombre de succÿs rÿussi
                                    AffTxt = 0;
                                    Defilement = 0;
                                    Ralentissement = 0;
                                    while (!keyb_isKeyPressed(KB_ENT))
                                    { // Attend l'appuis de "EXE"
                                        ggl_rect(&s, 64, 51, 126, 69,
                                                 ggl_mkcolor(0)); // Effaÿage de la 3ÿme zone d'ÿcriture
                                        /*ML_rectangle(64, 52, 126, 60, 1, 1, 0); // Cadre du texte du succÿ*/
                                        ggl_rect(&s, 64, 60, 126, 68,
                                                 ggl_mkcolor(15)); // Effaÿage de la 3ÿme zone d'ÿcriture
                                        ggl_rect(&s, 65, 61, 125, 67,
                                                 ggl_mkcolor(0)); // Effaÿage de la 3ÿme zone d'ÿcriture
                                        if (AffTxt >= 0 && AffTxt < 1000)
                                            /*ML_bmp_or(ImTexteSucces[Z / 3], 65, 44, 61, 7); // Dessin du succÿ
                                             * obtenu*/
                                            ggle_bmp_logic(&s, 65, 52, ImTexteSucces[Z / 3], 64, 7, LG_OR);
                                        if (AffTxt >= 1000)
                                            /*ML_bmp_or(ImExe, 87, 44, 17, 7); // Dessin de "EXE"*/
                                            ggle_bmp_logic(&s, 87, 52, ImExe, 24, 7, LG_OR);

                                        /*if (strlen(TextesSucces[Z]) >= 15)*/
                                        /*{*/
                                        /*strncpy(buffer, TextesSucces[Z] + Defilement, 15);*/
                                        /*buffer[16] = 0;*/
                                        /*Txt_Text(buffer, 66, 54, TXT_MINISD, TXT_OR);*/
                                        /*}*/
                                        /*else*/
                                        /*Txt_Text(TextesSucces[Z], 66, 54, TXT_MINISD, TXT_OR);*/

                                        /*AffTxt++;*/
                                        /*if (AffTxt == 1500)*/
                                        /*AffTxt = 0;*/
                                        /*if (!Defilement)*/
                                        /*Ralentissement++;*/
                                        /*if (!(AffTxt % 50) && Ralentissement > 500 &&*/
                                        /*Defilement < strlen(TextesSucces[Z]) - 15)*/
                                        /*Defilement++;*/
                                        /*if (Defilement == strlen(TextesSucces[Z]) - 15)*/
                                        /*Ralentissement++;*/
                                        /*if (Ralentissement == 1500)*/
                                        /*{*/
                                        /*Ralentissement = 0;*/
                                        /*Defilement = 0;*/
                                        /*}*/

                                        /*ML_display_vram(); // Affichage du message de succÿ*/
                                        ggl_bitblt(&rs, &s, 131, 80);
                                    }
                                    while (keyb_isKeyPressed(KB_ENT))
                                        ;                                          // Attend le relachement de "EXE"
                                    ggl_rect(&s, 64, 51, 126, 69, ggl_mkcolor(0)); // Effaÿage du succÿ
                                                                                   //
                                    ggle_bmp_logic(&s, 83, 52, ImTime, 32, 7, LG_OR);
									ggle_bmp_logic(&s, 71, 61, ImTempsNul, 48, 7, LG_OR);

                                    ggl_rect(&s, 107, 61, 117, 67, ggl_mkcolor(0));
                                    ggle_bmp_logic(&s, 112, 61, Chiffres[Secondes % 10], 8, 7, LG_OR);
                                    ggle_bmp_logic(&s, 106, 61, Chiffres[Secondes / 10], 8, 7, LG_OR);
                                    ggl_rect(&s, 89, 61, 99, 67, ggl_mkcolor(0));
                                    ggle_bmp_logic(&s, 94, 61, Chiffres[Minutes % 10], 8, 7, LG_OR);
                                    ggle_bmp_logic(&s, 88, 61, Chiffres[Minutes / 10], 8, 7, LG_OR);
                                    ggl_rect(&s, 71, 61, 81, 67, ggl_mkcolor(0));
                                    ggle_bmp_logic(&s, 76, 61, Chiffres[Heures % 10], 8, 7, LG_OR);
                                    ggle_bmp_logic(&s, 70, 61, Chiffres[Heures / 10], 8, 7, LG_OR);
                                }
                            } // Fin de la fonction de teste des succÿs

                        for (Z = 0; Z < 8; Z++)
                            TestFusion1[Z] = 0; // Rÿinitialisation des variables qui enregistrent donnÿes relatives aux
                                                // succÿs qui ont ÿtÿ crÿÿ au dernier coups
                        NbrFusion = 0;
                        TestSuite = 0;

                        /*ML_display_vram(); // Affichage du jeu*/
                        ggl_bitblt(&rs, &s, 131, 80);

                    } // Fin des fonctions de test d'aprÿs dÿplacement

                } // Fin des fonctions effectuÿes lors d'un dÿplacement
                if (!TestCase)
                    break;
            }
            if (Direction == 10)
                break; // Condition pour revenir au menu
        }
        if (keyb_isKeyPressed(KB_ON))
            return 0;
    }

    return 0;
}
