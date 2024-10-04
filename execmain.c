#include <STDIO.H>
#include <CONIO.H>
#include <ERRNO.H>
#include <STDLIB.H>
#include <STRING.H>
#include <PROCESS.H>
#include "SOUREXEC/EXECCLAV.H"
#include "SOUREXEC/EXECGRAP.H"
#include "SOUREXEC/EXECOUTI.H"
#include "SOUREXEC/EXECCHAR.H"
extern void Page_Regle (void);
extern void Page_Tableaux (void);
extern void Former_Acces_Fichier (char*,short,short);
extern BOOL Verifier_Tableau (short);
extern BOOL Verifier_Serie (short);
extern BOOL Verifier_Tableaux (void);
extern void Page_Scores (BOOL);
void Afficher_Presentation (void);
char NOM_TABLEAU [32] = "LEVELS01/LEVEL";
short numero_tableau = 1;
short numero_serie = 1;
BOOL hasard = OFF;
enreg_menu menu1;
void main (void)
{
    BOOL exec;
    BOOL etat;
    int retour;
    char stab [3];
    char bufrep [9];
    Activer_Ecran ();
    Installer_Clavier_Interruption ();
    Lire_Palette ("SPRFILES/COULEURS.PAL");
    Afficher_Page (0);
    Definir_Bobs ();
    menu1.page = PAGE1;
    menu1.select = 0;
    menu1.cl_car1 = 96;
    menu1.cl_car2 = 112;
    menu1.cl_fond = 255;
    menu1.y_ecran = 210;
    menu1.largeur_ecran = 320;
    menu1.hauteur_option_maxi = 130;
    menu1.nombre_option = 6;
    menu1.echelle_x = 1;
    menu1.echelle_y = 2;
    strcpy (menu1.option[0],"JOUER");
    strcpy (menu1.option[1],"TABLEAUX");
    strcpy (menu1.option[2],"EDITEUR");
    strcpy (menu1.option[3],"REGLE");
    strcpy (menu1.option[4],"SCORES");
    strcpy (menu1.option[5],"QUITTER");
    Afficher_Presentation ();
    do
    {
        Select_Option (PAGE1,&menu1);
        switch (menu1.select)
        {
        case 0:
        {
            etat = Verifier_Serie (numero_serie);
            if (etat == VRAI)
            {
                exec = FAUX;
                if (hasard == ON)
                {
                    etat = Verifier_Tableaux ();
                    if (etat == VRAI)
                    {
                        sprintf(stab,"%d",-1);
                        exec = VRAI;
                    }
                }
                if (hasard == OFF)
                {
                    etat = Verifier_Tableau (numero_tableau);
                    if (etat == VRAI)
                    {
                        sprintf(stab,"%d",numero_tableau);
                        exec = VRAI;
                    }
                }
                if (exec == VRAI)
                {
                    Former_Acces_Fichier (NOM_TABLEAU,
                                          numero_serie,
                                          numero_tableau);
                    strncpy (bufrep,NOM_TABLEAU,8);
                    *(bufrep + 8) = 0;
                    Desinstaller_Clavier_Interruption ();
                    retour = spawnl (P_WAIT,"SNAKLES.EXE","0",bufrep,stab,NULL);
                    if (retour == -1)
                    {
                        Desactiver_Ecran ();
                        Supprimer_Bobs ();
                        if (errno == E2BIG )
                            cprintf ("\n\rliste des arguments est trop longue");
                        if (errno == EACCES)
                            cprintf ("\n\rAcces au fichier est refusee");
                        if (errno == EMFILE)
                            cprintf ("\n\rTrop de fichier ouverts simultanement");
                        if (errno == ENOENT)
                            cprintf ("\n\rFichier ou chemin d'acces non trouve");
                        if (errno == ENOMEM)
                            cprintf ("\n\rEspace memoire insuffisant");
                        exit (EXIT_SUCCESS);
                    }
                    Activer_Ecran ();
                    Installer_Clavier_Interruption ();
                    Lire_Palette ("SPRFILES/COULEURS.PAL");
                    Afficher_Page (PAGE1);
                    Page_Scores (SAISIE_ON);
                    Afficher_Presentation ();
                }
            }
            break;
        }
        case 1:
        {
            Page_Tableaux ();
            break;
        }
        case 2:
        {
            Former_Acces_Fichier (NOM_TABLEAU,
                                  numero_serie,
                                  numero_tableau);
            strncpy (bufrep,NOM_TABLEAU,8);
            *(bufrep + 8) = 0;
            Desinstaller_Clavier_Interruption ();
            retour = spawnl (P_WAIT,"EDITEUR.EXE","0",bufrep,NULL);
            if (retour == -1)
            {
                Desactiver_Ecran ();
                Supprimer_Bobs ();
                if (errno == E2BIG )
                    cprintf ("\n\rliste des arguments est trop longue");
                if (errno == EACCES)
                    cprintf ("\n\rAcces au fichier est refusee");
                if (errno == EMFILE)
                    cprintf ("\n\rTrop de fichier ouverts simultanement");
                if (errno == ENOENT)
                    cprintf ("\n\rFichier ou chemin d'acces non trouve");
                if (errno == ENOMEM)
                    cprintf ("\n\rEspace memoire insuffisant");
                exit (EXIT_SUCCESS);
            }
            Activer_Ecran ();
            Installer_Clavier_Interruption ();
            Lire_Palette ("SPRFILES/COULEURS.PAL");
            Afficher_Page (PAGE0);
            Afficher_Presentation ();
            break;
        }
        case 3:
        {
            Page_Regle ();
            break;
        }
        case 4:
        {
            Page_Scores (SAISIE_OFF);
            break;
        }
        }
    }
    while (menu1.select != 5);
    Supprimer_Bobs ();
    Desinstaller_Clavier_Interruption ();
    Cls (PAGE0,0);
    Afficher_Page (PAGE0);
    Cls (PAGE1,0);
    Afficher_Page (PAGE1);
    Desactiver_Ecran ();
    printf ("SNAKLES V1.1 (C) COPYRIGHT 1996-97 MARTY M.\n");
}
void Afficher_Presentation (void)
{
    Cls (PAGE1,0);
    Lire_Image_Pcx ("SPRFILES/INTRO",PAGE1,0,20,MASK_ON,0,0,319,134);
    Afficher_Menu (&menu1);
    Print (PAGE1,1,1,0,390,249,255,"    (C) COPYRIGHT 1996-97 MARTY M.");
    Print (PAGE1,1,1,220,145,245,255,"ÛVERSION 1.1");
    Afficher_Page (PAGE1);
}
