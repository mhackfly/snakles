#include <STDLIB.H>
#include "SOUREDIT/EDITGRAP.H"
#include "SOUREDIT/EDITPANN.H"
#include "SOUREDIT/EDITTABL.H"
#include "SOUREDIT/EDITBOIT.H"
#include "SOUREDIT/EDITSOUR.H"
#include "SOUREDIT/EDITCHAR.H"
#define COUL_FOND 112
#define COUL_GH 96
#define COUL_DB 132
#define COUL_CAR_B 240
#define COUL_CAR_J 107
#define COUL_CAR_C 96
void Print_Cl (OCTET,float,float,OCTET,OCTET,char*);
char *str;
void Afficher_Boite_Message (OCTET page,OCTET num)
{
    short x,y;
    Afficher_Boite (page);
    switch (num)
    {
    case INFO01:
    {
        Souris (OFF);
        Print_Cl (page,4.5,6,COUL_CAR_B,COUL_FOND,"LE TABLEAU");
        Print_Cl (page,5,7,COUL_CAR_B,COUL_FOND,"NUMERO");
        Print_Cl (page,2,8,COUL_CAR_B,COUL_FOND,"VA ETRE DETRUIT");
        Print_Cl (page,3.5,10,COUL_CAR_B,COUL_FOND,"CONFIRMATION");
        Print_Cl (page,3,16,COUL_CAR_J,COUL_FOND,"OUI");
        Print_Cl (page,13,16,COUL_CAR_J,COUL_FOND,"NON");
        Souris (ON);
        Option (ON,page,INFO01_OUI);
        Option (ON,page,INFO01_NON);
        break;
    }
    case INFO02:
    {
        Souris (OFF);
        Print_Cl (page,6,1,COUL_CAR_B,COUL_FOND,"VITESSE");
        Print_Cl (page,3,3,COUL_CAR_J,COUL_FOND,"R   N   L   A");
        Print_Cl (page,5,7,COUL_CAR_B,COUL_FOND,"NOMBRE DE");
        Print_Cl (page,1,8,COUL_CAR_B,COUL_FOND,"DEPLACEMENT AVANT");
        Print_Cl (page,1.5,9,COUL_CAR_B,COUL_FOND,"UN CHANGEMENT DE");
        Print_Cl (page,5,10,COUL_CAR_B,COUL_FOND,"DIRECTION");
        Print_Cl (page,5.5,12,COUL_CAR_J,COUL_FOND,"<      >");
        Print_Cl (page,8.5,16,COUL_CAR_J,COUL_FOND,"OK");
        Souris (ON);
        Option (ON,page,INFO02_R);
        Option (ON,page,INFO02_N);
        Option (ON,page,INFO02_L);
        Option (ON,page,INFO02_A);
        Option (ON,page,INFO02_GAUCHE);
        Option (ON,page,INFO02_DROITE);
        Option (ON,page,INFO02_OK);
        break;
    }
    case INFO03:
    {
        Souris (OFF);
        Print_Cl (page,6,1,COUL_CAR_B,COUL_FOND,"VITESSE");
        Print_Cl (page,5,3,COUL_CAR_J,COUL_FOND,"R   N   L");
        Print_Cl (page,6,5,COUL_CAR_B,COUL_FOND,"OPTIONS");
        Print_Cl (page,8.5,16,COUL_CAR_J,COUL_FOND,"OK");
        Souris (ON);
        Option (ON,page,INFO03_R);
        Option (ON,page,INFO03_N);
        Option (ON,page,INFO03_L);
        Option (ON,page,INFO03_SO1);
        Option (ON,page,INFO03_SO2);
        Option (ON,page,INFO03_MO1);
        Option (ON,page,INFO03_MO2);
        Option (ON,page,INFO03_FL1);
        Option (ON,page,INFO03_FL2);
        Souris (OFF);
        x = CADX(2)+3;
        y = CADY(6)+3;
        Afficher_Bob (page,SNAKLES_BLANC+ 2,x+ 0,y,MASK_ON);
        Afficher_Bob (page,SNAKLES_BLANC+ 0,x+ 7,y,MASK_ON);
        Afficher_Bob (page,SNAKLES_BLANC+ 0,x+14,y,MASK_ON);
        Afficher_Bob (page,SNAKLES_BLANC+ 8,x+21,y,MASK_ON);
        Afficher_Bob (page,SNAKLES_BLANC+ 0,x+28,y,MASK_ON);
        Afficher_Bob (page,SNAKLES_BLANC+10,x+35,y,MASK_ON);
        x = CADX(10)+3;
        y = CADY(6)+3;
        Afficher_Bob (page,SNAKLES_BLANC+ 2,x+ 0,y,MASK_ON);
        Afficher_Bob (page,SNAKLES_BLANC+ 0,x+ 7,y,MASK_ON);
        Afficher_Bob (page,SNAKLES_BLANC+ 0,x+14,y,MASK_ON);
        Afficher_Bob (page,SNAKLES_BLANC+ 0,x+21,y,MASK_ON);
        Afficher_Bob (page,SNAKLES_BLANC+ 0,x+28,y,MASK_ON);
        Afficher_Bob (page,SNAKLES_BLANC+ 6,x+35,y,MASK_ON);
        x = CADX(2)+3;
        y = CADY(9)+3;
        Afficher_Bob (page,SNAKLES_VERT+ 2,x+ 0,y,MASK_ON);
        Afficher_Bob (page,SNAKLES_VERT+ 0,x+ 7,y,MASK_ON);
        Afficher_Bob (page,SNAKLES_VERT+ 0,x+14,y,MASK_ON);
        Afficher_Bob (page,SNAKLES_VERT+ 6,x+21,y,MASK_ON);
        Afficher_Bob (page,SNAKLES_BLANC+ 0,x+28,y,MASK_ON);
        Afficher_Bob (page,SNAKLES_BLANC+ 6,x+35,y,MASK_ON);
        x = CADX(10)+3;
        y = CADY(9)+3;
        Afficher_Bob (page,SNAKLES_VERT+ 2,x+ 0,y,MASK_ON);
        Afficher_Bob (page,SNAKLES_VERT+ 0,x+ 7,y,MASK_ON);
        Afficher_Bob (page,SNAKLES_VERT+ 6,x+14,y,MASK_ON);
        Afficher_Bob (page,SNAKLES_ORANGE+ 2,x+21,y,MASK_ON);
        Afficher_Bob (page,SNAKLES_ORANGE+ 0,x+28,y,MASK_ON);
        Afficher_Bob (page,SNAKLES_ORANGE+ 6,x+35,y,MASK_ON);
        x = CADX(2)+3;
        y = CADY(12)+3;
        Afficher_Bob (page,SNAKLES_BLANC+ 2,x+ 0,y,MASK_ON);
        Afficher_Bob (page,SNAKLES_BLANC+ 0,x+ 7,y,MASK_ON);
        Afficher_Bob (page,SNAKLES_BLANC+ 0,x+14,y,MASK_ON);
        Afficher_Bob (page,SNAKLES_BLANC+ 6,x+21,y,MASK_ON);
        Tracer_Droite (page,x+29,y+5,x+29+(12),y+5,240);
        x = CADX(10)+3;
        y = CADY(12)+3;
        Afficher_Bob (page,SNAKLES_BLANC+ 2,x+ 0,y,MASK_ON);
        Afficher_Bob (page,SNAKLES_BLANC+ 0,x+ 7,y,MASK_ON);
        Afficher_Bob (page,SNAKLES_BLANC+ 0,x+14,y,MASK_ON);
        Afficher_Bob (page,SNAKLES_BLANC+ 6,x+21,y,MASK_ON);
        Afficher_Point (page,x+29+ 0,y+5,240);
        Afficher_Point (page,x+29+ 2,y+5,240);
        Afficher_Point (page,x+29+ 4,y+5,240);
        Afficher_Point (page,x+29+ 6,y+5,240);
        Afficher_Point (page,x+29+ 8,y+5,240);
        Afficher_Point (page,x+29+10,y+5,240);
        Afficher_Point (page,x+29+12,y+5,240);
        Souris (ON);
        Option (ON,page,INFO03_OK);
        break;
    }
    case INFO04:
    {
        Souris (OFF);
        Nombre_Option (INFO04_NB,page,INFO04_LGNB,Lire_Temps ());
        Print_Cl (page,1.5,5,COUL_CAR_B,COUL_FOND,"COMPTE A REBOURS");
        Print_Cl (page,2,6,COUL_CAR_B,COUL_FOND,"SUR LA DUREE DU");
        Print_Cl (page,6,7,COUL_CAR_B,COUL_FOND,"TABLEAU");
        Print_Cl (page,6,9,COUL_CAR_J,COUL_FOND,"<");
        Print_Cl (page,12,9,COUL_CAR_J,COUL_FOND,">");
        Print_Cl (page,8.5,16,COUL_CAR_J,COUL_FOND,"OK");
        Souris (ON);
        Option (ON,page,INFO04_GAUCHE);
        Option (ON,page,INFO04_DROITE);
        Option (ON,page,INFO04_OK);
        break;
    }
    case INFO05:
    {
        Souris (OFF);
        Nombre_Option (INFO05_1_NB,page,INFO05_1_LGNB,Lire_Vlbonus () );
        Nombre_Option (INFO05_2_NB,page,INFO05_2_LGNB,Lire_Temps_Plus ());
        Nombre_Option (INFO05_3_NB,page,INFO05_3_LGNB,Lire_Temps_Moins ());
        x = CARX(3);
        y = CARY(1)-2;
        Afficher_Bob (page,BOB_PASTILLE+13,x,y,MASK_ON);
        Print_Cl (page,5,1,COUL_CAR_B,COUL_FOND,"BONUS POINT");
        Print_Cl (page,6,3,COUL_CAR_J,COUL_FOND,"<");
        Print_Cl (page,12,3,COUL_CAR_J,COUL_FOND,">");
        x = CARX(3.5);
        y = CARY(6)-2;
        Afficher_Bob (page,BOB_PASTILLE+20,x,y,MASK_ON);
        Print_Cl (page,5.5,6,COUL_CAR_B,COUL_FOND,"TEMPS PLUS");
        Print_Cl (page,6,8,COUL_CAR_J,COUL_FOND,"<");
        Print_Cl (page,12,8,COUL_CAR_J,COUL_FOND,">");
        x = CARX(3);
        y = CARY(11)-2;
        Afficher_Bob (page,BOB_PASTILLE+21,x,y,MASK_ON);
        Print_Cl (page,5,11,COUL_CAR_B,COUL_FOND,"TEMPS MOINS");
        Print_Cl (page,6,13,COUL_CAR_J,COUL_FOND,"<");
        Print_Cl (page,12,13,COUL_CAR_J,COUL_FOND,">");
        Print_Cl (page,8.5,16,COUL_CAR_J,COUL_FOND,"OK");
        Souris (ON);
        Option (ON,page,INFO05_1_GAUCHE);
        Option (ON,page,INFO05_1_DROITE);
        Option (ON,page,INFO05_2_GAUCHE);
        Option (ON,page,INFO05_2_DROITE);
        Option (ON,page,INFO05_3_GAUCHE);
        Option (ON,page,INFO05_3_DROITE);
        Option (ON,page,INFO05_OK);
        break;
    }
    case INFO06:
    {
        Souris (OFF);
        Print_Cl (page,1,6,COUL_CAR_B,COUL_FOND,"TOUS LES SERPENTS");
        Print_Cl (page,4.5,7,COUL_CAR_B,COUL_FOND,"VONT ETRES");
        Print_Cl (page,6,8,COUL_CAR_B,COUL_FOND,"EFFACES");
        Print_Cl (page,3.5,10,COUL_CAR_B,COUL_FOND,"CONFIRMATION");
        Print_Cl (page,3,16,COUL_CAR_J,COUL_FOND,"OUI");
        Print_Cl (page,13,16,COUL_CAR_J,COUL_FOND,"NON");
        Souris (ON);
        Option (ON,page,INFO06_OUI);
        Option (ON,page,INFO06_NON);
        break;
    }
    case INFO07:
    {
        Souris (OFF);
        Print_Cl (page,8.5,16,COUL_CAR_J,COUL_FOND,"OK");
        Souris (ON);
        Option (ON,page,INFO05_OK);
        break;
    }
    case INFO08:
    {
        Souris (OFF);
        Print_Cl (page,1.5,6,COUL_CAR_B,COUL_FOND,"TOUS LES DESSINS");
        Print_Cl (page,4.5,7,COUL_CAR_B,COUL_FOND,"VONT ETRES");
        Print_Cl (page,6,8,COUL_CAR_B,COUL_FOND,"EFFACES");
        Print_Cl (page,3.5,10,COUL_CAR_B,COUL_FOND,"CONFIRMATION");
        Print_Cl (page,3,16,COUL_CAR_J,COUL_FOND,"OUI");
        Print_Cl (page,13,16,COUL_CAR_J,COUL_FOND,"NON");
        Souris (ON);
        Option (ON,page,INFO08_OUI);
        Option (ON,page,INFO08_NON);
        break;
    }
    case INFO09:
    {
        Souris (OFF);
        Print_Cl (page,5,6,COUL_CAR_B,COUL_FOND,"SORTIE DE");
        Print_Cl (page,5,7,COUL_CAR_B,COUL_FOND,"l'EDITEUR");
        Print_Cl (page,3.5,9,COUL_CAR_B,COUL_FOND,"CONFIRMATION");
        Print_Cl (page,3,16,COUL_CAR_J,COUL_FOND,"OUI");
        Print_Cl (page,13,16,COUL_CAR_J,COUL_FOND,"NON");
        Souris (ON);
        Option (ON,page,INFO09_OUI);
        Option (ON,page,INFO09_NON);
        break;
    }
    case INFO10:
    {
        Souris (OFF);
        Print_Cl (page,3,6,COUL_CAR_B,COUL_FOND,"LE TABLEAU VA");
        Print_Cl (page,4,7,COUL_CAR_B,COUL_FOND,"ETRE EFFACE");
        Print_Cl (page,3.5,9,COUL_CAR_B,COUL_FOND,"CONFIRMATION");
        Print_Cl (page,3,16,COUL_CAR_J,COUL_FOND,"OUI");
        Print_Cl (page,13,16,COUL_CAR_J,COUL_FOND,"NON");
        Souris (ON);
        Option (ON,page,INFO10_OUI);
        Option (ON,page,INFO10_NON);
        break;
    }
    case INFO11:
    {
        Souris (OFF);
        Print_Cl (page,2,8,COUL_CAR_B,COUL_FOND,"TABLEAU COMPLET");
        Print_Cl (page,8.5,16,COUL_CAR_J,COUL_FOND,"OK");
        Souris (ON);
        Option (ON,page,INFO11_OK);
        break;
    }
    case INFO12:
    {
        Souris (OFF);
        Print_Cl (page,1,4,COUL_CAR_B,COUL_FOND,"TABLEAU INCOMPLET");
        Print_Cl (page,1,6,COUL_CAR_B,COUL_FOND,"CONDITIONS:");
        Print_Cl (page,3,8,COUL_CAR_B,COUL_FOND,"-AU MOINS UNE");
        Print_Cl (page,4,9,COUL_CAR_B,COUL_FOND,"PASTILLE BLEU");
        Print_Cl (page,3,11,COUL_CAR_B,COUL_FOND,"-SERPENT BLANC");
        Print_Cl (page,4,12,COUL_CAR_B,COUL_FOND,"DEFINI");
        Print_Cl (page,8.5,16,COUL_CAR_J,COUL_FOND,"OK");
        Souris (ON);
        Option (ON,page,INFO12_OK);
        break;
    }
    case INFO13:
    {
        Souris (OFF);
        Print_Cl (page,2,5,COUL_CAR_B,COUL_FOND,"SNAKLES EDITEUR");
        Print_Cl (page,4,6,COUL_CAR_B,COUL_FOND,"V2.0  09/97");
        Print_Cl (page,3.5,9,COUL_CAR_B,COUL_FOND,"MARTY Michel");
        Print_Cl (page,8.5,16,COUL_CAR_J,COUL_FOND,"OK");
        Souris (ON);
        Option (ON,page,INFO13_OK);
        break;
    }
    case INFO14:
    {
        Souris (OFF);
        Print_Cl (page,4,8,COUL_CAR_B,COUL_FOND,"LECTURE DES");
        Print_Cl (page,5.5,9,COUL_CAR_B,COUL_FOND,"TABLEAUX");
        Souris (ON);
        break;
    }
    case INFO15:
    {
        Souris (OFF);
        Print_Cl (page,2.5,6,COUL_CAR_B,COUL_FOND,"CREATION D'UNE");
        Print_Cl (page,2.5,7,COUL_CAR_B,COUL_FOND,"NOUVELLE SERIE");
        Print_Cl (page,3.5,9,COUL_CAR_B,COUL_FOND,"CONFIRMATION");
        Print_Cl (page,3,16,COUL_CAR_J,COUL_FOND,"OUI");
        Print_Cl (page,13,16,COUL_CAR_J,COUL_FOND,"NON");
        Souris (ON);
        Option (ON,page,INFO10_OUI);
        Option (ON,page,INFO10_NON);
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
    origx = ( LIMITE_X_ECRAN - LG_BOITE ) / 2;
    origy = ( LIMITE_Y_ECRAN - HT_BOITE ) / 2;
    str = (char *) malloc ( LG_BOITE * HT_BOITE );
    cptstr = 0;
    Souris (OFF);
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
            Afficher_Bob (page,BOB_BLOC_BLEU,
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
    Souris (ON);
}
void Effacer_Boite (OCTET page)
{
    OCTET couleur;
    short cptstr;
    short origx;
    short origy;
    short cpty;
    short cptx;
    origx = ( LIMITE_X_ECRAN - LG_BOITE ) / 2;
    origy = ( LIMITE_Y_ECRAN - HT_BOITE ) / 2;
    cptstr = 0;
    Souris (OFF);
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
    Souris (ON);
    free(str);
}
void Print_Cl (OCTET page,float x,float y,OCTET cl_car,OCTET cl_fond,
               char *message)
{
    short posx;
    short posy;
    posx = ( ( ( LIMITE_X_ECRAN - LG_BOITE ) / 2 ) + ( (x - 1) * 8 ) ) + 7;
    posy = ( ( ( LIMITE_Y_ECRAN - HT_BOITE ) / 2 ) + ( (y - 1) * 8 ) ) + 7;
    Print (page,posx,posy,cl_car,cl_fond,message);
}
