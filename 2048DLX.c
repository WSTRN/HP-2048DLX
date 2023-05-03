/*****************************************************************/
/*                                                               */
/*   CASIO fx-9860G SDK Library                                  */
/*                                                               */
/*   File name : [ProjectName].c                                 */
/*                                                               */
/*   Copyright (c) 2006 CASIO COMPUTER CO., LTD.                 */
/*                                                               */
/*****************************************************************/
#include <hpgcc3.h>
#include "port.h"
#include "ggl.h"
#include "main.h"


//****************************************************************************
//  AddIn_main (Sample program main function)
//
//  param   :   isAppli   : 1 = This application is launched by MAIN MENU.
//                        : 0 = This application is launched by a strip in eACT application.
//
//              OptionNum : Strip number (0~3)
//                         (This parameter is only used when isAppli parameter is 0.)
//
//  retval  :   1 = No error / 0 = Error
//
//****************************************************************************

// static int SysCallCode[] = {0xD201422B, 0x60F20000, 0x80010070}; // Truc pour pouvoir utiliser le syscall du temps
// static int (*SysCall)(int R4, int R5, int R6, int R7, int FNo) = (void *)&SysCallCode;

// int RTC_getTicks(void) // Fonction pour pouvoir utiliser le temps en tics 1/128
// {
// 	return (*SysCall)(0, 0, 0, 0, 0x3B); // on d�clare la fonction voulue selon son num�ro (ici 0x3B)
// }

// #define ABS(x) ((x > 0) ? x : -x)

// #define FILEPATH "\\\\fls0\\2048dlx.sav"

// void Read(int *Record, int *Score, int *TempsPartie, uint8_t Grille[4][4], uint8_t *MedaillesObtenues, uint8_t *Statistiques)
// { // Truc qui sers pour la lecture de fichiers
// 	int i;
// 	int handle;
// 	handle = memory_openfile(FILEPATH, _OPENMODE_READ);
// 	memory_readfile(handle, (void *)Record, 4, -1);
// 	memory_readfile(handle, (void *)Score, 4, -1);
// 	memory_readfile(handle, (void *)TempsPartie, 4, -1);
// 	for (i = 0; i < 4; i++)
// 		memory_readfile(handle, (void *)(Grille + i), 4, -1);
// 	memory_readfile(handle, (void *)MedaillesObtenues, 30, -1);
// 	memory_readfile(handle, (void *)Statistiques, 68, -1);
// 	memory_closefile(handle);
// }

// void Save(int Record, int Score, int TempsPartie, uint8_t **Grille, uint8_t *MedaillesObtenues, uint8_t *Statistiques)
// { // Truc qui sers pour la sauvegarde de fichiers
// 	int i;
// 	int handle;
// 	memory_deletefile(FILEPATH);
// 	memory_createfile(FILEPATH, 126);
// 	handle = memory_openfile(FILEPATH, _OPENMODE_WRITE);
// 	memory_writefile(handle, (void *)(&Record), 4);
// 	memory_writefile(handle, (void *)(&Score), 4);
// 	memory_writefile(handle, (void *)(&TempsPartie), 4);
// 	memory_writefile(handle, (void *)Grille, 16);
// 	memory_writefile(handle, (void *)MedaillesObtenues, 30);
// 	memory_writefile(handle, (void *)Statistiques, 68);
// 	memory_closefile(handle);
// }
extern gglsurface rs;
void app_2048_main() // Fonction du code du jeu entier
{
	ggl_rect(&rs, 0, 0, 130, 79, ggl_mkcolor(0));
    ggle_bmp(&rs, 0, 0, fill, 127, 2);
    ggle_bmp(&rs, 0, 2, fill, 127, 2);
    ggle_bmp(&rs, 0, 4, fill, 127, 2);
    ggle_bmp(&rs, 0, 6, fill, 127, 2);
    ggl_rect(&rs, 0, 73, 20, 79, ggl_mkcolor(15));
    ggl_rect(&rs, 22, 73, 42, 79, ggl_mkcolor(15));
    ggl_rect(&rs, 44, 73, 64, 79, ggl_mkcolor(15));
    ggl_rect(&rs, 66, 73, 86, 79, ggl_mkcolor(15));
    ggl_rect(&rs, 88, 73, 108, 79, ggl_mkcolor(15));
    ggl_rect(&rs, 110, 73, 130, 79, ggl_mkcolor(15));
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
	uint8_t TestFusion1[] = {0, 0, 0, 0, 0, 0, 0, 0};
	uint8_t TestFusion2[] = {0, 0, 0, 0, 0, 0, 0, 0};
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

	// TL_Point point1 = {-1, -1};
	// TL_Point point2 = {-1, -1};
	// TL_Point point3 = {-1, -1};

	uint8_t Grille[4][4] = {{0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}};
	uint8_t Boleens1[] = {0, 0, 0, 0};
	uint8_t Boleens2[] = {0, 0, 0, 0};
	unsigned int Statistiques[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

	uint8_t MedaillesObtenues[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};


	const char *TextesSucces[] = {"Jouer + de 30 min", "Jouer + de 1h 30min", "Jouer + de 4h 30min", "Faire un 1024", "Faire un 2048", "Faire un 4096", "Atteinde les 7000pts", "Atteinde les 42000pts", "Atteinde les 77000pts", "Mourir avant 600pts", "Mourir avant 300pts", "Mourir avant 150pts", "Enchainer 5 fusions", "Enchainer 8 fusions", "Enchainer 11 fusions", "3 fusions dans l'ordre", "6 fusions dans l'ordre", "9 fusions dans l'ordre", "3 fusions desordonnees", "4 fusions desordonnees", "5 fusions desordonnees", "2 fusions en meme temps", "4 fusions en meme temps", "6 fusions en meme temps", "Rectangle 3*4", "Triangle rectangle 4*4", "Carre 2*2", "Spawn de 2 '4' d'affile", "Gagner a 6min 42sec pile", "Obtenir tous les succes"};

	
	const uint8_t BandeauStatistiques[] = {0x0, 0x80, 0x0, 0x0, 0x0, 0x20, 0x0, 0x0, 0x0, 0x20, 0x0, 0x0, 0x0, 0x0, 0x8, 0x0, 0x18, 0x0, 0x0, 0x0, 0x0, 0x27, 0xbe, 0x73, 0xe7, 0xa0, 0x0, 0x0, 0x0, 0x0, 0x0, 0xc0, 0x18, 0x86, 0xae, 0xa4, 0xee, 0x28, 0xa2, 0x8a, 0x28, 0xa3, 0x33, 0x9b, 0xb1, 0x3b, 0x89, 0xe0, 0x18, 0x8, 0xa4, 0xaa, 0xa4, 0x2b, 0x36, 0xab, 0x6b, 0x22, 0xaa, 0x22, 0x2a, 0xa9, 0x3, 0xf0, 0x18, 0x84, 0xa4, 0xae, 0xa4, 0x28, 0x94, 0x89, 0x48, 0xa3, 0x33, 0x23, 0x2b, 0xa9, 0x8, 0xc0, 0x7e, 0x2, 0xa4, 0xaa, 0xa4, 0x26, 0x94, 0xa9, 0x46, 0xa2, 0x2a, 0x22, 0x2a, 0xa9, 0x0, 0xc0, 0x3c, 0x8c, 0x4e, 0x4a, 0xa4, 0x28, 0x94, 0xa9, 0x48, 0xa2, 0x2b, 0x9b, 0xb2, 0xa9, 0x8, 0xc0, 0x18, 0x0, 0x0, 0x0, 0x0, 0x2f, 0x1c, 0xd9, 0xcf, 0x20, 0x0, 0x0, 0x0, 0x0, 0x0, 0xc0, 0x0, 0x80, 0x0, 0x0, 0x0, 0x20, 0x0, 0x0, 0x0, 0x20, 0x0, 0x0, 0x0, 0x0, 0x8, 0x0, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf8};
	const char *TexteStatistiques[] = {"Parties ------------", "Temps de jeu total - 00:00:00", "Best time victoire - 00:00:00", "Succes sur 30 ------", "Nombre de 2 --------", "Nombre de 4 --------", "Nombre de 8 --------", "Nombre de 16 -------", "Nombre de 32 -------", "Nombre de 64 -------", "Nombre de 128 ------", "Nombre de 256 ------", "Nombre de 512 ------", "Nombre de 1024 -----", "Nombre de 2048 -----", "Nombre de 4096 -----", "Nombre de 8192 -----"};
	uint8_t *NombreStatistiques[10];

	
	srand(time_getTicks());

	// Txt_Init(FONT_MINISD | FONT_ARCADIUM);

	while (1)
	{

		// if (!memory_exists(FILEPATH))
		// {
		// 	memory_createfile(FILEPATH, 126);
		// 	Save(Record, Score, TempsPartie, Grille, MedaillesObtenues, Statistiques);
		// }

		// Read(&Record, &Score, &TempsPartie, Grille, MedaillesObtenues, Statistiques); // Extrait les informations du fichier

		ML_clear_vram();

		// Dessin de l'interface du menu
		ML_rectangle(0, 0, 64, 62, 1, 1, 0);   // Rectangle de gauche
		ML_rectangle(65, 0, 127, 62, 1, 1, 0); // Rectangle de droite
		ML_horizontal_line(63, 0, 127, 1);	   // Ligne du bas de l'�cran
		ML_bmp_16_or(P2[2], 66, 1);			   // 2
		ML_bmp_16_or(Im0, 81, 1);			   // 0
		ML_bmp_16_or(P2[3], 96, 1);			   // 4
		ML_bmp_16_or(P2[4], 111, 1);		   // 8
		ML_bmp_or(DELUX, 67, 17, 64, 12);	   // DELUX
		ML_bmp_or(ImRecord, 66, 30, 61, 7);	   // Record
		ML_bmp_or(Kirafi, 67, 48, 59, 13);	   // Kirafi

		// Dessin du record
		AffTxt = Record;
		if (AffTxt == 0)
			ML_bmp_or(Chiffres[0], 93, 39, 7, 7); // Si Record=0 dessine un 0
		for (Z = 93 + 3 * (int)(log10(AffTxt)); AffTxt; Z -= 6)
		{
			ML_bmp_or(Chiffres[AffTxt % 10], Z, 39, 7, 7); // Dessin de chaque chiffres du record
			AffTxt /= 10;
		}
		X = 1; //"Continuer" est selectionn� par d�faut
		X2 = X;

		while (1)
		{
			for (Z = 4; Z < 55; Z += 10)
				ML_bmp_or(TexteMenu[((Z - 4) / 10) * 2], 13, Z, 39, 5); // Dessin du texte du menu
			ML_rectangle(13, 4 + X * 10, 51, 8 + X * 10, 0, 0, 0);		// Effa�age du texte selectionn�
			ML_bmp_or(TexteMenu[X * 2 + 1], 4, 3 + X * 10, 57, 7);		// Dessin du texte selectionn�
			Sleep(2);													// Truc anti-bug d'affichage...
			ML_display_vram();											// Affichage du menu
			while (keyb_isKeyPressed(KB_UP) || keyb_isKeyPressed(KB_DN) || keyb_isKeyPressed(KB_ENT))
				; // Attend que les touche haut/bas/EXE soient relach�es
			X2 = X;
			while (X2 == X)
			{
				if (keyb_isKeyPressed(KB_UP))
					X--;
				if (keyb_isKeyPressed(KB_DN))
					X++;
				if (keyb_isKeyPressed(KB_ENT) || keyb_isKeyPressed(KB_ON))
					break; // EXE ou EXIT
			}
			if (X < 0)
				X = 5;
			if (X > 5)
				X = 0;
			ML_rectangle(1, 1, 63, 61, 0, 0, 0); // Effa�age du texte
			if (keyb_isKeyPressed(KB_ENT) || keyb_isKeyPressed(KB_ON))
				break; // EXE ou EXIT pour valider/quitter
		}

		while (keyb_isKeyPressed(KB_ENT))
			; // Attend que EXE soit relach�
		if (keyb_isKeyPressed(KB_ON))
			X = 5;	   // EXIT pour quitter
		ChoixMode = X; // Choix du mode du menu

		if (ChoixMode < 2)
		{ // Fonction du jeu

			// Choix du succ� � pouvoir r�aliser cette session de partie
			// Txt_Text("Quel succe", 3, 3, TXT_ARCADIUM, TXT_OR);
			// Txt_Text("veux - tu", 7, 10, TXT_ARCADIUM, TXT_OR);
			// Txt_Text("realiser ?", 3, 17, TXT_ARCADIUM, TXT_OR);
			X = 0;
			while (1)
			{
				for (Z = 0; Z < 4; Z++)
					ML_bmp_or(ImTexteSucces[Z + 4], 2, 27 + Z * 9, 61, 7); // Dessin des succ�s � selectionner
				ML_rectangle(1, 26 + X * 9, 63, 34 + X * 9, 0, 0, 2);	   // Dessin du succ� selectionn�
				ML_display_vram();										   // Affichage du menu de selection du succ�
				while (keyb_isKeyPressed(KB_UP) || keyb_isKeyPressed(KB_DN) || keyb_isKeyPressed(KB_ENT))
					; // Attend que les touche haut/bas/EXE soient relach�es
				X2 = X;
				while (X2 == X)
				{
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
				ML_rectangle(1, 26, 63, 61, 0, 0, 0); // Effa�age du texte des succ�s
				if (keyb_isKeyPressed(KB_ENT))
					break; // EXE pour valider
			}
			ChoixSucceOrganisation = X;
			while (keyb_isKeyPressed(KB_ENT))
				; // Attend que EXE soit relach�

			if (ChoixMode == 0)
			{
				// Si nouvelle partie, teste si l'ancien score est plus �lev� que le record
				if (Score > Record)
				{																			   // Nouveau record
					Record = Score;															   // Le record prend la valeur du score
					// Save(Record, Score, TempsPartie, Grille, MedaillesObtenues, Statistiques); // Stocke les donn�es dans un fichier
				}
				Score = 0; // R�initialisation du score � z�ro
			}

			while (1)
			{ // Jeu

				ML_clear_vram(); // Effa�age de l'�cran

				// Dessin de l'interface du jeu
				ML_rectangle(0, 0, 62, 62, 1, 1, 0);	// Rectangle de gauche
				ML_rectangle(63, 0, 127, 62, 1, 1, 0);	// Rectangle de Droite
				ML_horizontal_line(63, 0, 127, 1);		// Ligne du bas de l'�cran
				ML_rectangle(64, 20, 126, 21, 1, 1, 0); // Ligne qui s�pare le score et le record
				ML_rectangle(64, 41, 126, 42, 1, 1, 0); // Ligne qui s�pare le record du cadre sp�cial
				ML_bmp_or(ImScore1, 66, 2, 59, 7);		// Score
				ML_bmp_or(ImRecord, 65, 23, 61, 7);		// Record
				ML_bmp_or(ImTime, 83, 44, 25, 7);		// Time

				// Dessin du score
				AffTxt = Score;
				if (AffTxt == 0)
					ML_bmp_or(Chiffres[0], 92, 11, 7, 7); // Si Record=0 dessine un 0
				for (Z = 92 + 3 * (int)(log10(AffTxt)); AffTxt; Z -= 6)
				{
					ML_bmp_or(Chiffres[AffTxt % 10], Z, 11, 7, 7); // Dessin de chaque chiffres du score
					AffTxt /= 10;
				}

				// Dessin du record
				AffTxt = Record;
				if (AffTxt == 0)
					ML_bmp_or(Chiffres[0], 92, 32, 7, 7); // Si Score=0 dessine un 0
				for (Z = 92 + 3 * (int)(log10(AffTxt)); AffTxt; Z -= 6)
				{
					ML_bmp_or(Chiffres[AffTxt % 10], Z, 32, 7, 7); // Dessin de chaque chiffres du record
					AffTxt /= 10;
				}

				// Teste si nouvelle partie
				if (Score == 0)
				{
					TempsPartie = 0; // Initialisation du temps � 00:00:00

					Statistiques[0]++; // Sauvegarde du nombre de partie cr��

					// Initialisation des donn�es de la grille
					for (X = 0; X < 4; X++)
						for (Y = 0; Y < 4; Y++)
							Grille[Y][X] = 0; // Inisialisation de la grille
					for (X = 0; X < 4; X++)
						for (Y = 0; Y < 4; Y++)
							ML_bmp_16_or(P2[1], X * 15 + 1, Y * 15 + 1); // Dessin des cases vides de la grille
					ML_display_vram();									 // Affichage de la grille vide

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
						ML_bmp_16_and(P2[0], X * 15 + 1, Y * 15 + 1); // Dessin des chiffres d'apparition
					}

					ML_display_vram(); // Affichage de l'�cran de jeu

					Sleep(150); // Temps de latence pour l'animmation des premiers nombres
				}				// Fin de le cr�ation de nouvelle partie

				ML_rectangle(0, 0, 62, 62, 1, 1, 0); // Effa�age de la grille
				for (X = 0; X < 4; X++)
					for (Y = 0; Y < 4; Y++)
						ML_bmp_16_or(P2[Grille[Y][X] + 1], X * 15 + 1, Y * 15 + 1); // Dessin la grille

				ML_display_vram(); // Affichage de la grille

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
				// TempsReference = RTC_getTicks();
				while (Secondes != TempsPartie % 100)
				{
					// TempsActuel = RTC_getTicks();
					Secondes = (TempsActuel - TempsReference);
				}
				Minutes = (TempsPartie % 10000) / 100;
				Heures = TempsPartie / 10000;
				TempsReference = TempsActuel;
				TempsSession = 0;

				ML_bmp_or(ImTempsNul, 71, 53, 47, 7);			   // Temps � 00 : 00 : 00
				ML_rectangle(107, 53, 117, 59, 0, 0, 0);		   // Effa�age des secondes
				ML_bmp_or(Chiffres[Secondes % 10], 112, 53, 7, 7); // Dessin des unit�s des secondes
				ML_bmp_or(Chiffres[Secondes / 10], 106, 53, 7, 7); // Dessin des dixaines des secondes
				ML_rectangle(89, 53, 99, 59, 0, 0, 0);			   // Effa�age des minutes
				ML_bmp_or(Chiffres[Minutes % 10], 94, 53, 7, 7);   // Dessin des unit�s des minutes
				ML_bmp_or(Chiffres[Minutes / 10], 88, 53, 7, 7);   // Dessin des dixaines des minutes
				ML_rectangle(71, 53, 81, 59, 0, 0, 0);			   // Effa�age des heures
				ML_bmp_or(Chiffres[Heures % 10], 76, 53, 7, 7);	   // Dessin des unit�s des heures
				ML_bmp_or(Chiffres[Heures / 10], 70, 53, 7, 7);	   // Dessin des dixaines des heures

				while (1)
				{ // Moteur du jeu

					while (keyb_isKeyPressed(KB_RT) || keyb_isKeyPressed(KB_LF) || keyb_isKeyPressed(KB_UP) || keyb_isKeyPressed(KB_DN))
					{ // Attend le relachement des touches directionnelles
						// Incr�mentation du score
						// TempsActuel = RTC_getTicks();
						if ((TempsActuel - TempsReference) / 128)
						{
							// TempsReference = RTC_getTicks();
							Secondes++; // Secondes
							if (Secondes >= 60)
							{
								Minutes++; // Minutes
								if (Minutes >= 60)
								{
									Heures++;										// Heures
									ML_rectangle(71, 53, 81, 59, 0, 0, 0);			// Effa�age des heures
									ML_bmp_or(Chiffres[Heures % 10], 76, 53, 7, 7); // Dessin des unit�s des heures
									ML_bmp_or(Chiffres[Heures / 10], 70, 53, 7, 7); // Dessin des dixaines des heures
									Minutes = 0;									// R�initialisation des minutes
								}
								ML_rectangle(89, 53, 99, 59, 0, 0, 0);			 // Effa�age des minutes
								ML_bmp_or(Chiffres[Minutes % 10], 94, 53, 7, 7); // Dessin des unit�s des minutes
								ML_bmp_or(Chiffres[Minutes / 10], 88, 53, 7, 7); // Dessin des dixaines des minutes
								Secondes = 0;									 // R�initialisation des secondes
							}
							ML_rectangle(107, 53, 117, 59, 0, 0, 0);		   // Effa�age des secondes
							ML_bmp_or(Chiffres[Secondes % 10], 112, 53, 7, 7); // Dessin des unit�s des secondes
							ML_bmp_or(Chiffres[Secondes / 10], 106, 53, 7, 7); // Dessin des dixaines des secondes

							ML_display_vram(); // Affichage du temps
						}
					}

					// Le joueur choisie une direction
					Direction = 0; // R�initialisation de la direction
					while (Direction == 0)
					{ // Le joueur choisi une direction (les chiffres correspondent � leur fl�che sur le clavier)

						do
						{ // Tant qu'un point n'a pas ete presse, ou une touche du replay
							// TL_getTouchXY(&point1);
							if (keyb_isKeyPressed(KB_RT))
								Direction = 3;
							if (keyb_isKeyPressed(KB_LF))
								Direction = 1;
							if (keyb_isKeyPressed(KB_UP))
								Direction = 8;
							if (keyb_isKeyPressed(KB_DN))
								Direction = 5;
							if (keyb_isKeyPressed(KB_ON))
								Direction = 10; // Touche [MENU] pour retourner au menu
							if (keyb_isKeyPressed(KB_C))
							{ // Touche [OPTN] pour passer l'animation des chiffres on/off
								if (ChoixAnimation)
									ChoixAnimation = 0;
								else
									ChoixAnimation = 1;
								while (keyb_isKeyPressed(KB_C))
									;
							}
							// Incr�mentation du score
							// TempsActuel = RTC_getTicks();
							if ((TempsActuel - TempsReference) / 128)
							{
								// TempsReference = RTC_getTicks();
								Secondes++; // Secondes
							}
							if (Secondes >= 60)
							{
								Minutes++; // Minutes
								if (Minutes >= 60)
								{
									Heures++;										// Heures
									ML_rectangle(71, 53, 81, 59, 0, 0, 0);			// Effa�age des heures
									ML_bmp_or(Chiffres[Heures % 10], 76, 53, 7, 7); // Dessin des unit�s des heures
									ML_bmp_or(Chiffres[Heures / 10], 70, 53, 7, 7); // Dessin des dixaines des heures
									Minutes = 0;									// R�initialisation des minutes
								}
								ML_rectangle(89, 53, 99, 59, 0, 0, 0);			 // Effa�age des minutes
								ML_bmp_or(Chiffres[Minutes % 10], 94, 53, 7, 7); // Dessin des unit�s des minutes
								ML_bmp_or(Chiffres[Minutes / 10], 88, 53, 7, 7); // Dessin des dixaines des minutes
								Secondes = 0;									 // R�initialisation des secondes
							}
							ML_rectangle(107, 53, 117, 59, 0, 0, 0);		   // Effa�age des secondes
							ML_bmp_or(Chiffres[Secondes % 10], 112, 53, 7, 7); // Dessin des unit�s des secondes
							ML_bmp_or(Chiffres[Secondes / 10], 106, 53, 7, 7); // Dessin des dixaines des secondes

							ML_display_vram(); // Affichage du temps

						} while ( !Direction);

						if (Direction)
							break; // Si on a deja appuye sur une touchedu replay, inutile de continuer

						// i = 10; // Sert a savoir si on  bien retire le doigt ou si c'est juste temporaire

						// do
						// {
						// 	if (point2.x >= 0) // si on appuie sur un point, on met a jour le 3eme point (voir note /**/ ci-dessous) et le "timer"
						// 	{
						// 		point3.x = point2.x;
						// 		point3.y = point2.y;
						// 		i = 10;
						// 	}
						// 	else
						// 	{
						// 		i--;
						// 	}

						// 	TL_getTouchXY(&point2);
						// } while (i); // Tant qu'on a pas relache de touche pendant 30 frames, on continue de mettre a jour

						// /* le fait d'utiliser ci-dessus un troisieme point permet de garder en memoire la valeur du dernier point sur lequel on appuie, sinon on aurait tout le temps {-1, -1} */

						// i = point3.x - point1.x;
						// j = point3.y - point1.y;

						// if (ABS(i) > ABS(j)) // Si le deplacement le plus important est celui des x
						// {
						// 	Direction = (i < 0) ? 1 : 3; // On donne la valeur du deplacement en fonction des deplacements effectues
						// }
						// else // Idem pour les y
						// {
						// 	Direction = (j < 0) ? 8 : 5; // Ces conditions condens�es reviennent a faire "if(j<0) Direction=8; else Direction=5;"
						// }
					} // Fin de la boucle de choix d'une direction

					// Condition pour revenir au menu
					if (Direction == 10)
					{
						TempsSession = Secondes + Minutes * 100 + Heures * 10000;
						Statistiques[1] += TempsSession - TempsPartie;
						TempsPartie = TempsSession;
						if (Statistiques[1] % 100 > 59)
							Statistiques[1] += 40;
						if (Statistiques[1] % 10000 / 100 > 59)
							Statistiques[1] += 4000;
						// Save(Record, Score, TempsPartie, Grille, MedaillesObtenues, Statistiques); // Sauvegarde de la partie
						break;																	   // Retour au menu
					}

					// Condition qui d�place les nombres
					if (Direction != 10)
					{
						TestCoups = 0;
						for (Z = 0; Z < 4; Z++)
						{ // R�initialisation les collisions � z�ro
							Boleens1[Z] = 0;
							Boleens2[Z] = 0;
						}
						for (NbrDeplacement = 0; NbrDeplacement < 3; NbrDeplacement++)
						{ // Le nombre de d�placement
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
											X = E; // Coordonn�es de la case � d�placer
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
											X2 = X - 1; // Coordonn�es de la case vis�
										if (Direction == 3)
											X2 = X + 1;
										if (Direction == 8)
											Y2 = Y - 1;
										if (Direction == 5)
											Y2 = Y + 1;
										Case1 = Grille[Y][X];	// Case � d�placer
										Case2 = Grille[Y2][X2]; // Case vis�
										if (Case1)
										{ // Si il y a un nombre dans la case � d�placer
											if (!Case2)
											{ // Si il n'y a rien dans la case vis�, on y d�place le nombre K
												Grille[Y2][X2] = Case1;
												Grille[Y][X] = 0;
												if (ChoixAnimation)
												{
													ML_bmp_16_or(P2[1], X * 15 + 1, Y * 15 + 1); // Affichage du mouvement des nombres
													ML_bmp_16_and(P2[Grille[Y2][X2] + 1], X2 * 15 + 1, Y2 * 15 + 1);
												}
												TestCoups = 1; // Un coup viens d'�tre jou�
											}
											if (Case2 == Case1)
											{					 // Si les 2 nombres sont les m�me, �a fusionne
												Boleens2[J] = E; // Param�tres anti-double-fusion
												Case2++;
												if (Case2 == 11 && !Gagne)
													Gagne = 1; // Le 2048 apparait !
												Grille[Y2][X2] = Case2;
												Grille[Y][X] = 0;
												if (ChoixAnimation)
												{
													ML_bmp_16_or(P2[1], X * 15 + 1, Y * 15 + 1); // Affichage du mouvement des nombres
													ML_bmp_16_or(P2[1], X2 * 15 + 1, Y2 * 15 + 1);
													ML_bmp_16_and(P2[0], X2 * 15 + 1, Y2 * 15 + 1);
													ML_bmp_16_and(P2[Grille[Y2][X2] + 1], X2 * 15 + 1, Y2 * 15 + 1);
												}
												TestCoups = 1;
												Score += pow(2, Case2);			   // Augmentation du score
												ML_bmp_or(ImScore2, 66, 2, 59, 7); // Dessin de l'annimation du score

												for (Z = 3; Z < 6; Z++)
													if (Case2 == Z + 7 && !MedaillesObtenues[Z])
														MedaillesObtenues[Z] = 2; // Test si les succ�s de Fusion sont r�alis�es

												Statistiques[Case2 + 3]++;		// Sauvegarde du nombre cr�� dans les statistiques
												TestFusion1[NbrFusion] = Case2; // Enregistrement des nombres de fusion
												NbrFusion++;					// Enregistrement du nombre de fusion r�alis� pour ce coups
											}
										}
									}
								}
								if (ChoixAnimation)
								{
									ML_display_vram(); // Affichage du d�placement des nombre
									Sleep(20);
								}
							}
						} // Fin du d�placement des cases

						TestCase = 1;
						if (TestCoups)
						{			  // Si un coups viens d'�tre jou�
							Sleep(2); // Truc anti-bug d'affichage...

							ML_rectangle(0, 0, 62, 62, 1, 1, 0); // Effa�age de la grille
							for (X = 0; X < 4; X++)
								for (Y = 0; Y < 4; Y++)
									ML_bmp_16_or(P2[Grille[Y][X] + 1], X * 15 + 1, Y * 15 + 1); // Dessin de la grille

							ML_rectangle(64, 10, 126, 18, 1, 0, 0); // Effa�age du score
							AffTxt = Score;
							if (AffTxt == 0)
								ML_bmp_or(Chiffres[0], 92, 11, 7, 7); // Si Score=0, Dessine un 0
							for (Z = 92 + 3 * (int)(log10(AffTxt)); AffTxt; Z -= 6)
							{
								ML_bmp_or(Chiffres[AffTxt % 10], Z, 11, 7, 7); // Dessin de chaque chiffre du score
								AffTxt /= 10;
							}

							if (Gagne == 1)
							{
								if (!MedaillesObtenues[28] && Secondes + Minutes * 100 + Heures * 10000 == 642)
									MedaillesObtenues[28] = 2;			// Test du succ� 42
								ML_rectangle(64, 43, 126, 61, 0, 0, 0); // Effa�age de la 3�me zone d'�criture
								ML_bmp_or(ImGagne, 65, 44, 61, 16);		// Dessin du message de victoire "Gagn�"
							}
							ML_display_vram(); // Affichage du jeu

							if (Gagne == 1)
							{
								while (!keyb_isKeyPressed(KB_ENT))
									; // Attend l'appuis de [EXE] pour continuer � jouer
								while (keyb_isKeyPressed(KB_ENT))
									;									// Attend que [EXE] soit relach�
								Gagne = 2;								// Change la valeur pour que le joueur ne gagne pas plusieurs fois
								ML_rectangle(64, 43, 126, 61, 0, 0, 0); // Effa�age de la 3�me zone d'�criture
								if (Secondes + Minutes * 100 + Heures * 10000 < Statistiques[2] || !Statistiques[2])
								{
									Statistiques[2] = Secondes + Minutes * 100 + Heures * 10000; // Meilleur temps victoire
									ML_bmp_or(TexteMenu[1], 67, 44, 57, 7);						 // Dessin de "Nouveau"
									ML_bmp_or(ImTime, 83, 53, 25, 7);							 // Dessin de "TIME"
									ML_display_vram();
									while (!keyb_isKeyPressed(KB_ENT))
										; // Attend l'appuis de [EXE] pour continuer � jouer
									while (keyb_isKeyPressed(KB_ENT))
										;									// Attend que [EXE] soit relach�
									ML_rectangle(64, 43, 126, 61, 0, 0, 0); // Effa�age de la 3�me zone d'�criture
								}
								ML_bmp_or(ImTime, 83, 44, 25, 7);				   // Time
								ML_bmp_or(ImTempsNul, 71, 53, 47, 7);			   // Temps � 00 : 00 : 00
								ML_rectangle(107, 53, 117, 59, 0, 0, 0);		   // Effa�age des secondes
								ML_bmp_or(Chiffres[Secondes % 10], 112, 53, 7, 7); // Dessin des unit�s des secondes
								ML_bmp_or(Chiffres[Secondes / 10], 106, 53, 7, 7); // Dessin des dixaines des secondes
								ML_rectangle(89, 53, 99, 59, 0, 0, 0);			   // Effa�age des minutes
								ML_bmp_or(Chiffres[Minutes % 10], 94, 53, 7, 7);   // Dessin des unit�s des minutes
								ML_bmp_or(Chiffres[Minutes / 10], 88, 53, 7, 7);   // Dessin des dixaines des minutes
								ML_rectangle(71, 53, 81, 59, 0, 0, 0);			   // Effa�age des heures
								ML_bmp_or(Chiffres[Heures % 10], 76, 53, 7, 7);	   // Dessin des unit�s des heures
								ML_bmp_or(Chiffres[Heures / 10], 70, 53, 7, 7);	   // Dessin des dixaines des heures
							}

							while (Grille[Y][X])
							{
								X = rand() % 4; // Cr�ation al�atoire des coordonn�es du nouveau chiffre de la grille
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
							Statistiques[Grille[Y][X] + 3]++;			  // Sauvegarde du nombre cr�� dans les statistiques
							ML_bmp_16_and(P2[0], X * 15 + 1, Y * 15 + 1); // Dessin du nouveau chiffres
							ML_display_vram();							  // Affichage du nouveau chiffre
							Sleep(100);									  // Latence du � l'animation d'apparition du nouveau chiffre
							ML_bmp_16_or(P2[1], X * 15 + 1, Y * 15 + 1);
							ML_bmp_16_and(P2[Grille[Y][X] + 1], X * 15 + 1, Y * 15 + 1); // Dessin des chiffres al�atoire
							ML_bmp_and(ImScore1, 66, 2, 59, 7);							 // Dessin du score

							ML_display_vram(); // Affichage de la grille

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
											TestCase++; // Test si il y a 2 cases adjacentes ayant le m�me nombre sur l'axe Y
								for (Y = 0; Y < 4; Y++)
									for (X = 0; X < 3; X++)
										if (Grille[Y][X] == Grille[Y][X + 1])
											TestCase++; // Test si il y a 2 cases adjacentes ayant le m�me nombre sur l'axe X
							}

							// Test de validation des succ�s avec fusion
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
									TestFusion2[Z] = 0; // R�initialisation des variable qui valide les succ�s avec fusion si aucune fusion n'est r�alis�
								NbrCombo = 0;
								NbrSuite = 0;
								NbrDesordonne = 0;
							}

							// Test de tout les succ�
							for (Z = 0; Z < 30; Z++)
								if (MedaillesObtenues[Z] != 1)
								{
									Z2 = 0; // Boleen pour savoir si succ� r�alis�

									if (Z == 0 && Statistiques[1] + (Secondes + Minutes * 100 + Heures * 10000 - TempsPartie) > 3000)
										Z2 = 1; // Addiction 1
									if (Z == 1 && Statistiques[1] + (Secondes + Minutes * 100 + Heures * 10000 - TempsPartie) > 13000)
										Z2 = 1; // Addiction 2
									if (Z == 2 && Statistiques[1] + (Secondes + Minutes * 100 + Heures * 10000 - TempsPartie) > 43000)
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
										Z2 = 1; // D�sordonn�

									if (ChoixSucceOrganisation == 3 && Z >= 21 && Z <= 23 && NbrFusion == 2 + (Z - 21) * 2)
										Z2 = 1; // Eliminiation

									if (Z >= 24 && Z <= 26)
									{ // Teste Succ� Artistiques
										TestArtistique = 0;
										for (X = 0; X < 16; X++)
											if (Grille[X / 4][X % 4])
												TestArtistique += pow(2, X); // Analyse la grille pour les succ�s artistiques
										if (Z == 24 && (TestArtistique == 4095 || TestArtistique == 30583 || TestArtistique == 61166 || TestArtistique == 65520))
											Z2 = 1; // Artistique 1
										if (Z == 25 && (TestArtistique == 4991 || TestArtistique == 36079 || TestArtistique == 63281 || TestArtistique == 65224))
											Z2 = 1; // Artistique 2
										if (Z == 26 && (TestArtistique == 51 || TestArtistique == 204 || TestArtistique == 13056 || TestArtistique == 52224))
											Z2 = 1; // Artistique 3
									}

									if (Z == 27 && Chance == 2)
										Z2 = 1; // Autre (chance)
									if (Z == 28 && MedaillesObtenues[28] == 2)
										Z2 = 1; // Autre (42)
									if (Z == 29)
									{ // Autre (r�ussir tout les succ�s)
										TestDernierSucce = 0;
										for (i = 0; i < 29; i++)
											if (!MedaillesObtenues[i])
												TestDernierSucce++;
										if (!TestDernierSucce)
											Z2 = 2;
									}

									if (Z2)
									{
										MedaillesObtenues[Z] = 1; // D�bloquage du succ�
										Statistiques[3]++;		  // Sauvegarde du nombre de succ�s r�ussi
										AffTxt = 0;
										Defilement = 0;
										Ralentissement = 0;
										while (!keyb_isKeyPressed(KB_ENT))
										{											// Attend l'appuis de "EXE"
											ML_rectangle(64, 43, 126, 61, 0, 0, 0); // Effa�age de la 3�me zone d'�criture
											ML_rectangle(64, 52, 126, 60, 1, 1, 0); // Cadre du texte du succ�
											if (AffTxt >= 0 && AffTxt < 1000)
												ML_bmp_or(ImTexteSucces[Z / 3], 65, 44, 61, 7); // Dessin du succ� obtenu
											if (AffTxt >= 1000)
												ML_bmp_or(ImExe, 87, 44, 17, 7); // Dessin de "EXE"

											if (strlen(TextesSucces[Z]) >= 15)
											{
												strncpy(buffer, TextesSucces[Z] + Defilement, 15);
												buffer[16] = 0;
												// Txt_Text(buffer, 66, 54, TXT_MINISD, TXT_OR);
											}
											else
												// Txt_Text(TextesSucces[Z], 66, 54, TXT_MINISD, TXT_OR);

											AffTxt++;
											if (AffTxt == 1500)
												AffTxt = 0;
											if (!Defilement)
												Ralentissement++;
											if (!(AffTxt % 50) && Ralentissement > 500 && Defilement < strlen(TextesSucces[Z]) - 15)
												Defilement++;
											if (Defilement == strlen(TextesSucces[Z]) - 15)
												Ralentissement++;
											if (Ralentissement == 1500)
											{
												Ralentissement = 0;
												Defilement = 0;
											}

											ML_display_vram(); // Affichage du message de succ�
										}
										while (keyb_isKeyPressed(KB_ENT))
											;											   // Attend le relachement de "EXE"
										ML_rectangle(64, 43, 126, 61, 0, 0, 0);			   // Effa�age du succ�
										ML_bmp_or(ImTime, 83, 44, 25, 7);				   // Dessin de Time
										ML_bmp_or(ImTempsNul, 71, 53, 47, 7);			   // Dessin du temps � 00 : 00 : 00
										ML_rectangle(107, 53, 117, 59, 0, 0, 0);		   // Effa�age des secondes
										ML_bmp_or(Chiffres[Secondes % 10], 112, 53, 7, 7); // Dessin des unit�s des secondes
										ML_bmp_or(Chiffres[Secondes / 10], 106, 53, 7, 7); // Dessin des dixaines des secondes
										ML_rectangle(89, 53, 99, 59, 0, 0, 0);			   // Effa�age des minutes
										ML_bmp_or(Chiffres[Minutes % 10], 94, 53, 7, 7);   // Dessin des unit�s des minutes
										ML_bmp_or(Chiffres[Minutes / 10], 88, 53, 7, 7);   // Dessin des dixaines des minutes
										ML_rectangle(71, 53, 81, 59, 0, 0, 0);			   // Effa�age des heures
										ML_bmp_or(Chiffres[Heures % 10], 76, 53, 7, 7);	   // Dessin des unit�s des heures
										ML_bmp_or(Chiffres[Heures / 10], 70, 53, 7, 7);	   // Dessin des dixaines des heures
									}
								} // Fin de la fonction de teste des succ�s

							for (Z = 0; Z < 8; Z++)
								TestFusion1[Z] = 0; // R�initialisation des variables qui enregistrent donn�es relatives aux succ�s qui ont �t� cr�� au dernier coups
							NbrFusion = 0;
							TestSuite = 0;

							ML_display_vram(); // Affichage du jeu

						} // Fin des fonctions de test d'apr�s d�placement

					} // Fin des fonctions effectu�es lors d'un d�placement

					if (!TestCase)
						break; // Si aucun coups ne peut �tre jou� au prochain tour, on sort de la boucle du moteur du jeu et le joueur a perdu

				} // Fin de la boucle du moteur du jeu

				if (Direction == 10)
					break; // Condition pour revenir au menu

				if (Score > Record)
				{										   // Teste si nouveau record
					Record = Score;						   // Le score s'enregistre dans le record
					ML_rectangle(67, 2, 123, 9, 1, 0, 0);  // Effa�age du "Score"
					ML_bmp_or(TexteMenu[1], 67, 2, 57, 7); // Dessin de "Nouveau"
				}

				Score = 0; // R�initialisation du score
				TempsSession = Secondes + Minutes * 100 + Heures * 10000;
				Statistiques[1] += TempsSession - TempsPartie;
				TempsPartie = TempsSession;
				// Save(Record, Score, TempsPartie, Grille, MedaillesObtenues, Statistiques); // Stocke les donn�es dans le fichier de sauvegarde de partie
				ML_rectangle(64, 43, 126, 61, 0, 0, 0);									   // Effa�age de la 3�me zone d'�criture
				ML_bmp_or(ImPerdu, 65, 44, 63, 7);										   // Dessin de "Perdu"
				ML_bmp_or(ImExe, 87, 53, 17, 7);										   // Dessin de "EXE"
				ML_display_vram();														   // Affichage de l'�cran de d�faite

				while (!keyb_isKeyPressed(KB_ENT))
					; // Attend l'appuis de [EXE]
				break;

			} // Fin de la boucle du jeu

		} // Fin de la fonction du jeu

		// Selection de "Succes"
		if (ChoixMode == 2)
		{
			X = 0;
			Z2 = 0;
			while (1)
			{
				// Dessin de l'interface des succ�s
				ML_rectangle(0, 0, 126, 62, 1, 1, 0);							 // Effa�age de l'�cran tout en dessinant les bordure de profondeur
				// Txt_Text("<F1", 2, 13, TXT_MINISD, TXT_OR);						 // F1
				// Txt_Text("F6>", 114, 13, TXT_MINISD, TXT_OR);					 // F6
				ML_horizontal_line(20, 1, 125, 1);								 // Ligne de s�paration des medailles et du bandeau 2
				ML_vertical_line(42, 20, 62, 3);								 // 1�re ligne de s�paration entre les medailles
				ML_vertical_line(84, 20, 62, 3);								 // 2�me ligne de s�paration entre les medailles
				// ML_bmp_or(BandeauSucces, 1, 1, 125, 10);						 // Bandeau de succ�s
				ML_rectangle(2 + X * 6, 1, 70 + X * 6, 10, 0, 0, 0);			 // Effa�age des succ�s cach�s par la selection
				// ML_bmp_or(SelectSucce, 2 + X * 6, 1, 69, 10);					 // Succ� selectionn�
				ML_bmp_or(ImTexteSucces[X], 6 + X * 6, 2, 61, 7);				 // Nom du succ�
				ML_rectangle(14, 12, 112, 18, 0, 0, 1);							 // Rectangle noir, fond de texte d'obtention du succ� s�lectionn�
				// Txt_Text(TextesSucces[Z2 + X * 3], 16, 13, TXT_MINISD, TXT_XOR); // Texte d'obtention du succ� s�lectionn�
				for (Z = 0; Z < 3; Z++)
					// ML_bmp_or(ImMedailles[(X * 3 + Z + 1) * MedaillesObtenues[X * 3 + Z]], 2 + Z * 42, 22, 39, 39); // Les 3 m�dailles
				ML_rectangle(1 + Z2 * 42, 21, 41 + Z2 * 42, 61, 0, 0, 2);											// M�daille s�lectionn�

				ML_display_vram(); // Affichage de l'�cran des succ�s

				while (keyb_isKeyPressed(KB_RT) || keyb_isKeyPressed(KB_LF) || keyb_isKeyPressed(KB_A) || keyb_isKeyPressed(KB_F))
					; // Attend que droite/gauche /F1/F6 soient relach�
				X2 = X;
				Z = Z2;
				while (X == X2 && Z2 == Z)
				{
					if (keyb_isKeyPressed(KB_RT))
						X++;
					if (keyb_isKeyPressed(KB_LF))
						X--;
					if (keyb_isKeyPressed(KB_F))
						Z2++;
					if (keyb_isKeyPressed(KB_A))
						Z2--;
					if (keyb_isKeyPressed(KB_ON))
						break; //[MENU] pour retourner au menu
				}
				if (X < 0)
					X = 9;
				if (X > 9)
					X = 0;
				if (Z2 < 0)
					Z2 = 2;
				if (Z2 > 2)
					Z2 = 0;
				if (keyb_isKeyPressed(KB_ON))
					break; //[MENU] pour retourner au menu
			}
		}

		// Selection de "Stats"
		if (ChoixMode == 3)
		{
			ML_rectangle(0, 0, 126, 62, 1, 1, 0);		   // Effa�age de l'�cran tout en dessinant les bordure de profondeur
			ML_bmp_or(BandeauStatistiques, 1, 1, 125, 10); // Dessin du bandeau des statistique
			X = 0;
			while (1)
			{
				ML_rectangle(1, 11, 125, 61, 0, 0, 0); // Effa�age du texte des statistique
				for (Z = 0; Z < 7; Z++)
					// Txt_Text(TexteStatistiques[X + Z], 3, 13 + Z * 7, TXT_MINISD, TXT_OR); // Dessin du texte des statistiques

				for (Z = 0; Z < 7; Z++)
				{
					if (Z + X < 1 || Z + X > 2)
					{
						sprintf(NombreStatistiques, "%d", Statistiques[X + Z]);
						// Txt_Text(NombreStatistiques, 87, 13 + Z * 7, TXT_MINISD, TXT_OR); // Dessin des nombres correspondant au texte des statistiques
					}
					else
					{
						AffTxt = Statistiques[X + Z] % 10;
						sprintf(NombreStatistiques, "%d", AffTxt);
						// Txt_Text(NombreStatistiques, 115, 13 + Z * 7, TXT_MINISD, TXT_ON);
						AffTxt = Statistiques[X + Z] % 100 / 10;
						sprintf(NombreStatistiques, "%d", AffTxt);
						// Txt_Text(NombreStatistiques, 111, 13 + Z * 7, TXT_MINISD, TXT_ON);
						AffTxt = Statistiques[X + Z] % 1000 / 100;
						sprintf(NombreStatistiques, "%d", AffTxt);
						// Txt_Text(NombreStatistiques, 103, 13 + Z * 7, TXT_MINISD, TXT_ON);
						AffTxt = Statistiques[X + Z] % 10000 / 1000;
						sprintf(NombreStatistiques, "%d", AffTxt);
						// Txt_Text(NombreStatistiques, 99, 13 + Z * 7, TXT_MINISD, TXT_ON);
						AffTxt = Statistiques[X + Z] % 100000 / 10000;
						sprintf(NombreStatistiques, "%d", AffTxt);
						// Txt_Text(NombreStatistiques, 91, 13 + Z * 7, TXT_MINISD, TXT_ON);
						AffTxt = Statistiques[X + Z] / 100000;
						sprintf(NombreStatistiques, "%d", AffTxt);
						// Txt_Text(NombreStatistiques, 87, 13 + Z * 7, TXT_MINISD, TXT_ON);
					}
				}
				ML_display_vram(); // Affichage du texte

				while (keyb_isKeyPressed(KB_DN) || keyb_isKeyPressed(KB_UP))
					; // Attend que haut/bas soient relach�

				ML_rectangle(1, 1, 125, 10, 0, 0, 0);		   // Effa�age du bandeau des statistique
				ML_bmp_or(BandeauStatistiques, 1, 1, 125, 10); // Dessin du bandeau des statistique
				ML_display_vram();							   // Affichage du bandeau des statistique
				X2 = X;
				while (X == X2)
				{
					if (keyb_isKeyPressed(KB_DN))
						X++;
					if (keyb_isKeyPressed(KB_UP))
						X--;
					if (keyb_isKeyPressed(KB_ON))
						break; //[MENU] pour retourner au menu
				}
				if (X > X2)
					ML_rectangle(1, 1, 42, 9, 0, 0, 2);
				if (X < X2)
					ML_rectangle(76, 1, 125, 9, 0, 0, 2);
				if (X < 0)
					X = 10;
				if (X > 10)
					X = 0;
				if (keyb_isKeyPressed(KB_ON))
					break; //[MENU] pour retourner au menu
			}
		}

		// Selection de "Credit"
		if (ChoixMode == 4)
		{
			Z = 0;
			while (!keyb_isKeyPressed(KB_ENT))
			{
				Z++;
				if (Z == 1)
				{
					ML_clear_vram();					 // Effa�age de l'�cran
					// ML_bmp_or(ImCredits, 0, 0, 128, 64); // Dessin de l'image des cr�dits
					ML_display_vram();					 // Affichage de l'image des cr�dits
				}
				if (Z == 20000)
				{
					ML_rectangle(114, 55, 126, 61, 1, 1, 1); // Effa�age de "EXE"
					ML_display_vram();						 // Dessin de l'image des cr�dit sans "EXE"
				}
				if (Z == 30000)
					Z = 0;
			}
		}

		if (ChoixMode == 5)
			break; // Retour au menu de la calculatrice

	} // Fin du programme
	return 1;
}


