#include <MATH.H>
#include "SOUREDIT/EDITSOUR.H"
#include "SOUREDIT/EDITPANN.H"
#include "SOUREDIT/EDITGRAP.H"
#include "SOUREDIT/EDITTABL.H"
#include "SOUREDIT/EDITBOIT.H"
#define EFFACAGE 0
#define AFFICHAGE 1
#define STOCKAGE 2
#define VIDE 0
#define PLEIN 1
extern OCTET buftab1_sans_cadre [BUFSIZE_SANS_CADRE];
OCTET buffer_undo [BUFSIZE_SANS_CADRE];
OCTET buffer_block [BUFSIZE_SANS_CADRE];
OCTET etat_block = 0;
OCTET lg_block;
OCTET ht_block;
void Fonction_Cls (void);
void Fonction_Undo (void);
void Fonction_Flip_Horizontal (void);
void Fonction_Flip_Vertical (void);
void Fonction_Copy (void);
void Fonction_Paste (void);
void Fonction_Cut (void);
void Fonction_Chrono (void);
void Fonction_Pastille (void);
void Fonction_Point (void);
void Fonction_Ligne (void);
void Fonction_Carre_Vide (void);
void Fonction_Carre_Plein (void);
void Fonction_Cercle_Vide (void);
void Fonction_Cercle_Plein (void);
void Fonction_Losange_Vide (void);
void Fonction_Losange_Plein (void);
void Fonction_Remplissage (void);
void Point_Selection (OCTET,OCTET,OCTET);
void Ligne_Selection (OCTET,OCTET,OCTET,OCTET,OCTET);
void Carre_Vide_Selection (OCTET,OCTET,OCTET,OCTET,OCTET);
void Losange_Vide_Selection (OCTET,OCTET,OCTET,OCTET,OCTET);
void Cercle_Vide_Selection (OCTET,OCTET,OCTET,OCTET,OCTET);
void Cercle_Plein_Selection (OCTET,OCTET,OCTET,OCTET,OCTET);
BOOL Select (OCTET*,OCTET*,OCTET*,OCTET*);
short y_inf [NB_OUTIL] = { 28, 51, 80,118,156,185,220,243,266,
                           299,310,321,332,343,354,365,376,387
                         };
short y_sup [NB_OUTIL] = { 50, 79,117,155,184,219,242,265,298,
                           309,320,331,342,353,364,375,386,396
                         };
short *adresse;
short *adresse_fonction [NB_OUTIL] =
{
    (short*)Fonction_Cls,
    (short*)Fonction_Undo,
    (short*)Fonction_Flip_Horizontal,
    (short*)Fonction_Flip_Vertical,
    (short*)Fonction_Copy,
    (short*)Fonction_Paste,
    (short*)Fonction_Cut,
    (short*)Fonction_Chrono,
    (short*)Fonction_Pastille,
    (short*)Fonction_Point,
    (short*)Fonction_Ligne,
    (short*)Fonction_Carre_Vide,
    (short*)Fonction_Carre_Plein,
    (short*)Fonction_Cercle_Vide,
    (short*)Fonction_Cercle_Plein,
    (short*)Fonction_Losange_Vide,
    (short*)Fonction_Losange_Plein,
    (short*)Fonction_Remplissage
};
void Traiter_Outils (void)
{
    OCTET cpt,cpt2;
    for (cpt = 0;
            cpt < NB_OUTIL;
            cpt ++)
    {
        if ( Test_Clic_Zone (X_Fleche (),Y_Fleche (),309,y_inf [cpt],
                             319,y_sup [cpt]) == ON )
        {
            if (adresse_fonction [cpt] == adresse_fonction[0])
            {
                Option (OFF,Lire_Page(),309,y_inf[0],319,y_sup[0]);
                Save_Undo ();
                Fonction_Cls ();
                WAIT_NO_CLIC;
                Option (ON,Lire_Page(),309,y_inf[0],319,y_sup[0]);
                break;
            }
            if (adresse_fonction [cpt] == adresse_fonction[1])
            {
                Option (OFF,Lire_Page(),309,y_inf[1],319,y_sup[1]);
                Fonction_Undo ();
                WAIT_NO_CLIC;
                Option (ON,Lire_Page(),309,y_inf[1],319,y_sup[1]);
                break;
            }
            if (adresse_fonction [cpt] == adresse_fonction[7])
            {
                Option (OFF,Lire_Page(),309,y_inf[7],319,y_sup[7]);
                Fonction_Chrono ();
                WAIT_NO_CLIC;
                Option (ON,Lire_Page(),309,y_inf[7],319,y_sup[7]);
                break;
            }
            if (adresse_fonction [cpt] == adresse_fonction[8])
            {
                Option (OFF,Lire_Page(),309,y_inf[8],319,y_sup[8]);
                Fonction_Pastille ();
                WAIT_NO_CLIC;
                Option (ON,Lire_Page(),309,y_inf[8],319,y_sup[8]);
                break;
            }
            for (cpt2 = 0;
                    cpt2 < NB_OUTIL;
                    cpt2 ++)
            {
                Souris (OFF);
                Tracer_Droite (Lire_Page (),
                               309,y_inf [cpt2],
                               309,y_inf [cpt2] + (y_sup [cpt2]-y_inf [cpt2]),
                               RELIEF_CLAIR);
                Tracer_Droite (Lire_Page (),
                               309,y_inf [cpt2],
                               309 + (319-309),y_inf [cpt2],
                               RELIEF_CLAIR);
                Tracer_Droite (Lire_Page (),
                               319,y_sup [cpt2],
                               319 - ((319-309)-1),y_sup [cpt2],
                               RELIEF_FONCE);
                Tracer_Droite (Lire_Page (),
                               319,y_sup [cpt2],
                               319,y_sup [cpt2] - ((y_sup [cpt2]-y_inf [cpt2])-1),
                               RELIEF_FONCE);
                Souris (ON);
            }
            Option (OFF,Lire_Page (),309,y_inf [cpt],319,y_sup [cpt]);
            adresse = adresse_fonction [cpt];
            WAIT_NO_CLIC;
            break;
        }
    }
}
void Appeler_Outils (void)
{
    Save_Undo ();
    asm call adresse;
}
void Initialiser_Outils (void)
{
    Option (OFF,Lire_Page (),309,y_inf [9],319,y_sup [9]);
    adresse = adresse_fonction [9];
}
void Init_Undo (void)
{
    short cpt;
    for (cpt = 0;
            cpt < BUFSIZE_SANS_CADRE;
            cpt ++)
        buffer_undo [cpt] = 0;
}
void Save_Undo (void)
{
    short cpt;
    for (cpt = 0;
            cpt < BUFSIZE_SANS_CADRE;
            cpt ++)
        buffer_undo [cpt] = buftab1_sans_cadre [cpt];
}
void Load_Undo (void)
{
    short cpt;
    for (cpt = 0;
            cpt < BUFSIZE_SANS_CADRE;
            cpt ++)
        buftab1_sans_cadre [cpt] = buffer_undo [cpt];
}
BOOL Select (OCTET *xa,OCTET *ya,OCTET *xb,OCTET *yb)
{
    OCTET x1,y1,x2,y2,xh,yh;
    x1 = X_Case ();
    y1 = Y_Case ();
    x2 = x1;
    y2 = y1;
    xh = x1;
    yh = y1;
    Souris (OFF);
    Carre_Vide_Selection (ON,x1,y1,x2,y2);
    Souris (ON);
    do
    {
        x2 = X_Case ();
        y2 = Y_Case ();
        if ( (x2 == 0) | (y2 == 0) )
        {
            Souris (OFF);
            Carre_Vide_Selection (EFFACAGE,x1,y1,xh,yh);
            Souris (ON);
            return (FAUX);
        }
        if ( (x2 != xh) | (y2 != yh) )
        {
            Souris (OFF);
            Carre_Vide_Selection (EFFACAGE,x1,y1,xh,yh);
            Carre_Vide_Selection (AFFICHAGE,x1,y1,x2,y2);
            Souris (ON);
            xh = x2;
            yh = y2;
        }
        if (x2!=0) Afficher_Nombre (Lire_Page(),BOB_CHIFFRE,2,x2,310,13,MASK_OFF);
        if (y2!=0) Afficher_Nombre (Lire_Page(),BOB_CHIFFRE,2,y2,310,20,MASK_OFF);
    }
    while ( (Clic_Souris () == CLIC_GAUCHE) | (Clic_Souris () == CLIC_DROITE) );
    Souris (OFF);
    Carre_Vide_Selection (EFFACAGE,x1,y1,xh,yh);
    Souris (ON);
    if (x1 < xh)
    {
        *xa = x1;
        *xb = xh;
    }
    else
    {
        *xa = xh;
        *xb = x1;
    }
    if (y1 < yh)
    {
        *ya = y1;
        *yb = yh;
    }
    else
    {
        *ya = yh;
        *yb = y1;
    }
    return (VRAI);
}
void Point_Selection (OCTET etat,OCTET x,OCTET y)
{
    OCTET pastille;
    short x_bob;
    short y_bob;
    OCTET c;
    c = 120;
    if (etat == STOCKAGE)
    {
        pastille = Numero_Pastille ();
        Ecrire_Case (buftab1_sans_cadre,pastille,x,y);
        Afficher_Case (BOB_PASTILLE,pastille,x,y);
    }
    if (etat == EFFACAGE)
    {
        pastille = Lire_Case (buftab1_sans_cadre,x,y);
        Afficher_Case (BOB_PASTILLE,pastille,x,y);
    }
    if (etat == AFFICHAGE)
    {
        if ( (x != 0) & (y != 0) )
        {
            x_bob = X_TAB_PASTILLES_SERPENTS + ( (x - 1) * LG_BOB );
            y_bob = Y_TAB_PASTILLES_SERPENTS + ( (y - 1) * HT_BOB );
            Tracer_Droite (Lire_Page (),x_bob,y_bob,
                           x_bob + (LG_BOB-1),y_bob,c);
            Tracer_Droite (Lire_Page (),x_bob,y_bob + (HT_BOB-1),
                           x_bob + (LG_BOB-1),y_bob + (HT_BOB-1),c);
            Tracer_Droite (Lire_Page (),x_bob,y_bob,
                           x_bob,y_bob + (HT_BOB-1),c);
            Tracer_Droite (Lire_Page (),x_bob + (LG_BOB-1),y_bob,
                           x_bob + (LG_BOB-1),y_bob + (HT_BOB-1),c);
        }
    }
}
void Ligne_Selection (OCTET etat,OCTET x,OCTET y,OCTET x2,OCTET y2)
{
    int i, steep = 0, sx, sy, dx, dy, e;
    dx = abs(x2 - x);
    sx = ((x2 - x) > 0) ? 1 : -1;
    dy = abs(y2 - y);
    sy = ((y2 - y) > 0) ? 1 : -1;
    if(dy > dx)
    {
        steep = 1;
        x ^= y;
        y ^= x;
        x ^= y;
        dx ^= dy;
        dy ^= dx;
        dx ^= dy;
        sx ^= sy;
        sy ^= sx;
        sx ^= sy;
    }
    e = 2 * dy - dx;
    for(i = 0; i < dx; i++)
    {
        if(steep)
            Point_Selection (etat,y,x);
        else
            Point_Selection (etat,x,y);
        while(e >= 0)
        {
            y += sy;
            e -= 2 * dx;
        }
        x += sx;
        e += 2 * dy;
    }
    Point_Selection (etat,x2,y2);
}
void Carre_Vide_Selection (OCTET etat,OCTET x1,OCTET y1,OCTET x2,OCTET y2)
{
    Ligne_Selection (etat,x1,y1,x2,y1);
    Ligne_Selection (etat,x1,y2,x2,y2);
    Ligne_Selection (etat,x1,y1,x1,y2);
    Ligne_Selection (etat,x2,y1,x2,y2);
}
void Cercle_Vide_Selection (OCTET etat,OCTET x1,OCTET y1,OCTET x2,OCTET y2)
{
    OCTET xy;
    float d;
    float x,y;
    char ajx,ajy;
    float xd,yd;
    float xr,yr;
    float xc,yc;
    float xe,ye;
    OCTET cpt;
    if (x2 < x1)
    {
        xy = x1;
        x1 = x2;
        x2 = xy;
    }
    if (y2 < y1)
    {
        xy = y1;
        y1 = y2;
        y2 = xy;
    }
    if (x1 == x2)
    {
        for (cpt = y1;
                cpt <= y2;
                cpt ++)
            Point_Selection (etat,x1,cpt);
        return;
    }
    if (y1 == y2)
    {
        for (cpt = x1;
                cpt <= x2;
                cpt ++)
            Point_Selection (etat,cpt,y1);
        return;
    }
    xd = (OCTET)(x2 - x1);
    yd = (OCTET)(y2 - y1);
    xr = xd / 2;
    yr = yd / 2;
    xc = x1 + xr;
    yc = y1 + yr;
    ajx = (!((OCTET)xd % 2)) ? 0 : 1;
    ajy = (!((OCTET)yd % 2)) ? 0 : 1;
    if (xd == yd)
    {
        xe = 1;
        ye = 1;
        x = 0;
        y = yr;
        d = (2 * (1 - yr)) - 1;
        while (y > 0)
        {
            Point_Selection (etat,xc + x + ajx, yc + y);
            Point_Selection (etat,xc - x, yc - y);
            Point_Selection (etat,xc - x, yc + y);
            Point_Selection (etat,xc + x + ajx, yc - y);
            if (d + y > 0)
            {
                y -= 1;
                d -= (2 * y * ye) - 1;
            }
            if (x > d)
            {
                x += 1;
                d += (2 * x * xe) + 1;
            }
        }
        Point_Selection (etat,xc + x + ajx, yc);
        Point_Selection (etat,xc - x, yc);
        return;
    }
    if (yd < xd)
    {
        xe = 1;
        ye = (xd/yd)*(xd/yd);
        y = 0;
        x = xr;
        d = (2 * (1 - xr)) - 1;
        while (x > 0)
        {
            Point_Selection (etat,xc + x, yc + y );
            Point_Selection (etat,xc - x, yc - y + ajy);
            Point_Selection (etat,xc - x, yc + y );
            Point_Selection (etat,xc + x, yc - y + ajy);
            if (d + x > 0)
            {
                x -= 1;
                d -= (2 * x * xe) - 1;
            }
            if (y > d)
            {
                y += 1;
                d += (2 * y * ye) + 1;
            }
        }
        Point_Selection (etat,xc, yc + y );
        Point_Selection (etat,xc, yc - y + ajy);
        return;
    }
    if (xd < yd)
    {
        xe = (yd / xd) * (yd / xd);
        ye = 1;
        x = 0;
        y = yr;
        d = (2 * (1 - yr)) - 1;
        while (y > 0)
        {
            Point_Selection (etat,xc + x, yc + y);
            Point_Selection (etat,xc - x + ajx, yc - y);
            Point_Selection (etat,xc - x + ajx, yc + y);
            Point_Selection (etat,xc + x, yc - y);
            if (d + y > 0)
            {
                y -= 1;
                d -= (2 * y * ye) - 1;
            }
            if (x > d)
            {
                x += 1;
                d += (2 * x * xe) + 1;
            }
        }
        Point_Selection (etat,xc + x, yc);
        Point_Selection (etat,xc - x + ajx, yc);
    }
}
void Cercle_Plein_Selection (OCTET etat,OCTET x1,OCTET y1,OCTET x2,OCTET y2)
{
    OCTET xy;
    float d;
    float x,y;
    char ajx,ajy;
    float xd,yd;
    float xr,yr;
    float xc,yc;
    float xe,ye;
    OCTET cpt;
    if (x2 < x1)
    {
        xy = x1;
        x1 = x2;
        x2 = xy;
    }
    if (y2 < y1)
    {
        xy = y1;
        y1 = y2;
        y2 = xy;
    }
    if (x1 == x2)
    {
        for (cpt = y1;
                cpt <= y2;
                cpt ++)
            Point_Selection (etat,x1,cpt);
        return;
    }
    if (y1 == y2)
    {
        for (cpt = x1;
                cpt <= x2;
                cpt ++)
            Point_Selection (etat,cpt,y1);
        return;
    }
    xd = (OCTET)(x2 - x1);
    yd = (OCTET)(y2 - y1);
    xr = xd / 2;
    yr = yd / 2;
    xc = x1 + xr;
    yc = y1 + yr;
    ajx = (!((OCTET)xd % 2)) ? 0 : 1;
    ajy = (!((OCTET)yd % 2)) ? 0 : 1;
    if (xd == yd)
    {
        xe = 1;
        ye = 1;
        x = 0;
        y = yr;
        d = (2 * (1 - yr)) - 1;
        while (y > 0)
        {
            Ligne_Selection (etat,xc,yc+y,xc+x+ajx,yc+y);
            Ligne_Selection (etat,xc,yc-y,xc-x,yc-y);
            Ligne_Selection (etat,xc,yc+y,xc-x,yc+y);
            Ligne_Selection (etat,xc,yc-y,xc+x+ajx,yc-y);
            if (d + y > 0)
            {
                y -= 1;
                d -= (2 * y * ye) - 1;
            }
            if (x > d)
            {
                x += 1;
                d += (2 * x * xe) + 1;
            }
        }
        Ligne_Selection (etat,xc-x,yc,xc+x+ajx,yc);
        return;
    }
    if (yd < xd)
    {
        xe = 1;
        ye = (xd/yd)*(xd/yd);
        y = 0;
        x = xr;
        d = (2 * (1 - xr)) - 1;
        while (x > 0)
        {
            Ligne_Selection (etat,xc,yc+y,xc+x,yc+y);
            Ligne_Selection (etat,xc,yc-y+ajy,xc-x,yc-y+ajy);
            Ligne_Selection (etat,xc,yc+y,xc-x,yc+y);
            Ligne_Selection (etat,xc,yc-y+ajy,xc+x,yc-y+ajy);
            if (d + x > 0)
            {
                x -= 1;
                d -= (2 * x * xe) - 1;
            }
            if (y > d)
            {
                y += 1;
                d += (2 * y * ye) + 1;
            }
        }
        Ligne_Selection (etat,xc,yc+y,xc,yc-y+ajy);
        return;
    }
    if (xd < yd)
    {
        xe = (yd / xd) * (yd / xd);
        ye = 1;
        x = 0;
        y = yr;
        d = (2 * (1 - yr)) - 1;
        while (y > 0)
        {
            Ligne_Selection (etat,xc,yc+y,xc+x,yc+y);
            Ligne_Selection (etat,xc,yc-y,xc-x+ajx,yc-y);
            Ligne_Selection (etat,xc,yc+y,xc-x+ajx,yc+y);
            Ligne_Selection (etat,xc,yc-y,xc+x,yc-y);
            if (d + y > 0)
            {
                y -= 1;
                d -= (2 * y * ye) - 1;
            }
            if (x > d)
            {
                x += 1;
                d += (2 * x * xe) + 1;
            }
        }
        Ligne_Selection (etat,xc+x,yc,xc-x+ajx,yc);
    }
}
void Losange_Vide_Selection (OCTET etat,OCTET x1,OCTET y1,OCTET x2,OCTET y2)
{
    OCTET xa,ya,xb,yb;
    OCTET lg;
    OCTET ht;
    if (x2 < x1)
    {
        xa = x2;
        xb = x1;
    }
    else
    {
        xa = x1;
        xb = x2;
    }
    if (y2 < y1)
    {
        ya = y2;
        yb = y1;
    }
    else
    {
        ya = y1;
        yb = y2;
    }
    lg = ( xb - xa ) / 2;
    ht = ( yb - ya ) / 2;
    Ligne_Selection (etat,xb - lg,ya,xb,ya + ht);
    Ligne_Selection (etat,xb - lg,yb,xb,yb - ht);
    Ligne_Selection (etat,xa + lg,yb,xa,yb - ht);
    Ligne_Selection (etat,xa + lg,ya,xa,ya + ht);
}
void Fonction_Cls (void)
{
    OCTET page;
    short cpt;
    OCTET reponse;
    page = Lire_Page ();
    Afficher_Boite_Message (page,INFO10);
    reponse = RIEN;
    do
    {
        if ( Test_Option (INFO10_OUI) == ON )
        {
            reponse = OUI;
            Option (OFF,page,INFO10_OUI);
            WAIT_NO_CLIC;
            Option (ON,page,INFO10_OUI);
        }
        if ( Test_Option (INFO10_NON) == ON )
        {
            reponse = NON;
            Option (OFF,page,INFO10_NON);
            WAIT_NO_CLIC;
            Option (ON,page,INFO10_NON);
        }
    }
    while (reponse == RIEN);
    Effacer_Boite (page);
    if (reponse == OUI)
    {
        for (cpt = 0;
                cpt < BUFSIZE_SANS_CADRE;
                cpt ++)
            buftab1_sans_cadre [cpt] = 0;
        Afficher_Cases (buftab1_sans_cadre,BOB_PASTILLE-1,1,1,43,33);
    }
    Ecrire_Panneau_Demande (0);
}
void Fonction_Undo (void)
{
    Load_Undo ();
    Afficher_Cases (buftab1_sans_cadre,BOB_PASTILLE-1,1,1,43,33);
}
void Fonction_Point (void)
{
    OCTET pastille;
    OCTET x,y;
    pastille = Numero_Pastille ();
    do
    {
        x = X_Case ();
        y = Y_Case ();
        if ( (x == 0) | (y == 0) )
            return;
        if (Lire_Case (buftab1_sans_cadre,x,y) != pastille)
        {
            Souris (OFF);
            Point_Selection (STOCKAGE,x,y);
            Souris (ON);
        }
        if (x!=0) Afficher_Nombre (Lire_Page(),BOB_CHIFFRE,2,x,310,13,MASK_OFF);
        if (y!=0) Afficher_Nombre (Lire_Page(),BOB_CHIFFRE,2,y,310,20,MASK_OFF);
    }
    while ( (Clic_Souris () == CLIC_GAUCHE) | (Clic_Souris () == CLIC_DROITE) );
}
void Fonction_Flip_Horizontal (void)
{
    OCTET buffer [BUFSIZE_SANS_CADRE];
    OCTET x1,y1,x2,y2;
    OCTET cpty,cptx;
    OCTET element;
    short indice;
    if (Select (&x1,&y1,&x2,&y2) == VRAI)
    {
        indice = 0;
        for (cpty = y1;
                cpty <= y2;
                cpty ++)
        {
            for (cptx = x1;
                    cptx <= x2;
                    cptx ++)
            {
                element = Lire_Case (buftab1_sans_cadre,cptx,cpty);
                buffer [indice] = element;
                indice ++;
            }
        }
        indice = 0;
        Souris (OFF);
        for (cpty = y1;
                cpty <= y2;
                cpty ++)
        {
            for (cptx = x2;
                    cptx >= x1;
                    cptx --)
            {
                element = buffer [indice];
                indice ++;
                Ecrire_Case (buftab1_sans_cadre,element,cptx,cpty);
                Afficher_Case (BOB_PASTILLE,element,cptx,cpty);
            }
        }
        Souris (ON);
    }
}
void Fonction_Flip_Vertical (void)
{
    OCTET buffer [BUFSIZE_SANS_CADRE];
    OCTET x1,y1,x2,y2;
    OCTET cpty,cptx;
    OCTET element;
    short indice;
    if (Select (&x1,&y1,&x2,&y2) == VRAI)
    {
        indice = 0;
        for (cpty = y1;
                cpty <= y2;
                cpty ++)
        {
            for (cptx = x1;
                    cptx <= x2;
                    cptx ++)
            {
                element = Lire_Case (buftab1_sans_cadre,cptx,cpty);
                buffer [indice] = element;
                indice ++;
            }
        }
        indice = 0;
        Souris (OFF);
        for (cpty = y2;
                cpty >= y1;
                cpty --)
        {
            for (cptx = x1;
                    cptx <= x2;
                    cptx ++)
            {
                element = buffer [indice];
                indice ++;
                Ecrire_Case (buftab1_sans_cadre,element,cptx,cpty);
                Afficher_Case (BOB_PASTILLE,element,cptx,cpty);
            }
        }
        Souris (ON);
    }
}
void Fonction_Copy (void)
{
    OCTET x1,y1,x2,y2;
    OCTET cpty,cptx;
    OCTET element;
    short indice = 0;
    if (Select (&x1,&y1,&x2,&y2) == VRAI)
    {
        etat_block = PLEIN;
        lg_block = x2 - x1;
        ht_block = y2 - y1;
        for (cpty = y1;
                cpty <= y2;
                cpty ++)
        {
            for (cptx = x1;
                    cptx <= x2;
                    cptx ++)
            {
                element = Lire_Case (buftab1_sans_cadre,cptx,cpty);
                buffer_block [indice] = element;
                indice ++;
            }
        }
    }
}
void Fonction_Paste (void)
{
    OCTET x1,y1,x2,y2;
    OCTET cpty,cptx;
    OCTET element;
    short indice = 0;
    do {}
    while ( (Clic_Souris () == CLIC_GAUCHE) | (Clic_Souris () == CLIC_DROITE) );
    if (etat_block == VIDE) return;
    x1 = X_Case ();
    y1 = Y_Case ();
    if ( (x1 == 0) | (y1 == 0) ) return;
    x2 = x1 + lg_block;
    y2 = y1 + ht_block;
    Souris (OFF);
    for (cpty = y1;
            cpty <= y2;
            cpty ++)
    {
        for (cptx = x1;
                cptx <= x2;
                cptx ++)
        {
            if ( (cptx <= X_MAX - 2) & (cpty <= Y_MAX - 2) )
            {
                element = buffer_block [indice];
                indice ++;
                Ecrire_Case (buftab1_sans_cadre,element,cptx,cpty);
                Afficher_Case (BOB_PASTILLE,element,cptx,cpty);
            }
            else
                indice ++;
        }
    }
    Souris (ON);
}
void Fonction_Cut (void)
{
    OCTET x1,y1,x2,y2;
    OCTET cpty,cptx;
    if (Select (&x1,&y1,&x2,&y2) == VRAI)
    {
        for (cpty = y1;
                cpty <= y2;
                cpty ++)
        {
            for (cptx = x1;
                    cptx <= x2;
                    cptx ++)
            {
                Ecrire_Case (buftab1_sans_cadre,0,cptx,cpty);
            }
        }
        Afficher_Cases (buftab1_sans_cadre,BOB_PASTILLE-1,x1,y1,x2,y2);
    }
}
void Fonction_Chrono (void)
{
    OCTET page;
    OCTET sortie;
    short chrono;
    sortie = OFF;
    page = Lire_Page ();
    WAIT_NO_CLIC;
    Afficher_Boite_Message (page,INFO04);
    do
    {
        if ( Test_Option (INFO04_GAUCHE) == ON )
        {
            chrono = Traiter_Fleche (page,DEC,
                                     Lire_Temps (),
                                     INFO04_MIN,
                                     INFO04_MAX,
                                     INFO04_GAUCHE,
                                     INFO04_NB,
                                     INFO04_LGNB);
            Ecrire_Temps (chrono);
        }
        if ( Test_Option (INFO04_DROITE) == ON )
        {
            chrono = Traiter_Fleche (page,INC,
                                     Lire_Temps (),
                                     INFO04_MIN,
                                     INFO04_MAX,
                                     INFO04_DROITE,
                                     INFO04_NB,
                                     INFO04_LGNB);
            Ecrire_Temps (chrono);
        }
        if ( Test_Option (INFO04_OK) == ON )
        {
            sortie = ON;
            Option (OFF,page,INFO04_OK);
            WAIT_NO_CLIC;
            Option (ON,page,INFO04_OK);
        }
    }
    while (sortie == OFF);
    Effacer_Boite (page);
    Ecrire_Panneau_Demande (0);
}
void Fonction_Pastille (void)
{
    OCTET page;
    OCTET sortie;
    short valeur;
    sortie = OFF;
    page = Lire_Page ();
    WAIT_NO_CLIC;
    Afficher_Boite_Message (page,INFO05);
    do
    {
        if ( Test_Option (INFO05_1_GAUCHE) == ON )
        {
            valeur = Traiter_Fleche (Lire_Page (),DEC,
                                     Lire_Vlbonus (),
                                     INFO05_1_MIN,
                                     INFO05_1_MAX,
                                     INFO05_1_GAUCHE,
                                     INFO05_1_NB,
                                     INFO05_1_LGNB);
            Ecrire_Vlbonus (valeur);
        }
        if ( Test_Option (INFO05_1_DROITE) == ON )
        {
            valeur = Traiter_Fleche (Lire_Page (),INC,
                                     Lire_Vlbonus (),
                                     INFO05_1_MIN,
                                     INFO05_1_MAX,
                                     INFO05_1_DROITE,
                                     INFO05_1_NB,
                                     INFO05_1_LGNB);
            Ecrire_Vlbonus (valeur);
        }
        if ( Test_Option (INFO05_2_GAUCHE) == ON )
        {
            valeur = Traiter_Fleche (Lire_Page (),DEC,
                                     Lire_Temps_Plus (),
                                     INFO05_2_MIN,
                                     INFO05_2_MAX,
                                     INFO05_2_GAUCHE,
                                     INFO05_2_NB,
                                     INFO05_2_LGNB);
            Ecrire_Temps_Plus (valeur);
        }
        if ( Test_Option (INFO05_2_DROITE) == ON )
        {
            valeur = Traiter_Fleche (Lire_Page (),INC,
                                     Lire_Temps_Plus (),
                                     INFO05_2_MIN,
                                     INFO05_2_MAX,
                                     INFO05_2_DROITE,
                                     INFO05_2_NB,
                                     INFO05_2_LGNB);
            Ecrire_Temps_Plus (valeur);
        }
        if ( Test_Option (INFO05_3_GAUCHE) == ON )
        {
            valeur = Traiter_Fleche (Lire_Page (),DEC,
                                     Lire_Temps_Moins (),
                                     INFO05_3_MIN,
                                     INFO05_3_MAX,
                                     INFO05_3_GAUCHE,
                                     INFO05_3_NB,
                                     INFO05_3_LGNB);
            Ecrire_Temps_Moins (valeur);
        }
        if ( Test_Option (INFO05_3_DROITE) == ON )
        {
            valeur = Traiter_Fleche (Lire_Page (),INC,
                                     Lire_Temps_Moins (),
                                     INFO05_3_MIN,
                                     INFO05_3_MAX,
                                     INFO05_3_DROITE,
                                     INFO05_3_NB,
                                     INFO05_3_LGNB);
            Ecrire_Temps_Moins (valeur);
        }
        if ( Test_Option (INFO05_OK) == ON )
        {
            sortie = ON;
            Option (OFF,page,INFO05_OK);
            WAIT_NO_CLIC;
            Option (ON,page,INFO05_OK);
        }
    }
    while (sortie == OFF);
    Effacer_Boite (page);
    Ecrire_Panneau_Demande (0);
}
void Fonction_Ligne (void)
{
    OCTET x1,y1,x2,y2,xh,yh;
    x1 = X_Case ();
    y1 = Y_Case ();
    x2 = x1;
    y2 = y1;
    xh = x1;
    yh = y1;
    Souris (OFF);
    Ligne_Selection (AFFICHAGE,x1,y1,x2,y2);
    Souris (ON);
    do
    {
        x2 = X_Case ();
        y2 = Y_Case ();
        if ( (x2 == 0) | (y2 == 0) )
        {
            Souris (OFF);
            Ligne_Selection (EFFACAGE,x1,y1,xh,yh);
            Souris (ON);
            return;
        }
        if ( (x2 != xh) | (y2 != yh) )
        {
            Souris (OFF);
            Ligne_Selection (EFFACAGE,x1,y1,xh,yh);
            Ligne_Selection (AFFICHAGE,x1,y1,x2,y2);
            Souris (ON);
            xh = x2;
            yh = y2;
        }
        if (x2!=0) Afficher_Nombre (Lire_Page(),BOB_CHIFFRE,2,x2,310,13,MASK_OFF);
        if (y2!=0) Afficher_Nombre (Lire_Page(),BOB_CHIFFRE,2,y2,310,20,MASK_OFF);
    }
    while ( (Clic_Souris () == CLIC_GAUCHE) | (Clic_Souris () == CLIC_DROITE) );
    Souris (OFF);
    Ligne_Selection (STOCKAGE,x1,y1,xh,yh);
    Souris (ON);
}
void Fonction_Carre_Vide (void)
{
    OCTET x1,y1,x2,y2,xh,yh;
    x1 = X_Case ();
    y1 = Y_Case ();
    x2 = x1;
    y2 = y1;
    xh = x1;
    yh = y1;
    Souris (OFF);
    Carre_Vide_Selection (ON,x1,y1,x2,y2);
    Souris (ON);
    do
    {
        x2 = X_Case ();
        y2 = Y_Case ();
        if ( (x2 == 0) | (y2 == 0) )
        {
            Souris (OFF);
            Carre_Vide_Selection (EFFACAGE,x1,y1,xh,yh);
            Souris (ON);
            return;
        }
        if ( (x2 != xh) | (y2 != yh) )
        {
            Souris (OFF);
            Carre_Vide_Selection (EFFACAGE,x1,y1,xh,yh);
            Carre_Vide_Selection (AFFICHAGE,x1,y1,x2,y2);
            Souris (ON);
            xh = x2;
            yh = y2;
        }
        if (x2!=0) Afficher_Nombre (Lire_Page(),BOB_CHIFFRE,2,x2,310,13,MASK_OFF);
        if (y2!=0) Afficher_Nombre (Lire_Page(),BOB_CHIFFRE,2,y2,310,20,MASK_OFF);
    }
    while ( (Clic_Souris () == CLIC_GAUCHE) | (Clic_Souris () == CLIC_DROITE) );
    Souris (OFF);
    Carre_Vide_Selection (STOCKAGE,x1,y1,xh,yh);
    Souris (ON);
}
void Fonction_Carre_Plein (void)
{
    OCTET cpt;
    OCTET ht,lg;
    OCTET valcpt;
    OCTET xa,ya,xb,yb;
    OCTET x1,y1,x2,y2,xh,yh;
    x1 = X_Case ();
    y1 = Y_Case ();
    x2 = x1;
    y2 = y1;
    xh = x1;
    yh = y1;
    Souris (OFF);
    Carre_Vide_Selection (ON,x1,y1,x2,y2);
    Souris (ON);
    do
    {
        x2 = X_Case ();
        y2 = Y_Case ();
        if ( (x2 == 0) | (y2 == 0) )
        {
            Souris (OFF);
            Carre_Vide_Selection (EFFACAGE,x1,y1,xh,yh);
            Souris (ON);
            return;
        }
        if ( (x2 != xh) | (y2 != yh) )
        {
            Souris (OFF);
            Carre_Vide_Selection (EFFACAGE,x1,y1,xh,yh);
            Carre_Vide_Selection (AFFICHAGE,x1,y1,x2,y2);
            Souris (ON);
            xh = x2;
            yh = y2;
        }
        if (x2!=0) Afficher_Nombre (Lire_Page(),BOB_CHIFFRE,2,x2,310,13,MASK_OFF);
        if (y2!=0) Afficher_Nombre (Lire_Page(),BOB_CHIFFRE,2,y2,310,20,MASK_OFF);
    }
    while ( (Clic_Souris () == CLIC_GAUCHE) | (Clic_Souris () == CLIC_DROITE) );
    if (xh < x1)
    {
        xa = xh;
        xb = x1;
    }
    else
    {
        xa = x1;
        xb = xh;
    }
    if (yh < y1)
    {
        ya = yh;
        yb = y1;
    }
    else
    {
        ya = y1;
        yb = yh;
    }
    lg = (xb - xa) / 2;
    ht = (yb - ya) / 2;
    valcpt = (lg > ht) ? lg : ht;
    Souris (OFF);
    Carre_Vide_Selection (STOCKAGE,xa,ya,xb,yb);
    for (cpt = 0;
            cpt < valcpt;
            cpt ++)
    {
        if (xa < xb)
        {
            xa ++;
            xb --;
        }
        if (ya < yb)
        {
            ya ++;
            yb --;
        }
        Carre_Vide_Selection (STOCKAGE,xa,ya,xb,yb);
    }
    Souris (ON);
}
void Fonction_Cercle_Vide (void)
{
    OCTET x1,y1,x2,y2,xh,yh;
    x1 = X_Case ();
    y1 = Y_Case ();
    x2 = x1;
    y2 = y1;
    xh = x1;
    yh = y1;
    Souris (OFF);
    Cercle_Vide_Selection (ON,x1,y1,x2,y2);
    Souris (ON);
    do
    {
        x2 = X_Case ();
        y2 = Y_Case ();
        if ( (x2 == 0) | (y2 == 0) )
        {
            Souris (OFF);
            Cercle_Vide_Selection (EFFACAGE,x1,y1,xh,yh);
            Souris (ON);
            return;
        }
        if ( (x2 != xh) | (y2 != yh) )
        {
            Souris (OFF);
            Cercle_Vide_Selection (EFFACAGE,x1,y1,xh,yh);
            Cercle_Vide_Selection (AFFICHAGE,x1,y1,x2,y2);
            Souris (ON);
            xh = x2;
            yh = y2;
        }
        if (x2!=0) Afficher_Nombre (Lire_Page(),BOB_CHIFFRE,2,x2,310,13,MASK_OFF);
        if (y2!=0) Afficher_Nombre (Lire_Page(),BOB_CHIFFRE,2,y2,310,20,MASK_OFF);
    }
    while ( (Clic_Souris () == CLIC_GAUCHE) | (Clic_Souris () == CLIC_DROITE) );
    Souris (OFF);
    Cercle_Vide_Selection (STOCKAGE,x1,y1,xh,yh);
    Souris (ON);
}
void Fonction_Cercle_Plein (void)
{
    OCTET x1,y1,x2,y2,xh,yh;
    x1 = X_Case ();
    y1 = Y_Case ();
    x2 = x1;
    y2 = y1;
    xh = x1;
    yh = y1;
    Souris (OFF);
    Cercle_Vide_Selection (ON,x1,y1,x2,y2);
    Souris (ON);
    do
    {
        x2 = X_Case ();
        y2 = Y_Case ();
        if ( (x2 == 0) | (y2 == 0) )
        {
            Souris (OFF);
            Cercle_Vide_Selection (EFFACAGE,x1,y1,xh,yh);
            Souris (ON);
            return;
        }
        if ( (x2 != xh) | (y2 != yh) )
        {
            Souris (OFF);
            Cercle_Vide_Selection (EFFACAGE,x1,y1,xh,yh);
            Cercle_Vide_Selection (AFFICHAGE,x1,y1,x2,y2);
            Souris (ON);
            xh = x2;
            yh = y2;
        }
        if (x2!=0) Afficher_Nombre (Lire_Page(),BOB_CHIFFRE,2,x2,310,13,MASK_OFF);
        if (y2!=0) Afficher_Nombre (Lire_Page(),BOB_CHIFFRE,2,y2,310,20,MASK_OFF);
    }
    while ( (Clic_Souris () == CLIC_GAUCHE) | (Clic_Souris () == CLIC_DROITE) );
    Souris (OFF);
    Cercle_Plein_Selection (STOCKAGE,x1,y1,xh,yh);
    Souris (ON);
}
void Fonction_Losange_Vide (void)
{
    OCTET x1,y1,x2,y2,xh,yh;
    x1 = X_Case ();
    y1 = Y_Case ();
    x2 = x1;
    y2 = y1;
    xh = x1;
    yh = y1;
    Souris (OFF);
    Losange_Vide_Selection (ON,x1,y1,x2,y2);
    Souris (ON);
    do
    {
        x2 = X_Case ();
        y2 = Y_Case ();
        if ( (x2 == 0) | (y2 == 0) )
        {
            Souris (OFF);
            Losange_Vide_Selection (EFFACAGE,x1,y1,xh,yh);
            Souris (ON);
            return;
        }
        if ( (x2 != xh) | (y2 != yh) )
        {
            Souris (OFF);
            Losange_Vide_Selection (EFFACAGE,x1,y1,xh,yh);
            Losange_Vide_Selection (AFFICHAGE,x1,y1,x2,y2);
            Souris (ON);
            xh = x2;
            yh = y2;
        }
        if (x2!=0) Afficher_Nombre (Lire_Page(),BOB_CHIFFRE,2,x2,310,13,MASK_OFF);
        if (y2!=0) Afficher_Nombre (Lire_Page(),BOB_CHIFFRE,2,y2,310,20,MASK_OFF);
    }
    while ( (Clic_Souris () == CLIC_GAUCHE) | (Clic_Souris () == CLIC_DROITE) );
    Souris (OFF);
    Losange_Vide_Selection (STOCKAGE,x1,y1,xh,yh);
    Souris (ON);
}
void Fonction_Losange_Plein (void)
{
    OCTET cpt;
    OCTET ht,lg;
    OCTET valcpt;
    OCTET xa,ya,xb,yb;
    OCTET x1,y1,x2,y2,xh,yh;
    x1 = X_Case ();
    y1 = Y_Case ();
    x2 = x1;
    y2 = y1;
    xh = x1;
    yh = y1;
    Souris (OFF);
    Losange_Vide_Selection (ON,x1,y1,x2,y2);
    Souris (ON);
    do
    {
        x2 = X_Case ();
        y2 = Y_Case ();
        if ( (x2 == 0) | (y2 == 0) )
        {
            Souris (OFF);
            Losange_Vide_Selection (EFFACAGE,x1,y1,xh,yh);
            Souris (ON);
            return;
        }
        if ( (x2 != xh) | (y2 != yh) )
        {
            Souris (OFF);
            Losange_Vide_Selection (EFFACAGE,x1,y1,xh,yh);
            Losange_Vide_Selection (AFFICHAGE,x1,y1,x2,y2);
            Souris (ON);
            xh = x2;
            yh = y2;
        }
        if (x2!=0) Afficher_Nombre (Lire_Page(),BOB_CHIFFRE,2,x2,310,13,MASK_OFF);
        if (y2!=0) Afficher_Nombre (Lire_Page(),BOB_CHIFFRE,2,y2,310,20,MASK_OFF);
    }
    while ( (Clic_Souris () == CLIC_GAUCHE) | (Clic_Souris () == CLIC_DROITE) );
    if (xh < x1)
    {
        xa = xh;
        xb = x1;
    }
    else
    {
        xa = x1;
        xb = xh;
    }
    if (yh < y1)
    {
        ya = yh;
        yb = y1;
    }
    else
    {
        ya = y1;
        yb = yh;
    }
    lg = (xb - xa) / 2;
    ht = (yb - ya) / 2;
    valcpt = (lg > ht) ? lg : ht;
    Souris (OFF);
    Losange_Vide_Selection (STOCKAGE,xa,ya,xb,yb);
    for (cpt = 0;
            cpt < valcpt;
            cpt ++)
    {
        if (xa < xb)
        {
            xa ++;
            xb --;
        }
        if (ya < yb)
        {
            ya ++;
            yb --;
        }
        Losange_Vide_Selection (STOCKAGE,xa,ya,xb,yb);
    }
    Souris (ON);
}
#define MAX_LIGNE 100
#define byte unsigned char
#define bool unsigned char
typedef struct
{
    byte val_element;
    byte val_zone;
    byte x1_extremite;
    byte x2_extremite;
    byte y_extremite;
    byte x_buffer [MAX_LIGNE];
    byte y_buffer [MAX_LIGNE];
    byte x_min;
    byte y_min;
    byte x_max;
    byte y_max;
    short cpt_ligne;
} enreg_paint;
void Supprimer_Indice0 (enreg_paint *pt)
{
    short cpt;
    pt->cpt_ligne --;
    for (cpt = 0;
            cpt < pt->cpt_ligne;
            cpt ++)
    {
        pt->x_buffer [cpt] = pt->x_buffer [cpt+1];
        pt->y_buffer [cpt] = pt->y_buffer [cpt+1];
    }
}
void Rechercher_Extremite (enreg_paint *pt)
{
    byte val_case;
    pt->x1_extremite = pt->x_buffer [0];
    pt->x2_extremite = pt->x_buffer [0];
    pt->y_extremite = pt->y_buffer [0];
    Supprimer_Indice0 (pt);
    val_case = Lire_Case (buftab1_sans_cadre,pt->x2_extremite+1,pt->y_extremite);
    while ( (val_case == pt->val_zone) & (pt->x2_extremite+1 <= pt->x_max) )
    {
        pt->x2_extremite ++;
        val_case = Lire_Case (buftab1_sans_cadre,pt->x2_extremite+1,
                              pt->y_extremite);
    }
    val_case = Lire_Case (buftab1_sans_cadre,pt->x1_extremite-1,pt->y_extremite);
    while ( (val_case == pt->val_zone) & (pt->x1_extremite-1 >= pt->x_min) )
    {
        pt->x1_extremite --;
        val_case = Lire_Case (buftab1_sans_cadre,pt->x1_extremite-1,
                              pt->y_extremite);
    }
}
void Tracer_Ligne (enreg_paint *pt)
{
    byte cpt;
    for (cpt = pt->x1_extremite;
            cpt <= pt->x2_extremite;
            cpt ++)
        Point_Selection (STOCKAGE,cpt,pt->y_extremite);
}
bool Verifier_Zone (enreg_paint *pt)
{
    byte val_case;
    bool sortie;
    val_case = Lire_Case (buftab1_sans_cadre,pt->x_buffer [0],pt->y_buffer [0]);
    sortie = VRAI;
    if (val_case != pt->val_zone)
    {
        Supprimer_Indice0 (pt);
        sortie = FAUX;
    }
    return (sortie);
}
void Rechercher_Zone (enreg_paint *pt)
{
    byte val_case;
    byte cpt_case;
    byte num_ligne;
    char cpt_ligne;
    bool meme_ligne;
    for (cpt_ligne = -1;
            cpt_ligne <= 1;
            cpt_ligne +=2)
    {
        meme_ligne = FAUX;
        for (cpt_case = pt->x1_extremite;
                cpt_case <= pt->x2_extremite;
                cpt_case ++)
        {
            num_ligne = pt->y_extremite + cpt_ligne;
            if ( (num_ligne >= pt->y_min) & (num_ligne <= pt->y_max) )
            {
                val_case = Lire_Case (buftab1_sans_cadre,cpt_case,num_ligne);
                if ( (val_case == pt->val_zone) & (meme_ligne == FAUX) )
                {
                    if (pt->cpt_ligne < MAX_LIGNE)
                    {
                        pt->x_buffer [pt->cpt_ligne] = cpt_case;
                        pt->y_buffer [pt->cpt_ligne] = num_ligne;
                        pt->cpt_ligne ++;
                        meme_ligne = VRAI;
                    }
                }
                else
                {
                    if (val_case != pt->val_zone)
                        meme_ligne = FAUX;
                }
            }
        }
    }
}
void Fonction_Remplissage (void)
{
    enreg_paint paint;
    paint.val_element = Numero_Pastille ();
    paint.val_zone = Lire_Case (buftab1_sans_cadre,X_Case (),Y_Case ());
    paint.x_buffer [0] = X_Case ();
    paint.y_buffer [0] = Y_Case ();
    paint.cpt_ligne = 1;
    paint.x_min = X_MIN + 1;
    paint.y_min = Y_MIN + 1;
    paint.x_max = X_MAX - 2;
    paint.y_max = Y_MAX - 2;
    if ( (paint.x_buffer [0] == 0) | (paint.y_buffer [0] == 0) ) return;
    if (paint.val_element == paint.val_zone) return;
    do {}
    while ( (Clic_Souris () == CLIC_GAUCHE) | (Clic_Souris () == CLIC_DROITE) );
    do
    {
        if (Verifier_Zone (&paint) == VRAI)
        {
            Rechercher_Extremite (&paint);
            Souris (OFF);
            Tracer_Ligne (&paint);
            Souris (ON);
            Rechercher_Zone (&paint);
        }
    }
    while (paint.cpt_ligne>0);
}
