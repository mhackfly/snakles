#include "SOUREDIT/EDITSOUR.H"
#include "SOUREDIT/EDITGRAP.H"
#include "SOUREDIT/EDITPANN.H"
#include "SOUREDIT/EDITTABL.H"
#include "SOUREDIT/EDITBOIT.H"
#include "SOUREDIT/EDITONGL.H"
short Traiter_Bordures (void);
short Traiter_Fonds (void);
void Selection (OCTET,OCTET,short);
void Traiter_Apercu (void);
void Afficher_Apercu_Tableau (void);
short select_bordure;
short select_fond;
OCTET buffer_bordure [10][20] =
{
    { 4, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 7},
    {11, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,11},
    {11, 0, 4, 6, 5, 0, 0, 0, 4, 6, 6, 7, 0, 0, 0, 2, 6, 7, 0,11},
    {12, 6,15, 0, 0, 0, 0, 0,11, 0, 0,11, 0, 0, 0, 0, 0,12, 6,15},
    {11, 0, 9, 0, 0, 1, 0, 2,14, 6, 6,14, 5, 0, 1, 0, 0, 9, 0,11},
    {11, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,11},
    {11, 0, 3, 0, 3, 0, 0, 2, 7, 0, 0, 4, 5, 0, 0, 3, 0, 3, 0,11},
    {11, 0,10, 6,16, 5, 0, 0,10, 8, 8,13, 0, 0, 2,16, 6,13, 0,11},
    {11, 0, 0, 0,11, 0, 0, 0, 0,12,15, 0, 0, 0, 0,11, 0, 0, 0,11},
    {10, 6, 6, 6,14, 6, 6, 6, 6,14,14, 6, 6, 6, 6,14, 6, 6, 6,13}
};
void Panneau_5 (void)
{
    short x,y;
    OCTET page;
    short numero_element;
    Lire_Tableau ( Lire_Tableau_Encours() );
    Ecrire_Panneau_Encours (Lire_Panneau_Demande () );
    Ecrire_Panneau_Demande (0);
    page = (Lire_Page () == 0) ? 1 : 0;
    Afficher_Onglet (page,ONGLET5);
    Lire_Image_Pcx ("SPRFILES/DECORS",page,6,33,MASK_OFF,6,33,307,360);
    Changer_Page (page);
    Activer_Zone_Croix (6,33,313,393);
    select_bordure = Conv_Coord_Num (BORDURES,Lire_Xbordure (),Lire_Ybordure ());
    select_fond = Conv_Coord_Num (FONDS,Lire_Xfond (),Lire_Yfond ());
    Selection (BORDURES,ON,select_bordure);
    Afficher_Nombre (Lire_Page (),BOB_CHIFFRE,2,select_bordure,97,20,MASK_OFF);
    Selection (FONDS,ON,select_fond );
    Afficher_Nombre (Lire_Page (),BOB_CHIFFRE,3,select_fond,139,20,MASK_OFF);
    do
    {
        if ( Test_Clic_Zone (X_Fleche (),Y_Fleche (),X_MIN_BORDURES,
                             Y_MIN_BORDURES,
                             X_MAX_BORDURES,
                             Y_MAX_BORDURES) == ON)
        {
            numero_element = Traiter_Bordures ();
            if ( (numero_element != select_bordure) & (numero_element != 0) )
            {
                Selection (BORDURES,OFF,select_bordure);
                select_bordure = numero_element;
                Selection (BORDURES,ON,select_bordure);
                Afficher_Nombre (Lire_Page (),BOB_CHIFFRE,2,
                                 select_bordure,97,20,MASK_OFF);
            }
        }
        if ( Test_Clic_Zone (X_Fleche (),Y_Fleche (),X_MIN_FONDS,
                             Y_MIN_FONDS,
                             X_MAX_FONDS,
                             Y_MAX_FONDS) == ON)
        {
            numero_element = Traiter_Fonds ();
            if ( (numero_element != select_fond) & (numero_element != 0) )
            {
                Selection (FONDS,OFF,select_fond);
                select_fond = numero_element;
                Selection (FONDS,ON,select_fond);
                Afficher_Nombre (Lire_Page (),BOB_CHIFFRE,3,
                                 select_fond,139,20,MASK_OFF);
            }
        }
        if ( Test_Clic_Zone (X_Fleche (),Y_Fleche (),5,15,49,29) == ON )
        {
            Option (OFF,Lire_Page (),5,15,49,29);
            Traiter_Apercu ();
            Option (ON,Lire_Page (),5,15,49,29);
        }
    }
    while (Lire_Panneau_Demande () == 0);
    Conv_Num_Coord (BORDURES,select_bordure,&x,&y);
    Ecrire_Xbordure (x);
    Ecrire_Ybordure (y);
    Conv_Num_Coord (FONDS,select_fond,&x,&y);
    Ecrire_Xfond (x);
    Ecrire_Yfond (y);
    Desactiver_Zone_Croix ();
    Sauver_Tableau (Lire_Tableau_Encours ());
}
short Traiter_Bordures (void)
{
    short rep;
    OCTET tabx;
    OCTET taby;
    OCTET cptx;
    OCTET cpty;
    tabx = OFF;
    taby = OFF;
    for (cptx = 0;
            cptx < X_NB_BORDURES;
            cptx ++)
    {
        if (X_Fleche() >= (X_MIN_BORDURES + (cptx * X_ECART_BORDURES)))
        {
            if (X_Fleche() <= (X_MIN_BORDURES + (cptx * X_ECART_BORDURES) + LG_BORDURES-1))
            {
                tabx = ON;
                break;
            }
        }
    }
    for (cpty = 0;
            cpty < Y_NB_BORDURES;
            cpty ++)
    {
        if (Y_Fleche() >= (Y_MIN_BORDURES + (cpty * Y_ECART_BORDURES)))
        {
            if (Y_Fleche() <= (Y_MIN_BORDURES + (cpty * Y_ECART_BORDURES) + HT_BORDURES-1))
            {
                taby = ON;
                break;
            }
        }
    }
    if ( (tabx == ON) & (taby == ON) )
        rep = (X_NB_BORDURES * cpty) + (cptx + 1);
    else
        rep = 0;
    return (rep);
}
short Traiter_Fonds (void)
{
    short rep;
    OCTET tabx;
    OCTET taby;
    OCTET cptx;
    OCTET cpty;
    tabx = OFF;
    taby = OFF;
    for (cptx = 0;
            cptx < X_NB_FONDS;
            cptx ++)
    {
        if (X_Fleche() >= (X_MIN_FONDS + (cptx * X_ECART_FONDS)))
        {
            if (X_Fleche() <= (X_MIN_FONDS + (cptx * X_ECART_FONDS) + LG_FONDS-1))
            {
                tabx = ON;
                break;
            }
        }
    }
    for (cpty = 0;
            cpty < Y_NB_FONDS;
            cpty ++)
    {
        if (Y_Fleche() >= (Y_MIN_FONDS + (cpty * Y_ECART_FONDS)))
        {
            if (Y_Fleche() <= (Y_MIN_FONDS + (cpty * Y_ECART_FONDS) + HT_FONDS-1))
            {
                taby = ON;
                break;
            }
        }
    }
    if ( (tabx == ON) & (taby == ON) )
        rep = (X_NB_FONDS * cpty) + (cptx + 1);
    else
        rep = 0;
    return (rep);
}
void Selection (OCTET element,OCTET etat,short numero)
{
    short x,y;
    OCTET pg;
    OCTET coul;
    short lg;
    short ht;
    pg = Lire_Page ();
    coul = (etat == OFF) ? SELECTION_ELEMENT_OFF : SELECTION_ELEMENT_ON;
    lg = (element == BORDURES) ? LG_BORDURES : LG_FONDS;
    ht = (element == BORDURES) ? HT_BORDURES : HT_FONDS;
    Conv_Num_Coord (element,numero,&x,&y);
    Souris (OFF);
    Tracer_Droite (pg,x-1,y-1,x+lg,y-1,coul);
    Tracer_Droite (pg,x-1,y+ht,x+lg,y+ht,coul);
    Tracer_Droite (pg,x-1,y-1,x-1,y+ht,coul);
    Tracer_Droite (pg,x+lg,y-1,x+lg,y+ht,coul);
    Souris (ON);
}
void Traiter_Apercu (void)
{
    OCTET page;
    short cpt;
    short x,y;
    OCTET sortie;
    sortie = OFF;
    page = Lire_Page ();
    Souris (OFF);
    Conv_Num_Coord (BORDURES,select_bordure,&x,&y);
    for (cpt = 0;
            cpt < NB_BOB_BORDURE;
            cpt ++)
        Lire_Bob (BOB_BORDURE + cpt,page,x + (cpt * BORDURE_LONG),y);
    Conv_Num_Coord (FONDS,select_fond,&x,&y);
    Lire_Bob (BOB_FOND,page,x,y);
    Souris (ON);
    WAIT_NO_CLIC;
    Afficher_Boite_Message (page,INFO07);
    Afficher_Apercu_Tableau ();
    do
    {
        if ( Test_Option (INFO07_OK) == ON )
        {
            sortie = ON;
            Option (OFF,page,INFO07_OK);
            WAIT_NO_CLIC;
            Option (ON,page,INFO07_OK);
        }
    }
    while (sortie == OFF);
    Effacer_Boite (page);
    Ecrire_Panneau_Demande (0);
}
void Afficher_Apercu_Tableau (void)
{
    OCTET cptx,cpty;
    short x1,y1;
    x1 = CARX(0) + INFO07_COIN_X;
    y1 = CARY(0) + INFO07_COIN_Y;
    for (cpty = 0;
            cpty < 10;
            cpty ++)
    {
        for (cptx = 0;
                cptx < 20;
                cptx ++)
        {
            Afficher_Bob (Lire_Page(),
                          BOB_FOND,
                          x1 + (cptx * FOND_LONG),
                          y1 + (cpty * FOND_HAUT),
                          MASK_OFF);
            if (buffer_bordure [cpty][cptx] != 0)
                Afficher_Bob (Lire_Page(),
                              BOB_BORDURE + ( buffer_bordure [cpty][cptx] - 1 ),
                              x1 + (cptx * FOND_LONG),
                              y1 + (cpty * FOND_HAUT),
                              MASK_ON);
        }
    }
}
