#include <STRING.H>
#include <STDIO.H>
#include "SOUREDIT/EDITSOUR.H"
#include "SOUREDIT/EDITPANN.H"
#include "SOUREDIT/EDITTABL.H"
#include "SOUREDIT/EDITGRAP.H"
#include "SOUREDIT/EDITONGL.H"
#include "SOUREDIT/EDITCHAR.H"
#define CLBLANC 242
#define CLGRIS 248
#define CLJAUNE 9
#define CLBLEU 96
#define CVX(x) ( (x - 1) * 8 ) + 8
#define CVY(y) ( (y - 1) * 8 ) + 22
void Print_Text_Box (float,float,OCTET,char*);
void Tracer_Cadre (float,float,float,float,OCTET);
void Print_Valeur_Box (float,float,OCTET,short,char);
void Combler_Zero (char*,char);
extern OCTET buftab1_sans_cadre [BUFSIZE_SANS_CADRE];
OCTET page;
void Panneau_6 (void)
{
    OCTET cpt;
    short x,y;
    OCTET col,lig;
    float xbox,ybox;
    long ocdes;
    float pourcent;
    char buf [7];
    OCTET buffer [4][16] =
    {
        { 4, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 7},
        {11, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,11},
        {11, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,11},
        {10, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6,13}
    };
    Lire_Tableau ( Lire_Tableau_Encours() );
    Lire_Buftab_Sans_Cadre (buftab1_sans_cadre);
    Ecrire_Panneau_Encours (Lire_Panneau_Demande () );
    Ecrire_Panneau_Demande (0);
    page = (Lire_Page () == 0) ? 1 : 0;
    Lire_Image_Pcx ("SPRFILES/DECORS",page,0,0,MASK_OFF,0,0,319,399);
    for (cpt = 0;
            cpt < NB_BOB_BORDURE;
            cpt++)
        Lire_Bob (BOB_BORDURE + cpt,page,
                  Lire_Xbordure () + (cpt * BORDURE_LONG),
                  Lire_Ybordure () );
    Lire_Bob (BOB_FOND,page,
              Lire_Xfond (),
              Lire_Yfond ());
    Afficher_Onglet (page,ONGLET6);
    xbox = 3;
    ybox = 14.5;
    Tracer_Cadre (xbox,ybox,20,6,CLGRIS);
    Print_Text_Box (xbox+6,ybox+1,CLBLEU,"DESSINS");
    Print_Text_Box (xbox+1,ybox+3,CLBLANC,"NOMBRE  :");
    Print_Valeur_Box (xbox+14,ybox+3,CLJAUNE,Lire_Nbdessin (),2);
    Print_Text_Box (xbox+16,ybox+3,CLBLANC,"/32");
    Print_Text_Box (xbox+1,ybox+4,CLBLANC,"SURFACE :");
    Print_Text_Box (xbox+18,ybox+4,CLBLANC,"%");
    ocdes = 0L;
    for (cpt = 0;
            cpt < Lire_Nbdessin ();
            cpt ++)
        ocdes += ( (long)(Lire_Lgdessin(cpt) * 7) *
                   (long)(Lire_Htdessin(cpt) * 11) );
    pourcent = (float)(ocdes * 100L) / (float)109263L;
    sprintf (buf,"%.2f",pourcent);
    Combler_Zero (buf,6);
    Print_Text_Box (xbox+11,ybox+4,CLJAUNE,buf);
    xbox = 1;
    ybox = 21;
    Tracer_Cadre (xbox,ybox,14,26,CLGRIS);
    Print_Text_Box (xbox+1,ybox+1,CLBLEU,"SERPENTS RVB");
    Print_Text_Box (xbox+4,ybox+3,CLBLANC,"V LG DEP.");
    for (cpt = 0;
            cpt < Lire_Nbnibble_X ();
            cpt ++)
    {
        Print_Valeur_Box (xbox+1,ybox+5+cpt,CLBLANC,cpt+1,2);
        switch (Lire_Vtnibble_X (cpt))
        {
        case 0 :
        {
            Print_Text_Box (xbox+4,ybox+5+cpt,CLJAUNE,"R");
            break;
        }
        case 1 :
        {
            Print_Text_Box (xbox+4,ybox+5+cpt,CLJAUNE,"N");
            break;
        }
        case 2 :
        {
            Print_Text_Box (xbox+4,ybox+5+cpt,CLJAUNE,"L");
            break;
        }
        default :
        {
            Print_Text_Box (xbox+4,ybox+5+cpt,CLJAUNE,"A");
        }
        }
        Print_Valeur_Box (xbox+6,ybox+5+cpt,CLJAUNE,Lire_Lgnibble_X (cpt),2);
        Print_Valeur_Box (xbox+9,ybox+5+cpt,CLJAUNE,Lire_Tpnibble_X (cpt),4);
    }
    xbox = 1;
    ybox = 2;
    Tracer_Cadre (xbox,ybox,9,11,CLGRIS);
    Print_Text_Box (xbox+1,ybox+1,CLBLEU,"TABLEAU");
    Print_Valeur_Box (xbox+3.5,ybox+3,CLJAUNE,Lire_Tableau_Encours (),2);
    Afficher_Mini_Tableau_Isole (page,Lire_Tableau_Encours (),
                                 CVX(xbox + 1.8),CVY(ybox + 4.9));
    xbox = 24;
    ybox = 1;
    Tracer_Cadre (xbox,ybox,15,23,CLGRIS);
    Print_Text_Box (xbox+3,ybox+1,CLBLEU,"PASTILLES");
    for (cpt = 0;
            cpt <= 18;
            cpt ++)
    {
        Afficher_Bob (page,BOB_PASTILLE+cpt,CVX(xbox+1),
                      CVY(ybox+2.8+cpt),MASK_OFF);
        Print_Valeur_Box (xbox+ 3,ybox+3+cpt,CLJAUNE,
                          Totaliser_Pastilles (cpt+ 1),4);
        Afficher_Bob (page,BOB_PASTILLE+cpt+19,CVX(xbox+8),
                      CVY(ybox+2.8+cpt),MASK_OFF);
        Print_Valeur_Box (xbox+10,ybox+3+cpt,CLJAUNE,
                          Totaliser_Pastilles (cpt+20),4);
    }
    xbox = 15;
    ybox = 25;
    Tracer_Cadre (xbox,ybox,24,3,CLGRIS);
    Print_Text_Box (xbox+1,ybox+1,CLBLEU,"COMPTE A REBOURS :");
    Print_Valeur_Box (xbox+20,ybox+1,CLJAUNE,Lire_Temps (),3);
    xbox = 17.5;
    ybox = 28;
    Tracer_Cadre (xbox,ybox,19,3,CLGRIS);
    Print_Text_Box (xbox+1,ybox+1,CLBLEU,"BONUS POINT :");
    Print_Valeur_Box (xbox+15,ybox+1,CLJAUNE,Lire_Vlbonus (),3);
    xbox = 17.5;
    ybox = 31;
    Tracer_Cadre (xbox,ybox,19,3,CLGRIS);
    Print_Text_Box (xbox+1,ybox+1,CLBLEU,"TEMPS MOINS :");
    Print_Valeur_Box (xbox+15,ybox+1,CLJAUNE,Lire_Temps_Moins (),3);
    xbox = 18;
    ybox = 34;
    Tracer_Cadre (xbox,ybox,18,3,CLGRIS);
    Print_Text_Box (xbox+1,ybox+1,CLBLEU,"TEMPS PLUS :");
    Print_Valeur_Box (xbox+14,ybox+1,CLJAUNE,Lire_Temps_Plus (),3);
    xbox = 18.5;
    ybox = 37;
    Tracer_Cadre (xbox,ybox,17,10,CLGRIS);
    Print_Text_Box (xbox+1,ybox+1,CLBLEU,"BORDURE ET FOND");
    for (lig = 0;
            lig <= 3;
            lig ++)
    {
        for (col = 0;
                col <= 15;
                col ++)
        {
            Afficher_Bob (page,BOB_FOND,
                          CVX(xbox + 1.6) + (col * 7),
                          CVY(ybox + 2.9) + (lig * 11),
                          MASK_ON);
            if (buffer [lig][col] != 0)
                Afficher_Bob (page,
                              BOB_BORDURE + ( buffer [lig][col] - 1 ),
                              CVX(xbox + 1.6) + (col * 7),
                              CVY(ybox + 2.9) + (lig * 11),
                              MASK_ON);
        }
    }
    xbox = 10.5;
    ybox = 1;
    Tracer_Cadre (xbox,ybox,13,13,CLGRIS);
    Print_Text_Box (xbox+2,ybox+1,CLBLEU,"SERPENT B");
    Print_Text_Box (xbox+1,ybox+10,CLBLANC,"V  :");
    switch (Lire_Vtnibble ())
    {
    case 0 :
    {
        Print_Text_Box (xbox+6,ybox+10,CLJAUNE,"R");
        break;
    }
    case 1 :
    {
        Print_Text_Box (xbox+6,ybox+10,CLJAUNE,"N");
        break;
    }
    default :
    {
        Print_Text_Box (xbox+6,ybox+10,CLJAUNE,"L");
    }
    }
    Print_Text_Box (xbox+1,ybox+11,CLBLANC,"LG :");
    Print_Valeur_Box (xbox+6,ybox+11,CLJAUNE,Lire_Lgnibble (),2);
    if (Lire_Spnibble () == 1)
    {
        x = CVX(xbox + 4);
        y = CVY(ybox + 3);
        Afficher_Bob (page,SNAKLES_BLANC+ 2,x+ 0,y,MASK_ON);
        Afficher_Bob (page,SNAKLES_BLANC+ 0,x+ 7,y,MASK_ON);
        Afficher_Bob (page,SNAKLES_BLANC+ 0,x+14,y,MASK_ON);
        Afficher_Bob (page,SNAKLES_BLANC+ 8,x+21,y,MASK_ON);
        Afficher_Bob (page,SNAKLES_BLANC+ 0,x+28,y,MASK_ON);
        Afficher_Bob (page,SNAKLES_BLANC+10,x+35,y,MASK_ON);
    }
    else
    {
        x = CVX(xbox + 4);
        y = CVY(ybox + 3);
        Afficher_Bob (page,SNAKLES_BLANC+ 2,x+ 0,y,MASK_ON);
        Afficher_Bob (page,SNAKLES_BLANC+ 0,x+ 7,y,MASK_ON);
        Afficher_Bob (page,SNAKLES_BLANC+ 0,x+14,y,MASK_ON);
        Afficher_Bob (page,SNAKLES_BLANC+ 0,x+21,y,MASK_ON);
        Afficher_Bob (page,SNAKLES_BLANC+ 0,x+28,y,MASK_ON);
        Afficher_Bob (page,SNAKLES_BLANC+ 6,x+35,y,MASK_ON);
    }
    if (Lire_Mtnibble () == 1)
    {
        x = CVX(xbox + 4);
        y = CVY(ybox + 5);
        Afficher_Bob (page,SNAKLES_VERT+ 2,x+ 0,y,MASK_ON);
        Afficher_Bob (page,SNAKLES_VERT+ 0,x+ 7,y,MASK_ON);
        Afficher_Bob (page,SNAKLES_VERT+ 0,x+14,y,MASK_ON);
        Afficher_Bob (page,SNAKLES_VERT+ 6,x+21,y,MASK_ON);
        Afficher_Bob (page,SNAKLES_BLANC+ 0,x+28,y,MASK_ON);
        Afficher_Bob (page,SNAKLES_BLANC+ 6,x+35,y,MASK_ON);
    }
    else
    {
        x = CVX(xbox + 4);
        y = CVY(ybox + 5);
        Afficher_Bob (page,SNAKLES_VERT+ 2,x+ 0,y,MASK_ON);
        Afficher_Bob (page,SNAKLES_VERT+ 0,x+ 7,y,MASK_ON);
        Afficher_Bob (page,SNAKLES_VERT+ 6,x+14,y,MASK_ON);
        Afficher_Bob (page,SNAKLES_ORANGE+ 2,x+21,y,MASK_ON);
        Afficher_Bob (page,SNAKLES_ORANGE+ 0,x+28,y,MASK_ON);
        Afficher_Bob (page,SNAKLES_ORANGE+ 6,x+35,y,MASK_ON);
    }
    if (Lire_Flnibble () == 1)
    {
        x = CVX(xbox + 4);
        y = CVY(ybox + 7);
        Afficher_Bob (page,SNAKLES_BLANC+ 2,x+ 0,y,MASK_ON);
        Afficher_Bob (page,SNAKLES_BLANC+ 0,x+ 7,y,MASK_ON);
        Afficher_Bob (page,SNAKLES_BLANC+ 0,x+14,y,MASK_ON);
        Afficher_Bob (page,SNAKLES_BLANC+ 6,x+21,y,MASK_ON);
        Tracer_Droite (page,x+29,y+5,x+29+(12),y+5,240);
    }
    else
    {
        x = CVX(xbox + 4);
        y = CVY(ybox + 7);
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
    }
    Changer_Page (page);
    do
    {
    }
    while (Lire_Panneau_Demande () == 0);
}
void Print_Text_Box (float x,float y,OCTET cl,char *m)
{
    short posx;
    short posy;
    posx = CVX(x);
    posy = CVY(y);
    Print (page,posx,posy,cl,250,m);
}
void Tracer_Cadre (float ox,float oy,float lg,float ht,OCTET cl)
{
    short posx;
    short posy;
    posx = CVX(ox);
    posy = CVY(oy);
    Tracer_Droite (page,posx+4,posy+4,posx+(lg*8)-4,posy+4,cl);
    Tracer_Droite (page,posx+4,posy+4,posx+4,posy+(ht*8)-4,cl);
    Tracer_Droite (page,posx+(lg*8)-4,posy+4,posx+(lg*8)-4,posy+(ht*8)-4,cl);
    Tracer_Droite (page,posx+4,posy+(ht*8)-4,posx+(lg*8)-4,posy+(ht*8)-4,cl);
}
void Print_Valeur_Box (float x,float y,OCTET cl,short vl,char nbu)
{
    char buffer [7];
    sprintf (buffer,"%d",vl);
    Combler_Zero (buffer,nbu);
    Print_Text_Box (x,y,cl,buffer);
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
