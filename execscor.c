#include <STDIO.H>
#include <STRING.H>
#include "SOUREXEC/EXECGRAP.H"
#include "SOUREXEC/EXECCLAV.H"
#include "SOUREXEC/EXECOUTI.H"
#include "SOUREXEC/EXECCHAR.H"
#define ATTRBX 1
#define ATTRBY 1
#define FICHIER_SCORES "scores.dat"
#define FICHIER_FILEDATA "donnees.dat"
#define X_DONNEES 8
#define Y_DONNEES 45
#define SPC_LIGNE 10
#define X_REPERE 24
#define X_NOM 160
#define X_SERIE 24
#define X_TAB_DEB 24
#define X_TAB_FIN 24
#define X_SCORE 0
#define CC_REPERE 96
#define CC_NOM 208
#define CC_SERIE 9
#define CC_TAB_DEB 245
#define CC_TAB_FIN 245
#define CC_SCORE 240
#define CF 0
#define NB_SCORES 30
#define CAR_NOM 20
void Afficher_Scores (char);
BOOL Lire_Scores (void);
BOOL Sauver_Scores (void);
void Init_Scores (void);
BOOL Lire_Filedata (void);
BOOL Sauver_Filedata (ULONG,short);
char Determiner_Rang (ULONG);
void Decaler_Rang (char);
void Inserer_Valeurs (char);
void Saisir_Nom (char,char);
extern char NOM_TABLEAU [];
extern short numero_tableau;
extern short numero_serie;
typedef struct
{
    char noms [NB_SCORES][CAR_NOM];
    short serie [NB_SCORES];
    short tab_deb [NB_SCORES];
    short tab_fin [NB_SCORES];
    ULONG scores [NB_SCORES];
} enreg_scores;
enreg_scores scores;
typedef struct
{
    ULONG score;
    short tableau;
} enreg_filedata;
enreg_filedata filedata;
void Page_Scores (BOOL saisie)
{
    BOOL etat;
    char rang;
    enreg_menu menu4;
    menu4.page = PAGE0;
    menu4.select = 0;
    menu4.cl_car1 = 97;
    menu4.cl_car2 = 113;
    menu4.cl_fond = 0;
    menu4.y_ecran = 392;
    menu4.largeur_ecran = 320;
    menu4.hauteur_option_maxi = 8;
    menu4.nombre_option = 1;
    menu4.echelle_x = 1;
    menu4.echelle_y = 1;
    strcpy (menu4.option[0],"RETOUR");
    etat = Lire_Scores ();
    if (etat == FAUX)
    {
        Init_Scores ();
        etat = Sauver_Scores ();
        if (etat == FAUX)
            return;
    }
    if (saisie == SAISIE_ON)
    {
        etat = Lire_Filedata ();
        if (etat == VRAI)
        {
            if ( (filedata.score >= scores.scores [NB_SCORES - 1]) &
                    (filedata.score != 0) )
            {
                rang = Determiner_Rang (filedata.score);
                Decaler_Rang (rang);
                Inserer_Valeurs (rang);
                Cls (PAGE0,0);
                Print_Titre (PAGE0,0,"SCORES");
                Afficher_Menu (&menu4);
                Marquer_Option_Serpent (PAGE0,&menu4,OFF);
                Afficher_Scores (PAGE0);
                Afficher_Page (PAGE0);
                Saisir_Nom (PAGE0,rang);
                Sauver_Scores ();
                Marquer_Option_Serpent (PAGE0,&menu4,ON);
                Select_Option (PAGE0,&menu4);
                Sauver_Filedata (0L,0);
            }
            else
                Afficher_Page (PAGE0);
        }
    }
    else
    {
        Cls (PAGE0,0);
        Print_Titre (PAGE0,0,"SCORES");
        Afficher_Menu (&menu4);
        Afficher_Scores (PAGE0);
        Afficher_Page (PAGE0);
        Select_Option (PAGE0,&menu4);
        Afficher_Page (PAGE1);
    }
}
void Afficher_Scores (char page)
{
    char attrb;
    short x;
    short y;
    char cpt;
    x = X_DONNEES;
    y = Y_DONNEES;
    for (cpt = 0;
            cpt < NB_SCORES;
            cpt ++)
    {
        attrb = (cpt < 3) ? 1 : 0;
        Print_Vl (page,ATTRBX,ATTRBY + attrb,x,y,CC_REPERE,CF,2,cpt + 1);
        x += X_REPERE;
        Print (PAGE0,ATTRBX,ATTRBY + attrb,x,y,CC_NOM,CF,scores.noms [cpt]);
        x += X_NOM;
        Print_Vl (page,ATTRBX,ATTRBY + attrb,x,y,CC_SERIE,CF,2,scores.serie [cpt]);
        x += X_SERIE;
        Print_Vl (page,ATTRBX,ATTRBY + attrb,x,y,CC_TAB_DEB,CF,2,scores.tab_deb [cpt]);
        x += X_TAB_DEB;
        Print_Vl (page,ATTRBX,ATTRBY + attrb,x,y,CC_TAB_FIN,CF,2,scores.tab_fin [cpt]);
        x += X_TAB_FIN;
        Print_Vl (page,ATTRBX + 0,ATTRBY + attrb,x,y,CC_SCORE,CF,6,scores.scores [cpt]);
        x += X_SCORE;
        x = X_DONNEES;
        y += (ATTRBY + attrb) * SPC_LIGNE;
    }
}
BOOL Lire_Scores (void)
{
    BOOL sortie;
    FILE *flux;
    flux = fopen(FICHIER_SCORES,"rb");
    if (flux == NULL)
        sortie = FAUX;
    else
    {
        fread (&scores.noms[0][0],sizeof (enreg_scores),1,flux);
        fclose (flux);
        sortie = VRAI;
    }
    return (sortie);
}
BOOL Sauver_Scores (void)
{
    BOOL sortie;
    FILE *flux;
    flux = fopen(FICHIER_SCORES,"wb");
    if (flux == NULL)
        sortie = FAUX;
    else
    {
        fwrite (&scores.noms[0][0],sizeof (enreg_scores),1,flux);
        fclose (flux);
        sortie = VRAI;
    }
    return (sortie);
}
void Init_Scores (void)
{
    char ind;
    char cpt;
    for (cpt = 0;
            cpt < NB_SCORES;
            cpt ++)
    {
        for (ind = 0;
                ind < (CAR_NOM - 1);
                ind ++)
            strcpy (&scores.noms [cpt][ind]," ");
        strcpy (&scores.noms [cpt][CAR_NOM - 1],"\0");
        scores.serie [cpt] = 0;
        scores.tab_deb [cpt] = 0;
        scores.tab_fin [cpt] = 0;
        scores.scores [cpt] = 0;
    }
}
BOOL Lire_Filedata (void)
{
    BOOL sortie;
    FILE *flux;
    flux = fopen(FICHIER_FILEDATA,"rb");
    if (flux == NULL)
        sortie = FAUX;
    else
    {
        fread (&filedata.score,sizeof (enreg_filedata),1,flux);
        fclose (flux);
        sortie = VRAI;
    }
    return (sortie);
}
BOOL Sauver_Filedata (ULONG score,short tableau)
{
    BOOL sortie;
    FILE *flux;
    flux = fopen(FICHIER_FILEDATA,"wb");
    if (flux == NULL)
        sortie = FAUX;
    else
    {
        filedata.score = score;
        filedata.tableau = tableau;
        fwrite (&filedata.score,sizeof (enreg_filedata),1,flux);
        fclose (flux);
        sortie = VRAI;
    }
    return (sortie);
}
char Determiner_Rang (ULONG score)
{
    char cpt;
    for (cpt = 0;
            cpt < NB_SCORES;
            cpt ++)
        if (scores.scores [cpt] <= score)
            break;
    return (cpt);
}
void Decaler_Rang (char indice)
{
    char cpt;
    if (indice < (NB_SCORES - 1))
    {
        for (cpt = (NB_SCORES - 1);
                cpt > indice;
                cpt --)
        {
            strcpy (&scores.noms [cpt][0],&scores.noms [cpt - 1][0]);
            scores.serie [cpt] = scores.serie [cpt - 1];
            scores.tab_deb [cpt] = scores.tab_deb [cpt - 1];
            scores.tab_fin [cpt] = scores.tab_fin [cpt - 1];
            scores.scores [cpt] = scores.scores [cpt - 1];
        }
    }
}
void Inserer_Valeurs (char indice)
{
    scores.serie [indice] = numero_serie;
    scores.tab_deb [indice] = numero_tableau;
    scores.tab_fin [indice] = filedata.tableau;
    scores.scores [indice] = filedata.score;
}
void Saisir_Nom (char page,char indice)
{
    short x,y;
    char cpt;
    char attrb;
    x = X_DONNEES + X_REPERE;
    y = Y_DONNEES;
    for (cpt = 0;
            cpt < indice;
            cpt ++)
    {
        attrb = (cpt < 3) ? 1 : 0;
        y += (ATTRBY + attrb) * SPC_LIGNE;
    }
    attrb = (indice < 3) ? 1 : 0;
    Input (page,ATTRBX,
           ATTRBY + attrb,
           x,
           y,
           213,
           0,
           240,
           ALP,
           CAR_NOM - 1,
           &scores.noms [indice][0]);
    for (cpt = 0;
            cpt < CAR_NOM;
            cpt ++)
        Print (page,ATTRBX,
               ATTRBY + attrb,
               x + (cpt * 8),
               y,
               CC_NOM,
               CF,
               " ");
    Print (page,ATTRBX,
           ATTRBY + attrb,
           x,
           y,
           CC_NOM,
           CF,
           &scores.noms [indice][0]);
}
