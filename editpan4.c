#include "SOUREDIT/EDITSOUR.H"
#include "SOUREDIT/EDITPANN.H"
#include "SOUREDIT/EDITGRAP.H"
#include "SOUREDIT/EDITTABL.H"
#include "SOUREDIT/EDITBOIT.H"
#include "SOUREDIT/EDITONGL.H"
#include "SOUREDIT/EDITCHAR.H"
short Afficher_Obstacles_Dessins (OCTET,OCTET,OCTET,OCTET);
void Selectionner_Dessin (void);
void Tracer_Selection (short,short,short,short);
void Sauver_Selection (short,short,short,short);
void Restaurer_Selection (short,short,short,short);
OCTET Calculer_Afficher_Dessin (void);
OCTET Calculer_Effacer_Dessin (void);
void Envoyer_Elements_buffer (OCTET,OCTET);
void Effacer_Tous_Dessin (void);
OCTET Calculer_Taille_Dessin (void);
extern OCTET buftab1_sans_cadre [BUFSIZE_SANS_CADRE];
OCTET page_panneau;
OCTET page_dessins;
OCTET ht [2][(DESSINS_MAX_LG * LG_BOB)+2];
OCTET vt [2][(DESSINS_MAX_HT * HT_BOB)+2];
short nb_element;
short selection_x;
short selection_y;
OCTET selection_lg;
OCTET selection_ht;
void Panneau_4 (void)
{
    OCTET etat;
    OCTET cpt_dessin;
    OCTET nombre_dessin;
    Lire_Tableau ( Lire_Tableau_Encours() );
    Lire_Buftab_Sans_Cadre (buftab1_sans_cadre);
    Ecrire_Panneau_Encours (Lire_Panneau_Demande () );
    Ecrire_Panneau_Demande (0);
    page_panneau = (Lire_Page () == 0) ? 1 : 0;
    Afficher_Onglet (page_panneau,ONGLET4);
    Afficher_Nombre (page_panneau,BOB_CHIFFRE,2,0,310,13,MASK_OFF);
    Afficher_Nombre (page_panneau,BOB_CHIFFRE,2,0,310,20,MASK_OFF);
    nb_element = Afficher_Obstacles_Dessins (1,1,43,33);
    nombre_dessin = Lire_Nbdessin ();
    for (cpt_dessin = 0;
            cpt_dessin < nombre_dessin;
            cpt_dessin ++)
    {
        Afficher_Dessin (-2,20,page_panneau,cpt_dessin);
        Envoyer_Elements_buffer (cpt_dessin,0);
    }
    Afficher_Nombre (page_panneau,BOB_CHIFFRE,2,nombre_dessin,310,139,MASK_OFF);
    Changer_Page (page_panneau);
    page_dessins = (Lire_Page () == 0) ? 1 : 0;
    Lire_Image_Pcx ("SPRFILES/DESSINS",page_dessins,
                    0,0,MASK_OFF,0,0,319,399);
    Print (page_dessins,10,3,240,112,"X:");
    Print (page_dessins,60,3,240,112,"Y:");
    Print (page_dessins,110,3,240,112,"L:");
    Print (page_dessins,160,3,240,112,"H:");
    Afficher_Nombre (page_dessins,BOB_CHIFFRE_2,2,0,26,3,MASK_OFF);
    Afficher_Nombre (page_dessins,BOB_CHIFFRE_2,2,0,76,3,MASK_OFF);
    Afficher_Nombre (page_dessins,BOB_CHIFFRE_2,2,0,126,3,MASK_OFF);
    Afficher_Nombre (page_dessins,BOB_CHIFFRE_2,2,0,176,3,MASK_OFF);
    Print (page_dessins,40,390,245,112,"<BOUTON DE DROITE POUR SORTIR>");
    Activer_Zone_Croix (5,31,305,393);
    selection_x = 0;
    selection_y = 0;
    selection_lg = 0;
    selection_ht = 0;
    do
    {
        if ( Test_Clic_Zone (X_Fleche (),Y_Fleche (),309,51,319,79) == ON )
        {
            Option (OFF,page_panneau,309,51,319,79);
            WAIT_NO_CLIC;
            Option (ON,page_panneau,309,51,319,79);
            if (nb_element != 0)
            {
                Changer_Page (page_dessins);
                Activer_Zone_Croix (9,13,309,386);
                Selectionner_Dessin ();
                Changer_Page (page_panneau);
                Activer_Zone_Croix (5,31,305,393);
            }
        }
        if ( Test_Clic_Zone (X_Fleche (),Y_Fleche (),309,80,319,114) == ON )
        {
            Option (OFF,page_panneau,309,80,319,114);
            WAIT_NO_CLIC;
            if (nb_element != 0)
            {
                if ( (selection_lg != 0) & (selection_ht != 0) )
                {
                    do
                    {
                        etat = Calculer_Afficher_Dessin ();
                    }
                    while (etat != FAUX);
                }
            }
            Option (ON,page_panneau,309,80,319,114);
        }
        if ( Test_Clic_Zone (X_Fleche (),Y_Fleche (),309,115,319,137) == ON )
        {
            Option (OFF,page_panneau,309,115,319,137);
            WAIT_NO_CLIC;
            nombre_dessin = Lire_Nbdessin ();
            if (nombre_dessin != 0)
            {
                if (nb_element != 0)
                {
                    do
                    {
                        etat = Calculer_Effacer_Dessin ();
                    }
                    while (etat != FAUX);
                }
            }
            Option (ON,page_panneau,309,115,319,137);
        }
        if ( Test_Clic_Zone (X_Fleche (),Y_Fleche (),309,155,319,183) == ON )
        {
            Option (OFF,page_panneau,309,155,319,183);
            WAIT_NO_CLIC;
            nombre_dessin = Lire_Nbdessin ();
            if (nb_element != 0)
            {
                do
                {
                    etat = Calculer_Taille_Dessin ();
                }
                while (etat != FAUX);
            }
            Option (ON,page_panneau,309,155,319,183);
        }
        if ( Test_Clic_Zone (X_Fleche (),Y_Fleche (),309,28,319,50) == ON )
        {
            Option (OFF,page_panneau,309,28,319,50);
            WAIT_NO_CLIC;
            nombre_dessin = Lire_Nbdessin ();
            if (nombre_dessin != 0)
                if (nb_element != 0)
                    Effacer_Tous_Dessin ();
            Option (ON,page_panneau,309,28,319,50);
        }
        if (X_Case () != 0)
            Afficher_Nombre (page_panneau,BOB_CHIFFRE,2,X_Case(),310,13,MASK_OFF);
        if (Y_Case () != 0)
            Afficher_Nombre (page_panneau,BOB_CHIFFRE,2,Y_Case(),310,20,MASK_OFF);
    }
    while (Lire_Panneau_Demande () == 0);
    Desactiver_Zone_Croix ();
    Sauver_Tableau (Lire_Tableau_Encours ());
}
short Afficher_Obstacles_Dessins (OCTET x1,OCTET y1,OCTET x2,OCTET y2)
{
    OCTET cpt_x;
    OCTET cpt_y;
    short x_bob;
    short y_bob;
    short cpt_dessin;
    OCTET pastille;
    cpt_dessin = 0;
    for (cpt_y = y1;
            cpt_y <= y2;
            cpt_y ++)
    {
        for (cpt_x = x1;
                cpt_x <= x2;
                cpt_x ++)
        {
            pastille = Lire_Case (buftab1_sans_cadre,cpt_x,cpt_y);
            x_bob = X_TAB_DESSINS + ( (cpt_x - 1) * LG_BOB );
            y_bob = Y_TAB_DESSINS + ( (cpt_y - 1) * HT_BOB );
            if (pastille == OBST_DESSIN)
            {
                Afficher_Bob (page_panneau,FOND_1,x_bob,y_bob,MASK_OFF);
                Afficher_Bob (page_panneau,(BOB_PASTILLE-1) + OBST_DESSIN,
                              x_bob,y_bob,MASK_ON);
                cpt_dessin ++;
            }
            else
            {
                Ecrire_Case (buftab1_sans_cadre,0,cpt_x,cpt_y);
                Afficher_Bob (page_panneau,FOND_1,x_bob,y_bob,MASK_OFF);
            }
        }
    }
    return (cpt_dessin);
}
void Selectionner_Dessin (void)
{
    OCTET taille;
    short x1,y1;
    short x2,y2;
    short xb,yb;
    selection_x = 0;
    selection_y = 0;
    selection_lg = 0;
    selection_ht = 0;
    x1 = 0;
    y1 = 0;
    x2 = 0;
    y2 = 0;
    xb = x2;
    yb = y2;
    do
    {
        do
        {
            if (Clic_Souris () == CLIC_DROITE)
            {
                if ( (x1 != 0) & (y1 != 0) & (x2 != 0) & (y2 != 0) )
                {
                    Souris (OFF);
                    Restaurer_Selection (x1,y1,xb,yb);
                    Souris (ON);
                }
                Ecrire_Panneau_Demande (0);
                selection_x = x1+1;
                selection_y = y1+1;
                selection_lg = (x2-x1) / LG_BOB;
                selection_ht = (y2-y1) / HT_BOB;
                if (selection_lg > DESSINS_MAX_LG)
                    selection_lg = DESSINS_MAX_LG;
                if (selection_ht > DESSINS_MAX_HT)
                    selection_ht = DESSINS_MAX_HT;
                return;
            }
            if (X_Case () != 0)
                Afficher_Nombre (page_dessins,BOB_CHIFFRE_2,2,X_Case(),26,3,MASK_OFF);
            if (Y_Case () != 0)
                Afficher_Nombre (page_dessins,BOB_CHIFFRE_2,2,Y_Case(),76,3,MASK_OFF);
        }
        while (Test_Clic_Zone (X_Fleche (),Y_Fleche (),9,13,309,386) == OFF);
        if ( (x1 != 0) & (y1 != 0) & (x2 != 0) & (y2 != 0) )
        {
            Souris (OFF);
            Restaurer_Selection (x1,y1,xb,yb);
            Souris (ON);
        }
        x1 = 9 + ((X_Croix () / LG_BOB) * LG_BOB)- 1;
        y1 = 13 + ((Y_Croix () / HT_BOB) * HT_BOB)- 1;
        x2 = 9 + ((X_Croix () / LG_BOB) * LG_BOB)+ LG_BOB;
        y2 = 13 + ((Y_Croix () / HT_BOB) * HT_BOB)+ HT_BOB;
        xb = x2;
        yb = y2;
        Souris (OFF);
        Sauver_Selection (x1,y1,x2,y2);
        Tracer_Selection (x1,y1,x2,y2);
        Souris (ON);
        do
        {
            taille = (x2-x1) / LG_BOB;
            if ( (taille >= 1) & (taille <= DESSINS_MAX_LG) )
                Afficher_Nombre (page_dessins,BOB_CHIFFRE_2,2,taille,126,3,MASK_OFF);
            taille = (y2-y1) / HT_BOB;
            if ( (taille >= 1) & (taille <= DESSINS_MAX_HT) )
                Afficher_Nombre (page_dessins,BOB_CHIFFRE_2,2,taille,176,3,MASK_OFF);
            if ( (X_Croix () == -1) | (Y_Croix () == -1) )
            {
                Souris (OFF);
                Restaurer_Selection (x1,y1,xb,yb);
                Souris (ON);
                break;
            }
            x2 = 9+((X_Croix ()/LG_BOB)*LG_BOB)+LG_BOB;
            y2 = 13+((Y_Croix ()/HT_BOB)*HT_BOB)+HT_BOB;
            if ((x1+LG_BOB < x2) & (y1+HT_BOB < y2))
            {
                if ( (x2 < x1 + ((DESSINS_MAX_LG+1) * LG_BOB)) & (x2 != xb) )
                {
                    Souris (OFF);
                    Restaurer_Selection (x1,y1,xb,yb);
                    Sauver_Selection (x1,y1,x2,yb);
                    Tracer_Selection (x1,y1,x2,yb);
                    Souris (ON);
                    xb = x2;
                }
                if ( (y2 < y1 + ((DESSINS_MAX_HT+1) * HT_BOB)) & (y2 != yb) )
                {
                    Souris (OFF);
                    Restaurer_Selection (x1,y1,xb,yb);
                    Sauver_Selection (x1,y1,xb,y2);
                    Tracer_Selection (x1,y1,xb,y2);
                    Souris (ON);
                    yb = y2;
                }
            }
        }
        while (Clic_Souris () == CLIC_GAUCHE);
    }
    while (1);
}
void Tracer_Selection (short x1,short y1,short x2,short y2)
{
    short ecartx;
    short ecarty;
    ecartx = x2-x1;
    ecarty = y2-y1;
    Tracer_Droite (page_dessins,
                   x1,y1,x1 + ecartx,y1,DESSINS_SELECT_COUL);
    Tracer_Droite (page_dessins,
                   x1,y1 + ecarty,x1 + ecartx,y1 + ecarty,DESSINS_SELECT_COUL);
    Tracer_Droite (page_dessins,
                   x1,y1,x1,y1 + ecarty,DESSINS_SELECT_COUL);
    Tracer_Droite (page_dessins,
                   x1 + ecartx,y1,x1 + ecartx,y1 + ecarty,DESSINS_SELECT_COUL);
}
void Sauver_Selection (short x1,short y1,short x2,short y2)
{
    short cpt;
    OCTET couleur;
    for (cpt = 0;
            cpt <= (x2-x1);
            cpt ++)
    {
        couleur = Lire_Point (page_dessins,(x1 + cpt),y1);
        ht [0][cpt] = couleur;
        couleur = Lire_Point (page_dessins,(x1 + cpt),y2);
        ht [1][cpt] = couleur;
    }
    for (cpt = 0;
            cpt <= (y2-y1);
            cpt ++)
    {
        couleur = Lire_Point (page_dessins,x1,(y1 + cpt));
        vt [0][cpt] = couleur;
        couleur = Lire_Point (page_dessins,x2,(y1 + cpt));
        vt [1][cpt] = couleur;
    }
}
void Restaurer_Selection (short x1,short y1,short x2,short y2)
{
    short cpt;
    OCTET couleur;
    for (cpt = 0;
            cpt <= (x2-x1);
            cpt ++)
    {
        couleur = ht [0][cpt];
        Afficher_Point (page_dessins,(x1 + cpt),y1,couleur);
        couleur = ht [1][cpt];
        Afficher_Point (page_dessins,(x1 + cpt),y2,couleur);
    }
    for (cpt = 0;
            cpt <= (y2-y1);
            cpt ++)
    {
        couleur = vt [0][cpt];
        Afficher_Point (page_dessins,x1,(y1 + cpt),couleur);
        couleur = vt [1][cpt];
        Afficher_Point (page_dessins,x2,(y1 + cpt),couleur);
    }
}
OCTET Calculer_Afficher_Dessin (void)
{
    OCTET x,y;
    OCTET numero_dessin;
    OCTET element_lg;
    OCTET element_ht;
    numero_dessin = Lire_Nbdessin ();
    if (numero_dessin >= NB_DESSIN_TABLEAU) return (FAUX);
    do
    {
        if (X_Case () != 0)
            Afficher_Nombre (page_panneau,BOB_CHIFFRE,2,X_Case(),310,13,MASK_OFF);
        if (Y_Case () != 0)
            Afficher_Nombre (page_panneau,BOB_CHIFFRE,2,Y_Case(),310,20,MASK_OFF);
    }
    while (Clic_Souris () != CLIC_GAUCHE);
    do
    {
        x = X_Case ();
        y = Y_Case ();
        if ( (x == 0) | (y == 0) )
        {
            Ecrire_Panneau_Demande (0);
            return (FAUX);
        }
    }
    while (Clic_Souris () == CLIC_GAUCHE);
    element_lg = selection_lg;
    element_ht = selection_ht;
    Calculer_Surface (x,y,&element_lg,&element_ht);
    if (element_lg == 0)
    {
        Ecrire_Panneau_Demande (0);
        return (VRAI);
    }
    numero_dessin = Lire_Nbdessin ();
    Ecrire_Xfcdessin (numero_dessin,selection_x);
    Ecrire_Yfcdessin (numero_dessin,selection_y);
    Ecrire_Xdessin (numero_dessin,x);
    Ecrire_Ydessin (numero_dessin,y);
    Ecrire_Lgdessin (numero_dessin,element_lg);
    Ecrire_Htdessin (numero_dessin,element_ht);
    Ecrire_Nbdessin (numero_dessin+1);
    Envoyer_Elements_buffer (numero_dessin,0);
    Afficher_Nombre (page_panneau,BOB_CHIFFRE,2,numero_dessin+1,310,139,MASK_OFF);
    Souris (OFF);
    Afficher_Dessin (-2,20,page_panneau,numero_dessin);
    Souris (ON);
    Ecrire_Panneau_Demande (0);
    return (VRAI);
}
OCTET Calculer_Effacer_Dessin (void)
{
    OCTET cpt;
    OCTET x,y;
    OCTET x1buffer;
    OCTET y1buffer;
    OCTET x2buffer;
    OCTET y2buffer;
    OCTET lgbuffer;
    OCTET htbuffer;
    OCTET numero_dessin;
    numero_dessin = Lire_Nbdessin ();
    if (numero_dessin <= 0) return (FAUX);
    do
    {
        if (X_Case () != 0)
            Afficher_Nombre (page_panneau,BOB_CHIFFRE,2,X_Case(),310,13,MASK_OFF);
        if (Y_Case () != 0)
            Afficher_Nombre (page_panneau,BOB_CHIFFRE,2,Y_Case(),310,20,MASK_OFF);
    }
    while (Clic_Souris () != CLIC_GAUCHE);
    do
    {
        x = X_Case ();
        y = Y_Case ();
        if ( (x == 0) | (y == 0) )
        {
            Ecrire_Panneau_Demande (0);
            return (FAUX);
        }
    }
    while (Clic_Souris () == CLIC_GAUCHE);
    for (cpt = 0;
            cpt < numero_dessin;
            cpt ++)
    {
        lgbuffer = Lire_Lgdessin (cpt);
        htbuffer = Lire_Htdessin (cpt);
        x1buffer = Lire_Xdessin (cpt);
        y1buffer = Lire_Ydessin (cpt);
        x2buffer = x1buffer + (lgbuffer - 1);
        y2buffer = y1buffer + (htbuffer - 1);
        if ( (x >= x1buffer) & (x <= x2buffer) &
                (y >= y1buffer) & (y <= y2buffer) )
        {
            Envoyer_Elements_buffer (cpt,
                                     OBST_DESSIN);
            Souris (OFF);
            Afficher_Obstacles_Dessins (x1buffer,
                                        y1buffer,
                                        x1buffer + (lgbuffer - 1),
                                        y1buffer + (htbuffer - 1) );
            Souris (ON);
            Annuler_Dessin_Structure (cpt);
            Afficher_Nombre (page_panneau,BOB_CHIFFRE,2,
                             numero_dessin-1,310,139,
                             MASK_OFF);
            break;
        }
    }
    Ecrire_Panneau_Demande (0);
    return (VRAI);
}
void Envoyer_Elements_buffer (OCTET num_dessin,OCTET element)
{
    OCTET cptx;
    OCTET cpty;
    OCTET xbuffer;
    OCTET ybuffer;
    OCTET lgbuffer;
    OCTET htbuffer;
    xbuffer = Lire_Xdessin (num_dessin);
    ybuffer = Lire_Ydessin (num_dessin);
    lgbuffer = Lire_Lgdessin (num_dessin);
    htbuffer = Lire_Htdessin (num_dessin);
    for (cpty = 0;
            cpty < htbuffer;
            cpty ++)
    {
        for (cptx = 0;
                cptx < lgbuffer;
                cptx ++)
        {
            Ecrire_Case (buftab1_sans_cadre,
                         element,
                         xbuffer + cptx,
                         ybuffer + cpty);
        }
    }
}
void Effacer_Tous_Dessin (void)
{
    OCTET nombre_dessin;
    OCTET cpt_dessin;
    OCTET xdessin;
    OCTET ydessin;
    OCTET lgdessin;
    OCTET htdessin;
    OCTET reponse;
    Afficher_Boite_Message (page_panneau,INFO08);
    reponse = RIEN;
    do
    {
        if ( Test_Option (INFO08_OUI) == ON )
        {
            reponse = OUI;
            Option (OFF,page_panneau,INFO08_OUI);
            WAIT_NO_CLIC;
            Option (ON,page_panneau,INFO08_OUI);
        }
        if ( Test_Option (INFO08_NON) == ON )
        {
            reponse = NON;
            Option (OFF,page_panneau,INFO08_NON);
            WAIT_NO_CLIC;
            Option (ON,page_panneau,INFO08_NON);
        }
    }
    while (reponse == RIEN);
    Effacer_Boite (page_panneau);
    if (reponse == OUI)
    {
        nombre_dessin = Lire_Nbdessin ();
        for (cpt_dessin = 0;
                cpt_dessin < nombre_dessin;
                cpt_dessin ++)
        {
            Envoyer_Elements_buffer (cpt_dessin,
                                     OBST_DESSIN);
            xdessin = Lire_Xdessin (cpt_dessin);
            ydessin = Lire_Ydessin (cpt_dessin);
            lgdessin = Lire_Lgdessin (cpt_dessin);
            htdessin = Lire_Htdessin (cpt_dessin);
            Souris (OFF);
            Afficher_Obstacles_Dessins (xdessin,
                                        ydessin,
                                        xdessin + (lgdessin - 1),
                                        ydessin + (htdessin - 1));
            Souris (ON);
        }
        Ecrire_Nbdessin (0);
        Afficher_Nombre (page_panneau,BOB_CHIFFRE,2,0,310,139,MASK_OFF);
    }
    Ecrire_Panneau_Demande (0);
}
OCTET Calculer_Taille_Dessin (void)
{
    OCTET x,y;
    OCTET element_lg;
    OCTET element_ht;
    do
    {
        if (X_Case () != 0)
            Afficher_Nombre (page_panneau,BOB_CHIFFRE,2,X_Case(),310,13,MASK_OFF);
        if (Y_Case () != 0)
            Afficher_Nombre (page_panneau,BOB_CHIFFRE,2,Y_Case(),310,20,MASK_OFF);
    }
    while (Clic_Souris () != CLIC_GAUCHE);
    do
    {
        x = X_Case ();
        y = Y_Case ();
        if ( (x == 0) | (y == 0) )
        {
            Ecrire_Panneau_Demande (0);
            return (FAUX);
        }
    }
    while (Clic_Souris () == CLIC_GAUCHE);
    element_lg = 43;
    element_ht = 33;
    Calculer_Surface (x,y,&element_lg,&element_ht);
    Afficher_Nombre (page_panneau,BOB_CHIFFRE,2,element_lg,310,185,MASK_OFF);
    Afficher_Nombre (page_panneau,BOB_CHIFFRE,2,element_ht,310,198,MASK_OFF);
    Ecrire_Panneau_Demande (0);
    return (VRAI);
}
