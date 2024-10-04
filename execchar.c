#include <DOS.H>
#include <STDIO.H>
#include <STDARG.H>
#include <STRING.H>
#include "SOUREXEC/EXECGRAP.H"
#include "SOUREXEC/EXECCLAV.H"
#include "SOUREXEC/EXECCHAR.H"
void PrintChar(char pg,char echx,char echy,char caractere,
               int x,int y,OCTET cc,OCTET cf)
{
    typedef OCTET CARDEF[256][8];
    typedef CARDEF far *CARPTR;
    OCTET i, k,
          masque;
    static CARPTR fptr = (CARPTR) 0;
    if( fptr == (CARPTR) 0 )
        fptr = MK_FP(0xf000,0x0fa6e);
    if( cf == 255 )
        for( i = 0; i < 8; ++i )
        {
            masque = (*fptr)[caractere][i];
            for ( k = 0; k < 8; ++k, masque <<= 1 )
            {
                if ( masque & 128 )
                    Tracer_Carre_Plein (pg,x+(k*echx),
                                        y+(i*echy),
                                        x+(k*echx)+echx - 1,
                                        y+(i*echy)+echy - 1,
                                        cc);
            }
        }
    else
        for ( i = 0; i < 8; ++i )
        {
            masque = (*fptr)[caractere][i];
            for ( k = 0; k < 8; ++k, masque <<= 1 )
            {
                Tracer_Carre_Plein (pg,x+(k*echx),
                                    y+(i*echy),
                                    x+(k*echx)+echx - 1,
                                    y+(i*echy)+echy - 1,
                                    (OCTET) (( masque & 128 ) ? cc : cf) );
            }
        }
}
void Print (char pg,char echx,char echy,int x,int y,
            OCTET cc,OCTET cf,char * string, ... )
{
    va_list parameter;
    char affichage[255],
         *cp;
    va_start( parameter, string );
    vsprintf( affichage, string, parameter );
    for( cp = affichage; *cp; ++cp, x+= (8*echx) )
        PrintChar(pg,echx,echy,*cp,x,y,cc,cf);
}
void Print_Titre (char page,short y,char *st)
{
    char cpt;
    char nbcar;
    char numcar;
    char *bk_st;
    short larg;
    short x;
    short data_char [26][4] =
    {
        { 0,170,21,26},
        { 22,170,21,26},
        { 44,170,21,26},
        { 66,170,21,26},
        { 88,170,21,26},
        {110,170,21,26},
        {132,170,20,26},
        {153,170,20,26},
        {174,170, 6,26},
        {181,170,20,26},
        {202,170,17,26},
        {220,170,20,26},
        {241,170,22,26},
        {264,170,22,26},
        { 0,198,21,26},
        { 22,198,21,26},
        { 44,198,21,26},
        { 66,198,21,26},
        { 88,198,21,26},
        {110,198,22,26},
        {133,198,20,26},
        {154,198,21,26},
        {176,198,22,26},
        {199,198,18,26},
        {218,198,18,26},
        {237,198,17,26}
    };
    nbcar = strlen (st);
    bk_st = st;
    larg = 0;
    for (cpt = 0;
            cpt < nbcar;
            cpt ++)
    {
        if (*st == 32) larg += 20;
        if ( (*st >= 65) & (*st <= 90) )
        {
            numcar = *st - 65;
            larg += data_char [numcar][2] + 2;
        }
        st ++;
    }
    x = (320 - larg) / 2;
    st = bk_st;
    for (cpt = 0;
            cpt < nbcar;
            cpt ++)
    {
        if (*st == 32) x += 20;
        if ( (*st >= 65) & (*st <= 90) )
        {
            numcar = *st - 65;
            Lire_Image_Pcx ("SPRFILES/DATA",page,x,y,MASK_ON,data_char [numcar][0],
                            data_char [numcar][1],
                            data_char [numcar][2],
                            data_char [numcar][3]);
            x += data_char [numcar][2] + 2;
        }
        st ++;
    }
}
void Print_Vl (char page,char echx,char echy,short x,short y,
               OCTET cc,OCTET cf,char nbu,unsigned long valeur)
{
    char cpt;
    char nbzero;
    char backup [10];
    char buffer [10];
    sprintf (buffer,"%lu",valeur);
    nbzero = nbu - strlen (buffer);
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
    Print (page,echx,echy,x,y,cc,cf,buffer);
}
void Input (char pg,char echx,char echy,int x,int y,
            OCTET cc,OCTET cf,OCTET cr,
            char clav,char nb_car,char *buffer)
{
    OCTET cpt;
    char touche;
    char touche_actionnee;
    char curseur;
    char code [128];
    curseur = 0;
    for (cpt = 0;
            cpt < 128;
            cpt ++)
        code [cpt] = 0;
    code [57] = 32;
    code [14] = -1;
    code [28] = -2;
    code [16] = 65;
    code [48] = 66;
    code [46] = 67;
    code [32] = 68;
    code [18] = 69;
    code [33] = 70;
    code [34] = 71;
    code [35] = 72;
    code [23] = 73;
    code [36] = 74;
    code [37] = 75;
    code [38] = 76;
    code [39] = 77;
    code [49] = 78;
    code [24] = 79;
    code [25] = 80;
    code [30] = 81;
    code [19] = 82;
    code [31] = 83;
    code [20] = 84;
    code [22] = 85;
    code [47] = 86;
    code [44] = 87;
    code [45] = 88;
    code [21] = 89;
    code [17] = 90;
    code [11] = 48;
    code [ 2] = 49;
    code [ 3] = 50;
    code [ 4] = 51;
    code [ 5] = 52;
    code [ 6] = 53;
    code [ 7] = 54;
    code [ 8] = 55;
    code [ 9] = 56;
    code [10] = 57;
    code [82] = 48;
    code [79] = 49;
    code [80] = 50;
    code [81] = 51;
    code [75] = 52;
    code [76] = 53;
    code [77] = 54;
    code [71] = 55;
    code [72] = 56;
    code [73] = 57;
    for (cpt = 0;
            cpt < nb_car;
            cpt ++)
        Print (pg,echx,echy,x + (cpt*(8*echx)),y,cc,cf," ");
    Tracer_Carre_Plein (pg,
                        x + (curseur * (8 * echx)),
                        y + (7 * echy),
                        x + (curseur * (8 * echx)) + (8 * echx) - 1,
                        y + (7 * echy) + (echy - 1),
                        cr);
    *buffer = 0;
    do
    {
        touche_actionnee = Lire_Code_Touche ();
        touche = code [touche_actionnee];
        if ( (touche == -1) & (curseur > 0) )
        {
            Print (pg,echx,echy,x + (curseur * (8 * echx)),y,cc,cf," ");
            curseur --;
            Print (pg,echx,echy,x + (curseur * (8 * echx)),y,cc,cf," ");
            *(buffer + curseur) = 0;
            Tracer_Carre_Plein (pg,
                                x + (curseur * (8 * echx)),
                                y + (7 * echy),
                                x + (curseur * (8 * echx)) + (8 * echx) - 1,
                                y + (7 * echy) + (echy - 1),
                                cr);
        }
        if (
            (
                (touche >= 48) & (touche <= 57) &
                ( (clav == NUM) | (clav == ALPNUM) )
            )
            |
            (
                (touche >= 65) & (touche <= 90) &
                ( (clav == ALP) | (clav == ALPNUM) )
            )
            |
            (
                (touche == 32) &
                ( (clav == ALP) | (clav == ALPNUM) )
            )
        )
        {
            *(buffer + curseur) = touche;
            *(buffer + curseur + 1) = 0;
            Print (pg,echx,echy,x,y,cc,cf,buffer);
            if (curseur < (nb_car - 1))
                curseur ++;
            Tracer_Carre_Plein (pg,
                                x + (curseur * (8 * echx)),
                                y + (7 * echy),
                                x + (curseur * (8 * echx)) + (8 * echx) - 1,
                                y + (7 * echy) + (echy - 1),
                                cr);
        }
    }
    while ( Lire_Action_Touche (ENTREE) != 1 );
}
