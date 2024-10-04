#include <STDIO.H>
#include <STRING.H>
#include <STDLIB.H>
#include "SOURGAME/GAMEGRAP.H"
#include "SOURGAME/GAMETABL.H"
#include "SOURGAME/GAMEBOIT.H"
#include "SOURGAME/GAMEINFO.H"
#include "SOURGAME/GAMECHAR.H"
#define LG_BOITE 150
#define HT_BOITE 150
#define COUL_FOND 112
#define COUL_GH 96
#define COUL_DB 132
#define COUL_CAR_B 240
#define COUL_CAR_J 107
#define COUL_CAR_C 96
void Print_Cl (OCTET,float,float,OCTET,OCTET,char*);
void Combler_Zero (char*,char);
char *str;
void Afficher_Boite_Info (OCTET page,OCTET num)
{
    char buffer [7];
    unsigned long sc;
    short tp;
    Afficher_Boite (page);
    switch (num)
    {
    case PAUSE:
    {
        Print_Cl (page,7,8,COUL_CAR_B,COUL_FOND,"PAUSE");
        Print_Cl (page,5.5,16,COUL_CAR_C,COUL_FOND,"<ESPACE>");
        break;
    }
    case ECHAP:
    {
        Print_Cl (page,5,4,COUL_CAR_J,COUL_FOND,"C");
        Print_Cl (page,6,4,COUL_CAR_B,COUL_FOND,"ONTINUER");
        Print_Cl (page,4,9,COUL_CAR_J,COUL_FOND,"R");
        Print_Cl (page,5,9,COUL_CAR_B,COUL_FOND,"ECOMMENCER");
        Print_Cl (page,6,14,COUL_CAR_J,COUL_FOND,"Q");
        Print_Cl (page,7,14,COUL_CAR_B,COUL_FOND,"UITTER");
        break;
    }
    case BONUS:
    {
        Print_Cl (page,3,4,COUL_CAR_B,COUL_FOND,"SCORE");
        sc = Lir_Score () ;
        sprintf(buffer,"%ld",sc) ;
        Combler_Zero (buffer,6);
        Print_Cl (page,10,4,COUL_CAR_J,COUL_FOND,buffer);
        Print_Cl (page,5,6,COUL_CAR_B,COUL_FOND,"+");
        Print_Cl (page,3,8,COUL_CAR_B,COUL_FOND,"TEMPS");
        tp = Lir_Temps () ;
        sprintf(buffer,"%d",tp) ;
        Combler_Zero (buffer,3);
        Print_Cl (page,13,8,COUL_CAR_J,COUL_FOND,buffer);
        Print_Cl (page,3,10,COUL_CAR_B,COUL_FOND,"_____________");
        Print_Cl (page,5,13,COUL_CAR_B,COUL_FOND,"=");
        Inc_Score ((unsigned long)tp) ;
        sc = Lir_Score ();
        sprintf(buffer,"%ld",sc) ;
        Combler_Zero (buffer,6);
        Print_Cl (page,10,13,COUL_CAR_J,COUL_FOND,buffer);
        Print_Cl (page,5.5,16,COUL_CAR_C,COUL_FOND,"<ESPACE>");
        break;
    }
    case FIN_PARTIE:
    {
        Print_Cl (page,6.5,3,COUL_CAR_B,COUL_FOND,"PARTIE");
        Print_Cl (page,5,6,COUL_CAR_B,COUL_FOND,"TERMINEE!");
        Print_Cl (page,3.5,10,COUL_CAR_B,COUL_FOND,"VOTRE SCORE:");
        sc = Lir_Score () ;
        sprintf(buffer,"%ld",sc) ;
        Combler_Zero (buffer,6);
        Print_Cl (page,6.5,13,COUL_CAR_J,COUL_FOND,buffer);
        Print_Cl (page,5.5,16,COUL_CAR_C,COUL_FOND,"<ESPACE>");
        break;
    }
    case LECTURE_TABLEAU:
    {
        Print_Cl (page,6,4,COUL_CAR_B,COUL_FOND,"LECTURE");
        Print_Cl (page,8.5,9,COUL_CAR_B,COUL_FOND,"DU");
        Print_Cl (page,6,14,COUL_CAR_B,COUL_FOND,"TABLEAU");
        break;
    }
    }
}
void Afficher_Boite (OCTET page)
{
    OCTET couleur;
    short cptstr;
    short origx;
    short origy;
    short cpty;
    short cptx;
    origx = ( ( X_MAX * LG_BOB ) - LG_BOITE ) / 2;
    origy = ( ( Y_MAX * HT_BOB ) - HT_BOITE ) / 2;
    str = (char *) malloc ( LG_BOITE * HT_BOITE );
    cptstr = 0;
    for (cpty = 0;
            cpty < HT_BOITE;
            cpty ++)
    {
        for (cptx = 0;
                cptx < LG_BOITE;
                cptx ++)
        {
            couleur = Lire_Point (page,origx + cptx,origy + cpty);
            *(str + cptstr) = couleur;
            cptstr ++;
        }
    }
    for (cpty = 0;
            cpty < 15;
            cpty ++)
    {
        for (cptx = 0;
                cptx < 15;
                cptx ++)
        {
            Afficher_Bob (page,BOB_BLOC+1,
                          origx + ( cptx * 10 ),
                          origy + ( cpty * 10 ),
                          MASK_OFF);
        }
    }
    Tracer_Droite (page,origx+LG_BOITE-1,origy+HT_BOITE-1,
                   origx+LG_BOITE-1,origy,COUL_DB);
    Tracer_Droite (page,origx+LG_BOITE-1,origy+HT_BOITE-1,
                   origx,origy+HT_BOITE-1,COUL_DB);
    Tracer_Droite (page,origx,origy,origx+LG_BOITE-1,origy,COUL_GH);
    Tracer_Droite (page,origx,origy,origx,origy+HT_BOITE-1,COUL_GH);
}
void Effacer_Boite (OCTET page)
{
    OCTET couleur;
    short cptstr;
    short origx;
    short origy;
    short cpty;
    short cptx;
    origx = ( ( X_MAX * LG_BOB ) - LG_BOITE ) / 2;
    origy = ( ( Y_MAX * HT_BOB ) - HT_BOITE ) / 2;
    cptstr = 0;
    for (cpty = 0;
            cpty < HT_BOITE;
            cpty ++)
    {
        for (cptx = 0;
                cptx < LG_BOITE;
                cptx ++)
        {
            couleur = *(str + cptstr);
            cptstr ++;
            Afficher_Point (page,origx + cptx,origy + cpty,couleur);
        }
    }
    free(str);
}
void Print_Cl (OCTET page,float x,float y,OCTET cl_car,OCTET cl_fond,
               char *message)
{
    short origx;
    short origy;
    short posx;
    short posy;
    origx = ( ( X_MAX * LG_BOB ) - LG_BOITE ) / 2;
    origy = ( ( Y_MAX * HT_BOB ) - HT_BOITE ) / 2;
    posx = ( origx + ( (x - 1) * 8 ) ) + 7;
    posy = ( origy + ( (y - 1) * 8 ) ) + 7;
    Print (page,posx,posy,cl_car,cl_fond,message);
}
void Combler_Zero (char *buffer,char lgnb)
{
    char cpt;
    char nbzero;
    char backup [7];
    nbzero = lgnb - strlen (buffer);
    if (nbzero > 0)
    {
        strcpy (backup,"\0");
        for (cpt = 0;
                cpt < nbzero;
                cpt ++)
            strcat (backup,"0");
        strcat (backup,buffer);
        strcpy (buffer,backup);
    }
}
