#include <STRING.H>
#include "SOUREXEC/EXECGRAP.H"
#include "SOUREXEC/EXECOUTI.H"
#include "SOUREXEC/EXECCHAR.H"
void Afficher_Regle (char);
void Page_Regle (void)
{
    enreg_menu menu2;
    Cls (PAGE0,0);
    Print_Titre (PAGE0,0,"REGLE DU JEU");
    menu2.page = PAGE0;
    menu2.select = 0;
    menu2.cl_car1 = 97;
    menu2.cl_car2 = 113;
    menu2.cl_fond = 0;
    menu2.y_ecran = 392;
    menu2.largeur_ecran = 320;
    menu2.hauteur_option_maxi = 8;
    menu2.nombre_option = 1;
    menu2.echelle_x = 1;
    menu2.echelle_y = 1;
    strcpy (menu2.option[0],"RETOUR");
    Afficher_Menu (&menu2);
    Afficher_Regle (PAGE0);
    Afficher_Page (PAGE0);
    Select_Option (PAGE0,&menu2);
    Afficher_Page (PAGE1);
}
#define BOB_PASTILLES 7
#define PASTILLE_BLEU BOB_PASTILLES+10
#define X_PAST_BLEU 47
#define Y_PAST_BLEU 47
#define T_CHAR 8
#define X_TEXTE 0
#define Y_TEXTE 33
#define C_TEXTE 247
#define H_TEXTE 8
#define X_EXPLIC 0
#define Y_EXPLIC 103
#define C_EXPLIC 249
#define H_EXPLIC 19
void Afficher_Regle (char page)
{
    char bob;
    char cptbob;
    char cptcar;
    short x_pas;
    short y_pas;
    short x_exp;
    short y_exp;
    char *bk_ad;
    short cpt;
    short groupe [15] = {1,3,3,3,1,2,2,2,2,2,2,3,3,3,3};
    char *texte [8] =
    {
        {"  LE BUT DU JEU EST DE FAIRE GOBER A UN" },
        {"SERPENT (SNAKLE), TOUTES LES PASTILLES" },
        {"BLEUS   QUI SE TROUVENT DANS LE TABLEAU."},
        {"D'AUTRES SNAKLES DE COULEURS ROUGES," },
        {"VERTS ET BLEUS VOUS EMPECHERONT" },
        {"D'EVOLUER. DIFFERENTES PASTILLES PEUVENT"},
        {"ETRES PRESENTES DANS LE TABLEAU, AVEC" },
        {"DES ACTIONS DIVERSES :" }
    };
    char *exp_past [15] =
    {
        {"   -PORTE MOBILE" },
        {"   -PORTES FIXES FERMEES" },
        {"   -PORTES FIXES OUVERTES" },
        {"   -CLES PERMETTANT D'OUVRIR OU DE          FERMER LES PORTES DE MEMES COULEURS"},
        {"   -POINTS SUPPLEMENTAIRES" },
        {"   -DIMINUENT OU ALLONGENT LA LONGUEUR      DE SNAKLE" },
        {"   -AJOUTENT OU ENLEVENT UNE VIE" },
        {"   -AUTORISENT OU INTERDISENT A SNAKLE      DE PASSER SUR SON PROPRE CORPS" },
        {"   -AJOUTENT OU ENLEVENT DU TEMPS" },
        {"   -DESACTIVENT OU ACTIVENT                 L'IMMORTALITE" },
        {"   -DESACTIVENT OU ACTIVENT L'AVANCE PAS    A PAS" },
        {"   -CHANGENT LA VITESSE DE SNAKLE           (RAPIDE,NORMALE,LENTE)" },
        {"   -STOPPENT OU REACTIVENT LES SNAKLES      DE MEMES COULEURS" },
        {"   -DONNENT UNE NOUVELLE DIRECTION AUX      SNAKLES DE MEMES COULEURS" },
        {"   -DONNENT UNE NOUVELLE VITESSE AUX        SNAKLES DE MEMES COULEURS" }
    };
    for (cpt = 0;
            cpt < 8;
            cpt ++)
        Print (page,1,1,X_TEXTE,Y_TEXTE + (H_TEXTE * cpt),C_TEXTE,255,texte [cpt]);
    bob = BOB_PASTILLES;
    y_pas = Y_EXPLIC;
    for (cpt = 0;
            cpt < 15;
            cpt ++)
    {
        x_pas = X_EXPLIC + ((3 - groupe [cpt]) * 8);
        for (cptbob = 0;
                cptbob < groupe [cpt];
                cptbob ++)
        {
            if (bob == PASTILLE_BLEU) bob ++;
            Afficher_Bob (page,bob,x_pas + (8 * cptbob),y_pas - 2,MASK_ON);
            bob ++;
        }
        x_exp = X_EXPLIC;
        y_exp = y_pas;
        bk_ad = exp_past [cpt];
        cptcar = 0;
        do
        {
            if (*bk_ad != 32)
                PrintChar(page,1,1,*bk_ad,x_exp,y_exp,C_EXPLIC,255);
            x_exp += T_CHAR;
            cptcar ++;
            bk_ad ++;
            if (cptcar > 39)
            {
                cptcar = 0;
                y_exp += T_CHAR;
                x_exp = X_EXPLIC;
            }
        }
        while (*bk_ad != '\0');
        y_pas += H_EXPLIC;
    }
    Afficher_Bob (page,PASTILLE_BLEU,X_PAST_BLEU,Y_PAST_BLEU,MASK_ON);
}
