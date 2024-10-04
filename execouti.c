#include <STDIO.H>
#include <CONIO.H>
#include <STRING.H>
#include "SOUREXEC/EXECCLAV.H"
#include "SOUREXEC/EXECGRAP.H"
#include "SOUREXEC/EXECOUTI.H"
#include "SOUREXEC/EXECCHAR.H"
void Marquer_Option (char,enreg_menu*,char);
void Marquer_Option_Texte (enreg_menu*,char);
void Afficher_Menu (enreg_menu *pt)
{
    OCTET couleur;
    short x_option;
    short y_option;
    short largeur_menu;
    short hauteur_menu;
    short hauteur_option;
    short xg,xd;
    short longueur;
    char cpt;
    largeur_menu = 0;
    for (cpt = 0;
            cpt < pt->nombre_option;
            cpt ++)
    {
        longueur = strlen (pt->option [cpt]);
        if (longueur > largeur_menu)
            largeur_menu = longueur;
    }
    largeur_menu *= (8 * pt->echelle_x);
    x_option = (pt->largeur_ecran - largeur_menu) / 2;
    hauteur_menu = pt->nombre_option * (8 * pt->echelle_y);
    if (pt->nombre_option > 1)
    {
        hauteur_option = (pt->hauteur_option_maxi - hauteur_menu) /
                         (pt->nombre_option - 1);
        hauteur_option += (8 * pt->echelle_y);
    }
    y_option = pt->y_ecran;
    for (cpt = 0;
            cpt < pt->nombre_option;
            cpt ++)
    {
        longueur = strlen (pt->option [cpt]);
        longueur *= (8 * pt->echelle_x);
        xg = ( (largeur_menu - longueur) / 2) + x_option;
        xd = ( (xg + longueur) - pt->echelle_x) - 1;
        pt->xgt [cpt] = xg;
        pt->xdt [cpt] = xd;
        pt->yt [cpt] = y_option;
        if (pt->cl_fond == 255)
        {
            couleur = 240;
            Print (pt->page,
                   pt->echelle_x,
                   pt->echelle_y,
                   xg - 1,
                   y_option,
                   couleur,
                   pt->cl_fond,
                   pt->option [cpt]);
            Print (pt->page,
                   pt->echelle_x,
                   pt->echelle_y,
                   xg + 1,
                   y_option,
                   couleur,
                   pt->cl_fond,
                   pt->option [cpt]);
            Print (pt->page,
                   pt->echelle_x,
                   pt->echelle_y,
                   xg,
                   y_option - 1,
                   couleur,
                   pt->cl_fond,
                   pt->option [cpt]);
            Print (pt->page,
                   pt->echelle_x,
                   pt->echelle_y,
                   xg,
                   y_option + 1,
                   couleur,
                   pt->cl_fond,
                   pt->option [cpt]);
        }
        Print (pt->page,
               pt->echelle_x,
               pt->echelle_y,
               xg,y_option,
               pt->cl_car2,
               pt->cl_fond,
               pt->option [cpt]);
        y_option += hauteur_option;
    }
    Marquer_Option (pt->page,pt,ON);
}
void Marquer_Option (char page,enreg_menu *pt,char etat)
{
    Marquer_Option_Serpent (page,pt,etat);
    Marquer_Option_Texte (pt,etat);
}
void Marquer_Option_Serpent (char page,enreg_menu *pt,char etat)
{
    short xg,xd,y;
    xg = pt->xgt [pt->select] - ( (3*7) + 2 );
    xd = pt->xdt [pt->select] + 3;
    y = pt->yt [pt->select] + ( ((pt->echelle_y * 7) - 11) / 2);
    if (etat == ON)
    {
        Afficher_Bob (page,5,xg,y,MASK_ON);
        Afficher_Bob (page,6,xg+ 7,y,MASK_ON);
        Afficher_Bob (page,4,xg+14,y,MASK_ON);
        Afficher_Bob (page,2,xd,y,MASK_ON);
        Afficher_Bob (page,6,xd+ 7,y,MASK_ON);
        Afficher_Bob (page,3,xd+14,y,MASK_ON);
    }
    else
    {
        Afficher_Bob (page,1,xg+ 0,y,MASK_ON);
        Afficher_Bob (page,1,xg+ 7,y,MASK_ON);
        Afficher_Bob (page,1,xg+14,y,MASK_ON);
        Afficher_Bob (page,1,xd+ 0,y,MASK_ON);
        Afficher_Bob (page,1,xd+ 7,y,MASK_ON);
        Afficher_Bob (page,1,xd+14,y,MASK_ON);
    }
}
void Marquer_Option_Texte (enreg_menu *pt,char etat)
{
    if (etat == ON)
    {
        Print (pt->page,
               pt->echelle_x,
               pt->echelle_y,
               pt->xgt [pt->select],
               pt->yt [pt->select],
               pt->cl_car1,
               pt->cl_fond,
               pt->option [pt->select]);
    }
    else
    {
        Print (pt->page,
               pt->echelle_x,
               pt->echelle_y,
               pt->xgt [pt->select],
               pt->yt [pt->select],
               pt->cl_car2,
               pt->cl_fond,
               pt->option [pt->select]);
    }
}
void Select_Option (char page,enreg_menu *pt)
{
    Marquer_Option_Serpent (page,pt,ON);
    do
    {
        if (pt->nombre_option > 1)
        {
            if (Lire_Action_Touche (FLECHE_BAS) == 1)
            {
                Marquer_Option (page,pt,OFF);
                pt->select ++;
                if (pt->select >= pt->nombre_option)
                    pt->select = 0;
                Marquer_Option (page,pt,ON);
            }
            if (Lire_Action_Touche (FLECHE_HAUT) == 1)
            {
                Marquer_Option (page,pt,OFF);
                pt->select --;
                if (pt->select < 0)
                    pt->select = pt->nombre_option - 1;
                Marquer_Option (page,pt,ON);
            }
        }
    }
    while (Lire_Action_Touche (ENTREE) != 1);
    Marquer_Option_Serpent (page,pt,OFF);
}
