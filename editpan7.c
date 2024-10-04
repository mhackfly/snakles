#include "SOUREDIT/EDITSOUR.H"
#include "SOUREDIT/EDITGRAP.H"
#include "SOUREDIT/EDITPANN.H"
#include "SOUREDIT/EDITTABL.H"
#include "SOUREDIT/EDITONGL.H"
void Afficher_Tableau (OCTET);
void Afficher_Snakle (OCTET,OCTET,OCTET,OCTET,OCTET,OCTET);
extern OCTET buftab_avec_cadre [BUFSIZE_AVEC_CADRE];
extern OCTET buftab1_sans_cadre [BUFSIZE_SANS_CADRE];
extern OCTET buftab2_sans_cadre [BUFSIZE_SANS_CADRE];
OCTET element_snakles [13] = {0,6,0,2,8,0,4,7,1,3,9,1,5};
char sk_incx [5] = {0,-1,+1, 0, 0};
char sk_incy [5] = {0, 0, 0,-1,+1};
void Panneau_7 (void)
{
    OCTET lg_serpent;
    OCTET mt_serpent;
    OCTET nb_serpent;
    OCTET cpt_dessin;
    OCTET nombre_dessin;
    OCTET cpt;
    OCTET page;
    Lire_Tableau ( Lire_Tableau_Encours() );
    Lire_Buftab_Avec_Cadre (buftab_avec_cadre);
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
    Afficher_Onglet (page,ONGLET7);
    Afficher_Tableau (page);
    lg_serpent = Lire_Lgnibble ();
    mt_serpent = Lire_Mtnibble ();
    if ( lg_serpent > 0)
    {
        if (mt_serpent == ON)
            Afficher_Snakle (page,
                             Lire_Xnibble (),
                             Lire_Ynibble (),
                             Lire_Drnibble (),
                             Lire_Lgnibble (),
                             CL_BLANC);
        else
            Afficher_Snakle (page,
                             Lire_Xnibble (),
                             Lire_Ynibble (),
                             Lire_Drnibble (),
                             Lire_Lgnibble (),
                             CL_ORANGE);
    }
    nb_serpent = Lire_Nbnibble_X ();
    for (cpt = 0;
            cpt < nb_serpent;
            cpt++)
        Afficher_Snakle (page,
                         Lire_Xnibble_X (cpt),
                         Lire_Ynibble_X (cpt),
                         Lire_Drnibble_X (cpt),
                         Lire_Lgnibble_X (cpt),
                         Lire_Clnibble_X (cpt));
    nombre_dessin = Lire_Nbdessin ();
    for (cpt_dessin = 0;
            cpt_dessin < nombre_dessin;
            cpt_dessin ++)
        Afficher_Dessin (X_TAB_APERCU,
                         Y_TAB_APERCU,
                         page,cpt_dessin);
    Changer_Page (page);
    do
    {
    }
    while (Lire_Panneau_Demande () == 0);
    Sauver_Tableau (Lire_Tableau_Encours ());
}
void Afficher_Tableau (OCTET pg)
{
    OCTET coddr;
    OCTET codga;
    OCTET codha;
    OCTET codba;
    OCTET resul;
    OCTET y,x;
    OCTET code;
    short cptcode = 0;
    for (y=Y_MIN; y<Y_MAX; y++)
    {
        for (x=X_MIN; x<X_MAX; x++)
        {
            Afficher_Bob (pg,
                          BOB_FOND,
                          X_TAB_APERCU + (x * LG_BOB),
                          Y_TAB_APERCU + (y * HT_BOB),
                          MASK_OFF);
            code = buftab_avec_cadre [cptcode];
            if (code == OBST_BORDURE)
            {
                coddr = ( (cptcode+1) >= (X_MAX*(y+1)) ) ? 0 :buftab_avec_cadre [cptcode+1];
                codba = ( (cptcode+X_MAX) > (X_MAX*Y_MAX-1) ) ? 0 :buftab_avec_cadre [cptcode+X_MAX];
                codga = ( (cptcode-1) < (X_MAX*y) ) ? 0 :buftab_avec_cadre [cptcode-1];
                codha = ( (cptcode-X_MAX) < 0 ) ? 0 :buftab_avec_cadre [cptcode-X_MAX];
                resul=0;
                resul += (coddr == OBST_BORDURE) ? 1 : 0;
                resul += (codba == OBST_BORDURE) ? 2 : 0;
                resul += (codga == OBST_BORDURE) ? 4 : 0;
                resul += (codha == OBST_BORDURE) ? 8 : 0;
                Afficher_Bob (pg,
                              BOB_BORDURE+resul,
                              X_TAB_APERCU + (x * LG_BOB),
                              Y_TAB_APERCU + (y * HT_BOB),
                              MASK_ON);
            }
            else
            {
                if (code > OBST_BORDURE)
                {
                    Afficher_Bob (pg,
                                  (BOB_PASTILLE - 1) + code,
                                  X_TAB_APERCU + (x * LG_BOB),
                                  Y_TAB_APERCU + (y * HT_BOB),
                                  MASK_ON);
                }
            }
            cptcode++;
        }
    }
}
void Afficher_Snakle (OCTET page,OCTET x,OCTET y,
                      OCTET sens,OCTET lg,OCTET coul)
{
    short xec,yec;
    OCTET cpt_long;
    xec = (x * SNAKLES_LONG) + X_TAB_APERCU;
    yec = (y * SNAKLES_HAUT) + Y_TAB_APERCU;
    Afficher_Bob (page,BOB(sens,TETE,coul),xec,yec,MASK_ON);
    for (cpt_long = 0;
            cpt_long < lg;
            cpt_long ++)
    {
        xec += sk_incx [sens] * SNAKLES_LONG;
        yec += sk_incy [sens] * SNAKLES_HAUT;
        Afficher_Bob (page,BOB(sens,CORPS,coul),xec,yec,MASK_ON);
    }
    xec += sk_incx [sens] * SNAKLES_LONG;
    yec += sk_incy [sens] * SNAKLES_HAUT;
    Afficher_Bob (page,BOB(sens,QUEUE,coul),xec,yec,MASK_ON);
}
