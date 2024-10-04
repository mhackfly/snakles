#include <DOS.H>
#include "SOUREDIT/EDITSOUR.H"
#include "SOUREDIT/EDITGRAP.H"
#include "SOUREDIT/EDITPANN.H"
#include "SOUREDIT/EDITTABL.H"
short tableau_encours;
OCTET buftab_avec_cadre [BUFSIZE_AVEC_CADRE];
OCTET buftab1_sans_cadre [BUFSIZE_SANS_CADRE];
OCTET buftab2_sans_cadre [BUFSIZE_SANS_CADRE];
OCTET buffer_boite_info [LG_INFO * HT_INFO];
char incx [5] = {0,-1, 1, 0, 0};
char incy [5] = {0, 0, 0,-1, 1};
OCTET direction [16] = {1,3,2,4,1,3,2,4,1,3,2,4,1,3,2,4};
OCTET couleur [16] = {0,0,0,0,1,1,1,1,2,2,2,2,3,3,3,3};
OCTET tete [16] = {6,7,8,9,15,16,17,18,24,25,26,27,33,34,35,36};
OCTET corps [16] = {1,1,1,1,10,10,10,10,19,19,19,19,28,28,28,28};
OCTET queue [16] = {2,3,4,5,11,12,13,14,20,21,22,23,29,30,31,32};
short Lire_Tableau_Encours (void)
{
    return (tableau_encours);
}
void Ecrire_Tableau_Encours (short a)
{
    tableau_encours = a;
}
OCTET X_Case (void)
{
    OCTET rep;
    rep = 0;
    if (X_Croix () != -1) rep = ( X_Croix () / 7 ) + 1;
    return (rep);
}
OCTET Y_Case (void)
{
    OCTET rep;
    rep = 0;
    if (Y_Croix () != -1) rep = ( Y_Croix () / 11 ) + 1;
    return (rep);
}
void Selection_Pastille (OCTET num_past,OCTET etat)
{
    OCTET couleur;
    short x,y;
    short cpt_point;
    couleur = (etat == ON) ? SELECTION_PASTILLE_ON : SELECTION_PASTILLE_OFF;
    x = ( ( num_past - 1 ) * 8 ) + 3;
    y = 14;
    Souris (OFF);
    for (cpt_point = 0;
            cpt_point < 9;
            cpt_point ++)
    {
        Afficher_Point (Lire_Page (),x + cpt_point, y,couleur);
        Afficher_Point (Lire_Page (),x + cpt_point,y+12,couleur);
    }
    for (cpt_point = 0;
            cpt_point < 12;
            cpt_point ++)
    {
        Afficher_Point (Lire_Page (),x,14 + cpt_point,couleur);
        Afficher_Point (Lire_Page (),x+8,14 + cpt_point,couleur);
    }
    Souris (ON);
}
OCTET Lire_Case (OCTET *ad_buffer,OCTET x,OCTET y)
{
    short indice_buffer;
    OCTET val;
    indice_buffer = ( ((y - 1) * 43) + ( x - 1) );
    val = *(ad_buffer + indice_buffer);
    return (val);
}
void Ecrire_Case (OCTET *ad_buffer,OCTET val,OCTET x,OCTET y)
{
    short indice_buffer;
    if ( (x != 0) & (y != 0) )
    {
        indice_buffer = ( ((y - 1) * 43) + (x - 1) );
        *(ad_buffer + indice_buffer) = val;
    }
}
void Afficher_Case (OCTET deb_bob,OCTET val,OCTET x,OCTET y)
{
    short x_bob;
    short y_bob;
    if ( (x != 0) & (y != 0) )
    {
        x_bob = X_TAB_PASTILLES_SERPENTS + ( (x - 1) * LG_BOB );
        y_bob = Y_TAB_PASTILLES_SERPENTS + ( (y - 1) * HT_BOB );
        if (val != 0)
        {
            Afficher_Bob (Lire_Page (),FOND_1,x_bob,y_bob,MASK_ON);
            Afficher_Bob (Lire_Page (),val + (deb_bob - 1),x_bob,y_bob,MASK_ON);
        }
        else
            Afficher_Bob (Lire_Page (),FOND_1,x_bob,y_bob,MASK_ON);
    }
}
void Afficher_Cases (OCTET *ad_buffer,OCTET deb_bob,
                     OCTET x1,OCTET y1,OCTET x2,OCTET y2)
{
    OCTET cpt_x;
    OCTET cpt_y;
    short x_bob;
    short y_bob;
    OCTET pastille;
    Souris (OFF);
    for (cpt_y = y1;
            cpt_y <= y2;
            cpt_y ++)
    {
        for (cpt_x = x1;
                cpt_x <= x2;
                cpt_x ++)
        {
            pastille = Lire_Case (ad_buffer,cpt_x,cpt_y);
            x_bob = X_TAB_PASTILLES_SERPENTS + ( (cpt_x - 1) * LG_BOB );
            y_bob = Y_TAB_PASTILLES_SERPENTS + ( (cpt_y - 1) * HT_BOB );
            if (pastille != 0)
            {
                Afficher_Bob (Lire_Page (),FOND_1,x_bob,y_bob,MASK_ON);
                Afficher_Bob (Lire_Page (),deb_bob + pastille,
                              x_bob,y_bob,MASK_ON);
            }
            else
                Afficher_Bob (Lire_Page (),FOND_1,x_bob,y_bob,MASK_ON);
        }
    }
    Souris (ON);
}
void Convertir_Structure_Buffer (void)
{
    short cpt_buffer;
    OCTET cpt_serpent;
    for (cpt_buffer = 0;
            cpt_buffer < BUFSIZE_SANS_CADRE;
            cpt_buffer ++)
        buftab2_sans_cadre [cpt_buffer] = 0;
    if (Lire_Lgnibble () != 0)
        Afficher_Serpent_Buffer ( BLANC,
                                  Lire_Drnibble (),
                                  Lire_Lgnibble (),
                                  Lire_Xnibble (),
                                  Lire_Ynibble ());
    for (cpt_serpent = 0;
            cpt_serpent < Lire_Nbnibble_X ();
            cpt_serpent ++)
        Afficher_Serpent_Buffer ( Lire_Clnibble_X (cpt_serpent),
                                  Lire_Drnibble_X (cpt_serpent),
                                  Lire_Lgnibble_X (cpt_serpent),
                                  Lire_Xnibble_X (cpt_serpent),
                                  Lire_Ynibble_X (cpt_serpent));
}
void Afficher_Serpent_Buffer (OCTET couleur,OCTET sens,OCTET longueur,
                              OCTET x,OCTET y)
{
    OCTET incdir [5] = {0,0,2,1,3};
    OCTET indice;
    OCTET cpt_longueur;
    indice = (couleur * 4) + incdir [sens];
    Ecrire_Case (buftab2_sans_cadre,tete [indice],x,y);
    x += incx [ direction [ indice ] ];
    y += incy [ direction [ indice ] ];
    for (cpt_longueur = 0;
            cpt_longueur < longueur;
            cpt_longueur ++)
    {
        Ecrire_Case (buftab2_sans_cadre,corps [indice],x,y);
        x += incx [ direction [ indice ] ];
        y += incy [ direction [ indice ] ];
    }
    Ecrire_Case (buftab2_sans_cadre,queue [indice],x,y);
}
void Rechercher_Conflit_Serpents_Bord (void)
{
    OCTET element;
    OCTET cptx,cpty;
    for (cpty = 1;
            cpty <= 33;
            cpty ++)
    {
        for (cptx = 1;
                cptx <= 43;
                cptx ++)
        {
            if ( Lire_Case ( buftab2_sans_cadre,cptx,cpty ) != 0)
            {
                element = Lire_Case ( buftab1_sans_cadre,cptx,cpty );
                if ( (element >= 1) & (element <= 6) )
                    Ecrire_Case (buftab2_sans_cadre,0,cptx,cpty);
            }
        }
    }
}
OCTET Convertir_Buffer_Structure (void)
{
    OCTET indice;
    OCTET cptx,cpty;
    OCTET valeur_case;
    char resultat;
    OCTET cpt_blanc;
    OCTET cpt_rvb;
    OCTET cpt;
    OCTET buffer_x [NB_SERPENT_RVB];
    OCTET buffer_y [NB_SERPENT_RVB];
    OCTET buffer_vitesse [NB_SERPENT_RVB];
    short buffer_tempo [NB_SERPENT_RVB];
    cpt_blanc = 0;
    cpt_rvb = 0;
    for (cpt = 0;
            cpt < NB_SERPENT_RVB;
            cpt ++)
    {
        buffer_x [cpt] = 0;
        buffer_y [cpt] = 0;
        buffer_vitesse [cpt] = 0;
        buffer_tempo [cpt] = 0;
    }
    for (cpt = 0;
            cpt < Lire_Nbnibble_X ();
            cpt ++)
    {
        buffer_x [cpt] = Lire_Xnibble_X (cpt);
        buffer_y [cpt] = Lire_Ynibble_X (cpt);
        buffer_vitesse [cpt] = Lire_Vtnibble_X (cpt);
        buffer_tempo [cpt] = Lire_Tpnibble_X (cpt);
    }
    Ecrire_Lgnibble ( 0 );
    Ecrire_Drnibble ( 0 );
    Ecrire_Xnibble ( 0 );
    Ecrire_Ynibble ( 0 );
    for (cpt = 0;
            cpt < NB_SERPENT_RVB;
            cpt ++)
    {
        Ecrire_Lgnibble_X ( cpt, 0 );
        Ecrire_Drnibble_X ( cpt, 0 );
        Ecrire_Tpnibble_X ( cpt,5000 );
        Ecrire_Vtnibble_X ( cpt, 2 );
        Ecrire_Clnibble_X ( cpt, 0 );
        Ecrire_Xnibble_X ( cpt, 0 );
        Ecrire_Ynibble_X ( cpt, 0 );
    }
    for (cpty = 1;
            cpty <= 33;
            cpty ++)
    {
        for (cptx = 1;
                cptx <= 43;
                cptx ++)
        {
            valeur_case = Lire_Case (buftab2_sans_cadre,cptx,cpty);
            for (indice = 0;
                    indice <= 15;
                    indice ++)
            {
                if (valeur_case == tete [ indice ])
                {
                    resultat = Verifier_Serpent_Buffer (indice,cptx,cpty);
                    if ( resultat != INCORRECT )
                    {
                        if ( (couleur [indice] == BLANC) & (cpt_blanc == 0) )
                        {
                            Ecrire_Lgnibble ( resultat );
                            Ecrire_Drnibble ( direction [indice] );
                            Ecrire_Xnibble ( cptx );
                            Ecrire_Ynibble ( cpty );
                            cpt_blanc = 1;
                        }
                        if ( (couleur [indice] != BLANC) & (cpt_rvb < NB_SERPENT_RVB) )
                        {
                            Ecrire_Lgnibble_X ( cpt_rvb,resultat );
                            Ecrire_Drnibble_X ( cpt_rvb,direction [indice] );
                            Ecrire_Clnibble_X ( cpt_rvb,couleur [indice] );
                            Ecrire_Xnibble_X ( cpt_rvb,cptx );
                            Ecrire_Ynibble_X ( cpt_rvb,cpty );
                            cpt_rvb ++;
                        }
                    }
                }
            }
        }
    }
    Ecrire_Nbnibble_X ( cpt_rvb );
    for (cpt = 0;
            cpt < NB_SERPENT_RVB;
            cpt ++)
    {
        for (cpt_rvb = 0;
                cpt_rvb < Lire_Nbnibble_X ();
                cpt_rvb ++)
        {
            if ( Lire_Xnibble_X (cpt_rvb) == buffer_x [cpt] )
            {
                if ( Lire_Ynibble_X (cpt_rvb) == buffer_y [cpt] )
                {
                    Ecrire_Vtnibble_X ( cpt_rvb,buffer_vitesse [cpt] );
                    Ecrire_Tpnibble_X ( cpt_rvb,buffer_tempo [cpt] );
                }
            }
        }
    }
    return ( cpt_blanc + Lire_Nbnibble_X () );
}
char Verifier_Serpent_Buffer (OCTET indice,OCTET x,OCTET y)
{
    char longueur;
    longueur = 0;
    do
    {
        x += incx [ direction [ indice ] ];
        y += incy [ direction [ indice ] ];
        if ( (x<1) | (x>43) | (y<1) | (y>33) ) return (INCORRECT);
        longueur ++;
    }
    while ( Lire_Case (buftab2_sans_cadre,x,y) == corps [ indice ] );
    if ( Lire_Case (buftab2_sans_cadre,x,y) != queue [indice] ) return (INCORRECT);
    longueur --;
    if ( longueur < 1 ) return (INCORRECT);
    if ( longueur > LG_SERPENTS ) return (INCORRECT);
    return (longueur);
}
void Afficher_Dessin (short x,short y,OCTET page_video,OCTET num_dessin)
{
    short xecran;
    short yecran;
    short xfichier;
    short yfichier;
    short lgfichier;
    short htfichier;
    xecran = x + (short)(Lire_Xdessin (num_dessin) * LG_BOB);
    yecran = y + (short)(Lire_Ydessin (num_dessin) * HT_BOB);
    xfichier = Lire_Xfcdessin (num_dessin);
    yfichier = Lire_Yfcdessin (num_dessin);
    lgfichier = (short)( (Lire_Lgdessin (num_dessin) * LG_BOB) - 1);
    htfichier = (short)( (Lire_Htdessin (num_dessin) * HT_BOB) - 1);
    Lire_Image_Pcx ("SPRFILES/DESSINS",
                    page_video,
                    xecran,yecran,
                    MASK_OFF,
                    xfichier,yfichier,
                    lgfichier,htfichier);
}
void Calculer_Surface (OCTET x,OCTET y,OCTET *lg,OCTET *ht)
{
    OCTET cptlg;
    OCTET cptht;
    OCTET element;
    OCTET element_lg;
    OCTET element_ht;
    for (cptlg = 0;
            cptlg < *lg;
            cptlg ++)
    {
        if (x+cptlg > X_MAX-2) break;
        element = Lire_Case (buftab1_sans_cadre,x+cptlg,y);
        if (element != OBST_DESSIN) break;
    }
    if (cptlg == 0)
    {
        *lg = 0;
        *ht = 0;
        return;
    }
    element_lg = cptlg;
    for (cptht = 0;
            cptht < *ht;
            cptht ++)
    {
        for (cptlg = 0;
                cptlg < element_lg;
                cptlg ++)
        {
            element = Lire_Case (buftab1_sans_cadre,x+cptlg,y+cptht);
            if (element != OBST_DESSIN) break;
        }
        if (element != OBST_DESSIN) break;
        if (y+cptht > Y_MAX-2) break;
    }
    element_ht = cptht;
    *lg = element_lg;
    *ht = element_ht;
}
void Annuler_Dessin_Structure (OCTET num_dessin_a_annuler)
{
    OCTET cpt;
    short xfichier;
    short yfichier;
    OCTET xbuffer;
    OCTET ybuffer;
    OCTET lgbuffer;
    OCTET htbuffer;
    OCTET nombre_dessin;
    nombre_dessin = Lire_Nbdessin ();
    if (num_dessin_a_annuler != (nombre_dessin - 1))
    {
        for (cpt = num_dessin_a_annuler;
                cpt < (nombre_dessin - 1);
                cpt ++)
        {
            xfichier = Lire_Xfcdessin (cpt + 1);
            yfichier = Lire_Yfcdessin (cpt + 1);
            xbuffer = Lire_Xdessin (cpt + 1);
            ybuffer = Lire_Ydessin (cpt + 1);
            lgbuffer = Lire_Lgdessin (cpt + 1);
            htbuffer = Lire_Htdessin (cpt + 1);
            Ecrire_Xfcdessin (cpt,xfichier);
            Ecrire_Yfcdessin (cpt,yfichier);
            Ecrire_Xdessin (cpt,xbuffer );
            Ecrire_Ydessin (cpt,ybuffer );
            Ecrire_Lgdessin (cpt,lgbuffer);
            Ecrire_Htdessin (cpt,htbuffer);
        }
    }
    Ecrire_Nbdessin (nombre_dessin - 1);
}
void Verifier_Corriger_Dessin (void)
{
    OCTET cpt_dessin;
    OCTET nb_dessin;
    OCTET xdessin;
    OCTET ydessin;
    OCTET lgdessin;
    OCTET htdessin;
    OCTET lgelement;
    OCTET htelement;
    short xf [NB_DESSIN_TABLEAU];
    short yf [NB_DESSIN_TABLEAU];
    OCTET xd [NB_DESSIN_TABLEAU];
    OCTET yd [NB_DESSIN_TABLEAU];
    OCTET lg [NB_DESSIN_TABLEAU];
    OCTET ht [NB_DESSIN_TABLEAU];
    OCTET cpt_buf;
    cpt_buf = 0;
    nb_dessin = Lire_Nbdessin ();
    for (cpt_dessin = 0;
            cpt_dessin < nb_dessin;
            cpt_dessin ++)
    {
        xdessin = Lire_Xdessin (cpt_dessin);
        ydessin = Lire_Ydessin (cpt_dessin);
        lgdessin = Lire_Lgdessin (cpt_dessin);
        htdessin = Lire_Htdessin (cpt_dessin);
        lgelement = lgdessin;
        htelement = htdessin;
        Calculer_Surface (xdessin,ydessin,&lgelement,&htelement);
        if ( (lgelement >= lgdessin) & (htelement >= htdessin) )
        {
            xf [cpt_buf] = Lire_Xfcdessin (cpt_dessin);
            yf [cpt_buf] = Lire_Yfcdessin (cpt_dessin);
            xd [cpt_buf] = Lire_Xdessin (cpt_dessin);
            yd [cpt_buf] = Lire_Ydessin (cpt_dessin);
            lg [cpt_buf] = Lire_Lgdessin (cpt_dessin);
            ht [cpt_buf] = Lire_Htdessin (cpt_dessin);
            cpt_buf ++;
        }
    }
    for (cpt_dessin = 0;
            cpt_dessin < cpt_buf;
            cpt_dessin ++)
    {
        Ecrire_Xfcdessin (cpt_dessin,xf [cpt_dessin]);
        Ecrire_Yfcdessin (cpt_dessin,yf [cpt_dessin]);
        Ecrire_Xdessin (cpt_dessin,xd [cpt_dessin]);
        Ecrire_Ydessin (cpt_dessin,yd [cpt_dessin]);
        Ecrire_Lgdessin (cpt_dessin,lg [cpt_dessin]);
        Ecrire_Htdessin (cpt_dessin,ht [cpt_dessin]);
    }
    Ecrire_Nbdessin (cpt_buf);
}
short Conv_Coord_Num (OCTET element,short x,short y)
{
    short rep;
    short numcol;
    short numlig;
    if (element == BORDURES)
    {
        numlig = (y - Y_MIN_BORDURES) / Y_ECART_BORDURES;
        numcol = (x - X_MIN_BORDURES) / X_ECART_BORDURES;
        rep = (numlig * X_NB_BORDURES) + numcol;
    }
    if (element == FONDS)
    {
        numlig = (y - Y_MIN_FONDS) / Y_ECART_FONDS;
        numcol = (x - X_MIN_FONDS) / X_ECART_FONDS;
        rep = (numlig * X_NB_FONDS) + numcol;
    }
    return (rep+1);
}
void Conv_Num_Coord (OCTET element,short numero,short *x,short *y)
{
    short numlig;
    short numcol;
    numero --;
    if (element == BORDURES)
    {
        numlig = numero / X_NB_BORDURES;
        numcol = numero - (numlig * X_NB_BORDURES);
        *y = Y_MIN_BORDURES + (numlig * Y_ECART_BORDURES);
        *x = X_MIN_BORDURES + (numcol * X_ECART_BORDURES);
    }
    if (element == FONDS)
    {
        numlig = numero / X_NB_FONDS;
        numcol = numero - (numlig * X_NB_FONDS);
        *y = Y_MIN_FONDS + (numlig * Y_ECART_FONDS);
        *x = X_MIN_FONDS + (numcol * X_ECART_FONDS);
    }
}
void Option (OCTET etat,OCTET page,short x1,short y1,short x2,short y2)
{
    Souris (OFF);
    if (etat == ON)
    {
        Tracer_Droite (page,x1,y1,x1,y1 + (y2-y1),RELIEF_CLAIR);
        Tracer_Droite (page,x1,y1,x1 + (x2-x1),y1,RELIEF_CLAIR);
        Tracer_Droite (page,x2,y2,x2 - ((x2-x1)-1),y2,RELIEF_FONCE);
        Tracer_Droite (page,x2,y2,x2,y2 - ((y2-y1)-1),RELIEF_FONCE);
    }
    else
    {
        Tracer_Droite (page,x1,y1,x1,y1 + ((y2-y1)-1),RELIEF_FONCE);
        Tracer_Droite (page,x1,y1,x1 + ((x2-x1)-1),y1,RELIEF_FONCE);
        Tracer_Droite (page,x2,y2,x2 - (x2-x1),y2,RELIEF_CLAIR);
        Tracer_Droite (page,x2,y2,x2,y2 - (y2-y1),RELIEF_CLAIR);
    }
    Souris (ON);
}
OCTET Test_Option (short xinf,short yinf,short xsup,short ysup)
{
    OCTET sortie;
    sortie = OFF;
    if ( Test_Clic_Zone (X_Fleche (),Y_Fleche (),xinf,yinf,xsup,ysup) == ON )
        sortie = ON;
    return (sortie);
}
void Nombre_Option (short xn,short yn,OCTET page,OCTET lgnb,short valeur)
{
    Afficher_Nombre (page,BOB_CHIFFRE_2,lgnb,valeur,xn,yn,MASK_OFF);
}
short Traiter_Fleche (OCTET page,short incdec,
                      short val,short valmin,short valmax,
                      short x1,short y1,short x2,short y2,
                      short xval,short yval,OCTET lgnb)
{
    OCTET sortie;
    short tempo;
    float cpt_tempo;
    sortie = NON;
    tempo = 0;
    cpt_tempo = 0;
    Option (OFF,page,x1,y1,x2,y2);
    do
    {
        if (tempo <= 500) tempo = ( cpt_tempo++ * .5 ) + 1;
        val = val + (incdec * tempo);
        if ( (val >= valmin) & (val <= valmax) )
        {
            Nombre_Option (xval,yval,page,lgnb,val);
        }
        else
        {
            val = (incdec == 1) ? valmax : valmin;
            Nombre_Option (xval,yval,page,lgnb,val);
        }
        Pause (80);
        if ( Clic_Souris () != CLIC_GAUCHE) sortie = OUI;
        if ( Test_Option (x1,y1,x2,y2) == OFF ) sortie = OUI;
    }
    while (sortie == NON);
    Option (ON,page,x1,y1,x2,y2);
    return (val);
}
void Changer_Page (OCTET page)
{
    disable ();
    Restaurer_Fond ();
    Afficher_Page (page);
    Sauver_Fond ();
    Afficher_Souris ();
    enable ();
}
short Totaliser_Pastilles (OCTET element)
{
    OCTET cpt_x;
    OCTET cpt_y;
    OCTET pastille;
    short cptpastille;
    cptpastille = 0;
    for (cpt_y = 1;
            cpt_y <= 33;
            cpt_y ++)
    {
        for (cpt_x = 1;
                cpt_x <= 43;
                cpt_x ++)
        {
            pastille = Lire_Case (buftab1_sans_cadre,cpt_x,cpt_y);
            if (pastille == element) cptpastille ++;
        }
    }
    return (cptpastille);
}
void Afficher_Cadre (OCTET page)
{
    char cpt;
    for (cpt = 0;
            cpt <= 42;
            cpt ++)
    {
        Afficher_Point (page,5 + (cpt * 7) + 0,30,249);
        Tracer_Droite (page,5 + (cpt * 7) + 1,30,5 + (cpt * 7) + 5,30,9);
        Afficher_Point (page,5 + (cpt * 7) + 6,30,249);
        Afficher_Point (page,5 + (cpt * 7) + 0,394,249);
        Tracer_Droite (page,5 + (cpt * 7) + 1,394,5 + (cpt * 7) + 5,394,9);
        Afficher_Point (page,5 + (cpt * 7) + 6,394,249);
    }
    for (cpt = 0;
            cpt <= 32;
            cpt ++)
    {
        Afficher_Point (page,4,31 + (cpt * 11) + 0,249);
        Tracer_Droite (page,4,31 + (cpt * 11) + 1,4,31 + (cpt * 11) + 9,9);
        Afficher_Point (page,4,31 + (cpt * 11) + 10,249);
        Afficher_Point (page,306,31 + (cpt * 11) + 0,249);
        Tracer_Droite (page,306,31 + (cpt * 11) + 1,306,31 + (cpt * 11) + 9,9);
        Afficher_Point (page,306,31 + (cpt * 11) + 10,249);
    }
    Tracer_Droite (page,5 + (21 * 7) + 1, 30,5 + (21 * 7) + 5, 30,0);
    Tracer_Droite (page,5 + (21 * 7) + 1,394,5 + (21 * 7) + 5,394,0);
    Tracer_Droite (page, 4,31 + (16 * 11) + 1, 4,31 + (16 * 11) + 9,0);
    Tracer_Droite (page,306,31 + (16 * 11) + 1,306,31 + (16 * 11) + 9,0);
}
