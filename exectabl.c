#include <IO.H>
#include <DOS.H>
#include <STDIO.H>
#include <STRING.H>
#include <STDLIB.H>
#include "SOUREXEC/EXECGRAP.H"
#include "SOUREXEC/EXECCLAV.H"
#include "SOUREXEC/EXECOUTI.H"
#include "SOUREXEC/EXECCHAR.H"
#define EXTENSION ".DAT"
#define FICHIER "/LEVEL"
#define REPERTOIRE "LEVELS"
#define C_CURSEUR 80
#define ATTRBX_NUMERO 2
#define ATTRBY_NUMERO 8
#define XT_TABLEAU 22
#define YT_TABLEAU 325
#define CCT_TABLEAU 240
#define CFT_TABLEAU 255
#define XV_TABLEAU 35
#define YV_TABLEAU 336
#define CCV_TABLEAU 112
#define CFV_TABLEAU 0
#define XT_SERIE 258
#define YT_SERIE 325
#define CCT_SERIE 240
#define CFT_SERIE 255
#define XV_SERIE 264
#define YV_SERIE 336
#define CCV_SERIE 112
#define CFV_SERIE 0
#define CCS_SERIE 240
#define CFS_SERIE 111
#define X1_HELP_EFFACE 77
#define Y1_HELP_EFFACE 325
#define X2_HELP_EFFACE 256
#define Y2_HELP_EFFACE 340
#define XT_HELP1 93
#define YT_HELP1 325
#define CCT_HELP1 192
#define CFT_HELP1 0
#define XT_HELP2 97
#define YT_HELP2 325
#define CCT_HELP2 192
#define CFT_HELP2 0
#define X_MAX 45
#define Y_MAX 35
#define ACCES_FICHIER 32
#define OBST_BOULE_BLEU 13
#define NB_TABLEAU_X 6
#define NB_TABLEAU_Y 8
#define X_TABLEAUX 22
#define Y_TABLEAUX 34
#define LG_TABLEAU 44
#define HT_TABLEAU 34
#define X_ECART 46
#define Y_ECART 36
void Effacer_Help (void);
void Afficher_Mini_Tableau (OCTET,short);
void Afficher_Tableau_Vide (OCTET,short);
void Marquer_Mini_Tableau (OCTET,OCTET,short);
void Select_Mini_Tableau (OCTET);
void Select_Serie (OCTET);
void Select_Hasard (OCTET,enreg_menu*);
void Afficher_Numero_Tableau (OCTET);
void Afficher_Numero_Serie (OCTET);
void Former_Acces_Fichier (char*,short,short);
BOOL Verifier_Tableau (short);
BOOL Verifier_Serie (short);
BOOL Verifier_Tableaux (void);
extern char NOM_TABLEAU [];
extern short numero_tableau;
extern short numero_serie;
extern BOOL hasard;
BOOL info = OFF;
BOOL serie;
void Page_Tableaux (void)
{
    BOOL verif;
    short cpt;
    enreg_menu menu3;
    Cls (PAGE0,0);
    Print_Titre (PAGE0,0,"TABLEAUX");
    menu3.page = PAGE0;
    menu3.select = 3;
    menu3.cl_car1 = 97;
    menu3.cl_car2 = 113;
    menu3.cl_fond = 0;
    menu3.y_ecran = 350;
    menu3.largeur_ecran = 320;
    menu3.hauteur_option_maxi = 50;
    menu3.nombre_option = 4;
    menu3.echelle_x = 1;
    menu3.echelle_y = 1;
    strcpy (menu3.option[0],"NUMERO TABLEAU");
    strcpy (menu3.option[1],"NUMERO SERIE");
    if (hasard == OFF) strcpy (menu3.option[2],"ORDRE NORMAL");
    else strcpy (menu3.option[2],"ORDRE HASARD");
    strcpy (menu3.option[3],"RETOUR");
    Afficher_Menu (&menu3);
    Print (PAGE0,1,1,XT_TABLEAU,YT_TABLEAU,CCT_TABLEAU,CFT_TABLEAU,"TABLEAU");
    Afficher_Numero_Tableau (PAGE0);
    Print (PAGE0,1,1,XT_SERIE,YT_SERIE,CCT_SERIE,CFT_SERIE,"SERIE");
    Afficher_Numero_Serie (PAGE0);
    verif = Verifier_Serie (numero_serie);
    if (verif == VRAI)
    {
        serie = ON;
        for (cpt = 1; cpt <= 48; cpt ++)
            Afficher_Mini_Tableau (PAGE0,cpt);
        Marquer_Mini_Tableau (PAGE0,ON,numero_tableau);
        verif = Verifier_Tableau (numero_tableau);
        if ( verif == FAUX)
        {
            Effacer_Help ();
            Print (PAGE0,1,2,XT_HELP1,YT_HELP1,CCT_HELP1,CFT_HELP1,
                   "TABLEAU INCOMPLET");
            info = ON;
        }
    }
    else
    {
        serie = OFF;
        numero_tableau = 1;
        Effacer_Help ();
        Print (PAGE0,1,2,XT_HELP2,YT_HELP2,CCT_HELP2,CFT_HELP2,
               "SERIE NON DEFINI");
        for (cpt = 1; cpt <= 48; cpt ++)
            Afficher_Tableau_Vide (PAGE0,cpt);
    }
    Afficher_Page (PAGE0);
    do
    {
        Select_Option (PAGE0,&menu3);
        if ( (menu3.select == 0) & (serie == ON) )
            Select_Mini_Tableau (PAGE0);
        if (menu3.select == 1)
            Select_Serie (PAGE0);
        if (menu3.select == 2)
            Select_Hasard (PAGE0,&menu3);
    }
    while (menu3.select != 3);
    Former_Acces_Fichier (NOM_TABLEAU,numero_serie,numero_tableau);
    Afficher_Page (PAGE1);
}
void Effacer_Help (void)
{
    Tracer_Carre_Plein (PAGE0,X1_HELP_EFFACE,Y1_HELP_EFFACE,
                        X2_HELP_EFFACE,Y2_HELP_EFFACE,0);
}
void Afficher_Mini_Tableau (OCTET page,short num_tableau)
{
    FILE *flux;
    OCTET cptx;
    OCTET cpty;
    short cptind;
    OCTET couleur;
    OCTET col;
    OCTET lig;
    short x;
    short y;
    char acces_fichier [ACCES_FICHIER];
    OCTET buffertableau [X_MAX*Y_MAX];
    OCTET couleurs [30] =
    {
        252,
        98,
        20,
        3,
        3,
        3,
        3,
        3,
        3,
        3,
        3,
        3,
        3,
        96,
        3,
        3,
        3,
        240,
        3,
        3,
        3,
        3,
        3,
        3,
        3,
        3,
        3,
        3,
        3,
        3
    };
    lig = ( num_tableau - 1 ) / NB_TABLEAU_X;
    col = ( num_tableau - 1 ) - ( NB_TABLEAU_X * lig );
    x = X_TABLEAUX + ( col * X_ECART );
    y = Y_TABLEAUX + ( lig * Y_ECART );
    cptind = 0;
    Former_Acces_Fichier (acces_fichier,numero_serie,num_tableau);
    flux = fopen(acces_fichier,"rb");
    fread (&buffertableau[0],(X_MAX * Y_MAX),1,flux);
    fclose (flux);
    for (cpty = 0;
            cpty < Y_MAX;
            cpty ++)
    {
        for (cptx = 0;
                cptx < X_MAX;
                cptx ++)
        {
            couleur = couleurs [buffertableau [cptind]];
            Afficher_Point (page,(x + cptx),(y + cpty),couleur);
            cptind ++;
        }
    }
}
void Afficher_Tableau_Vide (OCTET page,short num_tableau)
{
    OCTET cptx;
    OCTET cpty;
    OCTET col;
    OCTET lig;
    short x;
    short y;
    lig = ( num_tableau - 1 ) / NB_TABLEAU_X;
    col = ( num_tableau - 1 ) - ( NB_TABLEAU_X * lig );
    x = X_TABLEAUX + ( col * X_ECART );
    y = Y_TABLEAUX + ( lig * Y_ECART );
    for (cpty = 0;
            cpty < Y_MAX;
            cpty ++)
        for (cptx = 0;
                cptx < X_MAX;
                cptx ++)
            Afficher_Point (page,(x + cptx),(y + cpty),252);
}
void Marquer_Mini_Tableau (OCTET page,OCTET etat,short num_tableau)
{
    short col;
    short lig;
    short x;
    short y;
    OCTET coul;
    lig = ( num_tableau - 1 ) / NB_TABLEAU_X;
    col = ( num_tableau - 1 ) - ( NB_TABLEAU_X * lig );
    x = X_TABLEAUX + ( col * X_ECART );
    y = Y_TABLEAUX + ( lig * Y_ECART );
    coul = (etat == ON) ? 240 : 0;
    Tracer_Rectangle (page,x - 1,y - 1,x + 45,y + 35,coul);
}
void Select_Mini_Tableau (OCTET page)
{
    BOOL tab;
    char cpt;
    for (cpt = 0;
            cpt < 3;
            cpt ++)
    {
        Marquer_Mini_Tableau (page,OFF,numero_tableau);
        delay (60);
        Marquer_Mini_Tableau (page,ON,numero_tableau);
        delay (60);
    }
    do
    {
        if (Lire_Action_Touche (FLECHE_GAUCHE) == ON)
        {
            if (info == ON)
            {
                Effacer_Help ();
                info = OFF;
            }
            Marquer_Mini_Tableau (page,OFF,numero_tableau);
            numero_tableau --;
            if ( (numero_tableau % 6) == 0) numero_tableau += 6;
            Marquer_Mini_Tableau (page,ON,numero_tableau);
            Afficher_Numero_Tableau (page);
        }
        if (Lire_Action_Touche (FLECHE_DROITE) == ON)
        {
            if (info == ON)
            {
                Effacer_Help ();
                info = OFF;
            }
            Marquer_Mini_Tableau (page,OFF,numero_tableau);
            numero_tableau ++;
            if ( ( (numero_tableau - 1) % 6) == 0) numero_tableau -= 6;
            Marquer_Mini_Tableau (page,ON,numero_tableau);
            Afficher_Numero_Tableau (page);
        }
        if (Lire_Action_Touche (FLECHE_BAS) == ON)
        {
            if (info == ON)
            {
                Effacer_Help ();
                info = OFF;
            }
            Marquer_Mini_Tableau (page,OFF,numero_tableau);
            numero_tableau += 6;
            if (numero_tableau > 48) numero_tableau -= 48;
            Marquer_Mini_Tableau (page,ON,numero_tableau);
            Afficher_Numero_Tableau (page);
        }
        if (Lire_Action_Touche (FLECHE_HAUT) == ON)
        {
            if (info == ON)
            {
                Effacer_Help ();
                info = OFF;
            }
            Marquer_Mini_Tableau (page,OFF,numero_tableau);
            numero_tableau -= 6;
            if (numero_tableau < 1) numero_tableau += 48;
            Marquer_Mini_Tableau (page,ON,numero_tableau);
            Afficher_Numero_Tableau (page);
        }
    }
    while (Lire_Action_Touche (ENTREE) == OFF);
    tab = Verifier_Tableau (numero_tableau);
    if (tab == FAUX)
    {
        Effacer_Help ();
        Print (PAGE0,1,2,XT_HELP1,YT_HELP1,CCT_HELP1,CFT_HELP1,
               "TABLEAU INCOMPLET");
        info = ON;
    }
    if (info == OFF)
    {
        for (cpt = 0;
                cpt < 3;
                cpt ++)
        {
            Marquer_Mini_Tableau (page,OFF,numero_tableau);
            delay (60);
            Marquer_Mini_Tableau (page,ON,numero_tableau);
            delay (60);
        }
    }
}
void Select_Hasard (OCTET page,enreg_menu *pt)
{
    if (hasard == OFF)
    {
        strcpy (pt->option[2],"            ");
        Afficher_Menu (pt);
        Marquer_Option_Serpent (page,pt,OFF);
        strcpy (pt->option[2],"ORDRE HASARD");
        Afficher_Menu (pt);
        hasard = ON;
    }
    else
    {
        strcpy (pt->option[2],"            ");
        Afficher_Menu (pt);
        Marquer_Option_Serpent (page,pt,OFF);
        strcpy (pt->option[2],"ORDRE NORMAL");
        Afficher_Menu (pt);
        hasard = OFF;
    }
}
void Afficher_Numero_Tableau (OCTET page)
{
    Print_Vl (page,ATTRBX_NUMERO,ATTRBY_NUMERO,
              XV_TABLEAU,YV_TABLEAU,
              CCV_TABLEAU,CFV_TABLEAU,
              2,numero_tableau);
}
void Afficher_Numero_Serie (OCTET page)
{
    Print_Vl (page,ATTRBX_NUMERO,ATTRBY_NUMERO,
              XV_SERIE,YV_SERIE,
              CCV_SERIE,CFV_SERIE,
              2,numero_serie);
}
void Select_Serie (OCTET page)
{
    short cpt;
    BOOL verif;
    char buffer [3];
    Input (page,ATTRBX_NUMERO,ATTRBY_NUMERO,
           XV_SERIE,YV_SERIE,
           CCS_SERIE,CFS_SERIE,
           C_CURSEUR,
           NUM,2,buffer);
    numero_serie = atoi (buffer);
    Afficher_Numero_Serie (page);
    verif = Verifier_Serie (numero_serie);
    if (verif == VRAI)
    {
        Effacer_Help ();
        Marquer_Mini_Tableau (PAGE0,OFF,numero_tableau);
        for (cpt = 1; cpt <= 48; cpt ++)
            Afficher_Mini_Tableau (PAGE0,cpt);
        numero_tableau = 1;
        Afficher_Numero_Tableau (PAGE0);
        Marquer_Mini_Tableau (PAGE0,ON,numero_tableau);
        serie = ON;
    }
    else
    {
        Marquer_Mini_Tableau (PAGE0,OFF,numero_tableau);
        numero_tableau = 1;
        Afficher_Numero_Tableau (PAGE0);
        Effacer_Help ();
        Print (PAGE0,1,2,XT_HELP2,YT_HELP2,CCT_HELP2,CFT_HELP2,
               "SERIE NON DEFINI");
        for (cpt = 1; cpt <= 48; cpt ++)
            Afficher_Tableau_Vide (PAGE0,cpt);
        serie = OFF;
    }
}
void Former_Acces_Fichier (char *buffer,short serie,short tableau)
{
    char nbbuffer [3];
    char zero2 [2][2] = { {"0"},{""} };
    char zero3 [3][3] = { {"00"},{"0"},{""} };
    strcpy (buffer,REPERTOIRE);
    itoa (serie,nbbuffer,10);
    strcat (buffer,zero2 [strlen(nbbuffer) - 1] );
    strcat (buffer,nbbuffer);
    strcat (buffer,FICHIER);
    itoa (tableau,nbbuffer,10);
    strcat (buffer,zero3 [strlen(nbbuffer) - 1] );
    strcat (buffer,nbbuffer);
    strcat (buffer,EXTENSION);
}
BOOL Verifier_Tableau (short tab)
{
    OCTET car;
    OCTET buffertableau [X_MAX*Y_MAX];
    BOOL boule;
    BOOL sortie;
    FILE *flux;
    short cpt;
    char acces_fichier [ACCES_FICHIER];
    boule = FAUX;
    sortie = VRAI;
    Former_Acces_Fichier (acces_fichier,numero_serie,tab);
    flux = fopen(acces_fichier,"rb");
    if (flux == NULL) return (FAUX);
    fread (&buffertableau[0],(X_MAX * Y_MAX),1,flux);
    for (cpt = 0;
            cpt < (X_MAX*Y_MAX);
            cpt ++)
    {
        if (buffertableau [cpt] == OBST_BOULE_BLEU)
        {
            boule = VRAI;
            break;
        }
    }
    fseek(flux,(0x0772-0x0035),SEEK_SET);
    car = fgetc (flux);
    if (car == 0)
        sortie = FAUX;
    if (boule == FAUX)
        sortie = FAUX;
    fclose (flux);
    return (sortie);
}
BOOL Verifier_Serie (short serie)
{
    BOOL sortie;
    char acces_fichier [ACCES_FICHIER];
    char nbbuffer [3];
    char zero2 [2][2] = { {"0"},{""} };
    strcpy (acces_fichier,REPERTOIRE);
    itoa (serie,nbbuffer,10);
    strcat (acces_fichier,zero2 [strlen(nbbuffer) - 1] );
    strcat (acces_fichier,nbbuffer);
    if (access (acces_fichier,0) == 0)
        sortie = VRAI;
    else
        sortie = FAUX;
    return (sortie);
}
BOOL Verifier_Tableaux (void)
{
    char cpt;
    BOOL tab1;
    BOOL tab48;
    tab48 = FAUX;
    for (cpt = 1;
            cpt <= 48;
            cpt ++)
    {
        tab1 = Verifier_Tableau (cpt);
        if (tab1 == VRAI)
        {
            tab48 = VRAI;
            break;
        }
    }
    return (tab48);
}
