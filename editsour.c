#include <DOS.H>
#include "SOUREDIT/EDITSOUR.H"
#include "SOUREDIT/EDITGRAP.H"
#define TIMER_INTERRUPTION 8
#define FREQUENCE 50
#define CURS_ORIGX 0
#define CURS_ORIGY 0
void interrupt far Routine_Timer_Interruption (void);
void (interrupt far *Ancienne_Interruption_Timer) (void);
void Determiner_Curseur (void);
short Lire_X_Souris (void);
short Lire_Y_Souris (void);
void Accelerer_Horloge (OCTET);
void Retablir_Horloge (void);
short result;
short port = 0x3c4;
OCTET panneau_demande;
OCTET panneau_encours;
short xs_coord;
short ys_coord;
short xs_old_coord;
short ys_old_coord;
short xs_new;
short ys_new;
short xs_old;
short ys_old;
short x_ecart=0;
short y_ecart=0;
OCTET forme_curseur;
OCTET num_curseur;
OCTET etat_zone_croix;
short xinf_zone_croix;
short yinf_zone_croix;
short xsup_zone_croix;
short ysup_zone_croix;
OCTET etat_inter;
OCTET Lire_Panneau_Demande (void)
{
    return (panneau_demande);
}
void Ecrire_Panneau_Demande (OCTET pn)
{
    panneau_demande = pn;
}
OCTET Lire_Panneau_Encours (void)
{
    return (panneau_encours);
}
void Ecrire_Panneau_Encours (OCTET pn)
{
    panneau_encours = pn;
}
short X_Fleche (void)
{
    return (xs_coord);
}
short Y_Fleche (void)
{
    return (ys_coord);
}
short X_Croix (void)
{
    short rep;
    rep = -1;
    if (forme_curseur == CROIX)
        rep = xs_coord - xinf_zone_croix;
    return (rep);
}
short Y_Croix (void)
{
    short rep;
    rep = -1;
    if (forme_curseur == CROIX)
        rep = ys_coord - yinf_zone_croix;
    return (rep);
}
void Souris (OCTET etat)
{
    if (etat == OFF)
    {
        disable ();
        etat_inter = OFF;
        enable ();
        Restaurer_Fond ();
    }
    if (etat == ON)
    {
        Sauver_Fond ();
        Afficher_Souris ();
        disable ();
        etat_inter = ON;
        enable ();
    }
}
void interrupt far Routine_Timer_Interruption (void)
{
    if ( etat_inter == OFF )
    {
        enable ();
        (void)outp (0x20,0x20);
        return;
    }
    xs_new = Lire_X_Souris ();
    ys_new = Lire_Y_Souris ();
    if (xs_new > LIMITE_X_ECRAN - CURS_LONG_FLECHE)
        xs_new = LIMITE_X_ECRAN - CURS_LONG_FLECHE;
    if (ys_new > LIMITE_Y_ECRAN - CURS_HAUT_FLECHE)
        ys_new = LIMITE_Y_ECRAN - CURS_HAUT_FLECHE;
    xs_coord = xs_new + x_ecart;
    ys_coord = ys_new + y_ecart;
    Determiner_Curseur ();
    if ( (xs_new != xs_old) | (ys_new != ys_old) )
    {
        Restaurer_Fond ();
        Sauver_Fond ();
        Afficher_Souris ();
        xs_old = xs_new;
        ys_old = ys_new;
        xs_old_coord = xs_coord;
        ys_old_coord = ys_coord;
    }
    if (etat_zone_croix == ON)
    {
        if (Test_Zone (xs_coord,ys_coord,xinf_zone_croix,
                       yinf_zone_croix,
                       xsup_zone_croix,
                       ysup_zone_croix) == ON)
        {
            if (forme_curseur != CROIX)
            {
                Restaurer_Fond ();
                forme_curseur = CROIX;
                Sauver_Fond ();
                Afficher_Souris ();
            }
        }
        if (Test_Zone (xs_coord,ys_coord,xinf_zone_croix,
                       yinf_zone_croix,
                       xsup_zone_croix,
                       ysup_zone_croix) == OFF)
        {
            if (forme_curseur != FLECHE)
            {
                Restaurer_Fond ();
                forme_curseur = FLECHE;
                Sauver_Fond ();
                Afficher_Souris ();
            }
        }
    }
    if (Clic_Souris () == CLIC_GAUCHE)
    {
        if (ys_coord <= 11)
        {
            if ( (xs_coord >= 0) & (xs_coord <= 47) )
            {
                panneau_demande = 1;
            }
            if ( (xs_coord >= 51) & (xs_coord <= 98) )
            {
                panneau_demande = 2;
            }
            if ( (xs_coord >= 102) & (xs_coord <= 148) )
            {
                panneau_demande = 3;
            }
            if ( (xs_coord >= 152) & (xs_coord <= 189) )
            {
                panneau_demande = 4;
            }
            if ( (xs_coord >= 193) & (xs_coord <= 228) )
            {
                panneau_demande = 5;
            }
            if ( (xs_coord >= 232) & (xs_coord <= 260) )
            {
                panneau_demande = 6;
            }
            if ( (xs_coord >= 264) & (xs_coord <= 298) )
            {
                panneau_demande = 7;
            }
            if ( (xs_coord >= 302) & (xs_coord <= 319) )
            {
                panneau_demande = 8;
            }
            if (panneau_demande == panneau_encours) panneau_demande = 0;
        }
    }
    enable ();
    (void)outp (0x20,0x20);
}
void far Installer_Timer_Interruption (void)
{
    disable ();
    Accelerer_Horloge (FREQUENCE);
    Ancienne_Interruption_Timer = getvect (TIMER_INTERRUPTION);
    setvect (TIMER_INTERRUPTION,Routine_Timer_Interruption);
    enable ();
}
void far Desinstaller_Timer_Interruption (void)
{
    disable ();
    Retablir_Horloge ();
    setvect (TIMER_INTERRUPTION,
             Ancienne_Interruption_Timer);
    enable ();
}
BOOL Activer_Souris (void)
{
    union REGS reg;
    etat_zone_croix = OFF;
    forme_curseur = FLECHE;
    num_curseur = CURS_FLECHE_1;
    reg.x.ax=0x00;
    int86(0x33, &reg, &reg);
    if (reg.x.ax==0x00)
        return (FAUX);
    reg.x.ax=0x0f;
    reg.x.cx=8;
    reg.x.dx=16;
    int86(0x33, &reg, &reg);
    reg.x.ax=0x08;
    reg.x.cx=0;
    reg.x.dx=399;
    int86(0x33, &reg, &reg);
    reg.x.ax = 0x04;
    reg.x.cx = CURS_ORIGX*2;
    reg.x.dx = CURS_ORIGY;
    int86(0x33, &reg, &reg);
    xs_new = Lire_X_Souris ();
    ys_new = Lire_Y_Souris ();
    xs_old = xs_new;
    ys_old = ys_new;
    etat_inter = ON;
    Installer_Timer_Interruption ();
    return (VRAI);
}
BOOL Desactiver_Souris (void)
{
    Desinstaller_Timer_Interruption ();
    return 0;
}
void Afficher_Souris (void)
{
    result = inport(port);
    if (forme_curseur == FLECHE)
        Afficher_Bob (Lire_Page (),num_curseur,xs_new,ys_new,MASK_ON);
    else if ( (xs_coord - 3 >= 0) & (ys_coord - 5 >=0) )
        Afficher_Bob (Lire_Page (),CURS_CROIX,xs_coord-3,ys_coord-5,MASK_ON);
    outport (port,result);
}
void Sauver_Fond (void)
{
    if (forme_curseur == FLECHE)
        Lire_Bob (CURS_FOND_FLECHE,Lire_Page (),xs_new,ys_new);
    else if ( (xs_coord - 3 >= 0) & (ys_coord - 5 >=0) )
        Lire_Bob (CURS_FOND_CROIX,Lire_Page (),xs_coord-3,ys_coord-5);
}
void Restaurer_Fond (void)
{
    result = inport(port);
    if (forme_curseur == FLECHE)
        Afficher_Bob (Lire_Page (),CURS_FOND_FLECHE,xs_old,ys_old,MASK_OFF);
    else if ( (xs_old_coord - 3 >= 0) & (ys_old_coord - 5 >=0) )
        Afficher_Bob (Lire_Page (),CURS_FOND_CROIX,xs_old_coord-3,ys_old_coord-5,MASK_OFF);
    outport (port,result);
}
void Repositionner_Souris (short x,short y)
{
    union REGS reg;
    reg.x.ax = 0x04;
    reg.x.cx = x*2;
    reg.x.dx = y;
    int86(0x33, &reg, &reg);
}
short Lire_X_Souris (void)
{
    union REGS reg;
    int px;
    reg.x.ax=0x03;
    int86(0x33, &reg, &reg);
    px=reg.x.cx/2;
    return (px);
}
short Lire_Y_Souris (void)
{
    union REGS reg;
    int py;
    reg.x.ax=0x03;
    int86(0x33, &reg, &reg);
    py=reg.x.dx;
    return (py);
}
short Clic_Souris(void)
{
    union REGS reg;
    int clic;
    reg.x.ax=0x03;
    int86(0x33, &reg, &reg);
    clic=reg.h.bl & 3;
    return (clic);
}
OCTET Test_Zone (short xm,short ym,short px,short py,short tx,short ty)
{
    OCTET rep;
    rep = OFF;
    if ( (xm >= px) & (xm <= tx) & (ym >= py) & (ym <= ty)) rep = ON;
    return (rep);
}
OCTET Test_Clic_Zone (short xm,short ym,short px,short py,short tx,short ty)
{
    OCTET rep;
    rep = OFF;
    if (Clic_Souris () == CLIC_GAUCHE)
        if ( (xm >= px) & (xm <= tx) & (ym >= py) & (ym <= ty))
            rep = ON;
    return (rep);
}
void Sens_1v2_4v3 (void)
{
    x_ecart = CURS_LONG_FLECHE - 1;
    Repositionner_Souris (xs_new - (CURS_LONG_FLECHE - 1),ys_new);
}
void Sens_2v1_3v4 (void)
{
    x_ecart = 0;
    Repositionner_Souris (xs_new + (CURS_LONG_FLECHE - 1),ys_new);
}
void Sens_1v4_2v3 (void)
{
    y_ecart = CURS_HAUT_FLECHE - 1;
    Repositionner_Souris (xs_new,ys_new - (CURS_HAUT_FLECHE - 1));
}
void Sens_4v1_3v2 (void)
{
    y_ecart = 0;
    Repositionner_Souris (xs_new,ys_new + (CURS_HAUT_FLECHE - 1));
}
void Sens_1v3 (void)
{
    x_ecart = CURS_LONG_FLECHE - 1;
    y_ecart = CURS_HAUT_FLECHE - 1;
    Repositionner_Souris (xs_new - (CURS_LONG_FLECHE - 1),ys_new - (CURS_HAUT_FLECHE - 1));
}
void Sens_2v4 (void)
{
    x_ecart = 0;
    y_ecart = CURS_HAUT_FLECHE - 1;
    Repositionner_Souris (xs_new + (CURS_LONG_FLECHE - 1),ys_new - (CURS_HAUT_FLECHE - 1));
}
void Sens_3v1 (void)
{
    x_ecart = 0;
    y_ecart = 0;
    Repositionner_Souris (xs_new + (CURS_LONG_FLECHE - 1),ys_new + (CURS_HAUT_FLECHE - 1));
}
void Sens_4v2 (void)
{
    x_ecart = CURS_LONG_FLECHE - 1;
    y_ecart = 0;
    Repositionner_Souris (xs_new - (CURS_LONG_FLECHE - 1),ys_new + (CURS_HAUT_FLECHE - 1));
}
void Determiner_Curseur (void)
{
    if (num_curseur == 1)
    {
        if ( (xs_coord > 159) & (ys_coord <= 199) )
        {
            num_curseur = 2 ;
            Sens_1v2_4v3 ();
        }
        if ( (xs_coord > 159) & (ys_coord > 199) )
        {
            num_curseur = 3 ;
            Sens_1v3 ();
        }
        if ( (xs_coord <= 159) & (ys_coord > 199) )
        {
            num_curseur = 4 ;
            Sens_1v4_2v3 ();
        }
    }
    if (num_curseur == 2)
    {
        if ( (xs_coord <= 159) & (ys_coord <= 199) )
        {
            num_curseur = 1 ;
            Sens_2v1_3v4 ();
        }
        if ( (xs_coord <= 159) & (ys_coord > 199) )
        {
            num_curseur = 4 ;
            Sens_2v4 ();
        }
        if ( (xs_coord > 159) & (ys_coord > 199) )
        {
            num_curseur = 3 ;
            Sens_1v4_2v3 ();
        }
    }
    if (num_curseur == 3)
    {
        if ( (xs_coord <= 159) & (ys_coord > 199) )
        {
            num_curseur = 4 ;
            Sens_2v1_3v4 ();
        }
        if ( (xs_coord <= 159) & (ys_coord <= 199) )
        {
            num_curseur = 1 ;
            Sens_3v1 ();
        }
        if ( (xs_coord > 159) & (ys_coord <= 199) )
        {
            num_curseur = 2 ;
            Sens_4v1_3v2 ();
        }
    }
    if (num_curseur == 4)
    {
        if ( (xs_coord <= 159) & (ys_coord <= 199) )
        {
            num_curseur = 1 ;
            Sens_4v1_3v2 ();
        }
        if ( (xs_coord > 159) & (ys_coord <= 199) )
        {
            num_curseur = 2 ;
            Sens_4v2 ();
        }
        if ( (xs_coord > 159) & (ys_coord > 199) )
        {
            num_curseur = 3 ;
            Sens_1v2_4v3 ();
        }
    }
}
void Activer_Zone_Croix (short xinf,short yinf,short xsup,short ysup)
{
    etat_zone_croix = ON;
    xinf_zone_croix = xinf;
    yinf_zone_croix = yinf;
    xsup_zone_croix = xsup;
    ysup_zone_croix = ysup;
}
void Desactiver_Zone_Croix (void)
{
    etat_zone_croix = OFF;
}
void Accelerer_Horloge (OCTET freq)
{
    unsigned short tspeed;
    tspeed = 1193180UL / freq;
    outportb (0x43,0x3c);
    outportb (0x40,tspeed & 0xff);
    outportb (0x40,tspeed >> 8);
}
void Retablir_Horloge (void)
{
    outportb (0x43,0x3c);
    outportb (0x40,0xff);
    outportb (0x40,0xff);
}
void Pause (unsigned short duree)
{
    delay (duree * (FREQUENCE/18.206759) );
}
