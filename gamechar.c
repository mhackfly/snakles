#include <DOS.H>
#include <STDIO.H>
#include <STDARG.H>
#include "SOURGAME/GAMEGRAP.H"
void PrintChar(char pg, char caractere, int x, int y, OCTET cc, OCTET cf)
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
                if ( masque & 128 )
                    Afficher_Point (pg, x+k, y+i, cc);
        }
    else
        for ( i = 0; i < 8; ++i )
        {
            masque = (*fptr)[caractere][i];
            for ( k = 0; k < 8; ++k, masque <<= 1 )
                Afficher_Point (pg, x+k, y+i, (OCTET) (( masque & 128 ) ? cc : cf) );
        }
}
void Print ( char pg,int x, int y, OCTET cc, OCTET cf, char * string, ... )
{
    va_list parameter;
    char affichage[255],
         *cp;
    va_start( parameter, string );
    vsprintf( affichage, string, parameter );
    for( cp = affichage; *cp; ++cp, x+= 8 )
        PrintChar( pg,*cp, x, y, cc, cf );
}
void Demo (void)
{
    OCTET pg;
    short x,y,lg,ht;
    FILE *flux;
    short cpt_point_x;
    short cpt_point_y;
    OCTET couleur_point;
    pg = 0;
    x = 0;
    y = 0;
    lg = 319;
    ht = 199;
    Print (pg,0, 0,10,0,"ABCDEFGHIJKLMNOPQRSTUVWXYZ");
    Print (pg,0, 8,10,0,"abcdefghijklmnopqrstuvwxyz");
    Print (pg,0, 16,10,0,"0123456789");
    Print (pg,0, 24,10,0,"xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
    Print (pg,0, 32,10,0,"COMPTE A REBOURS SUR LA DUREE DU");
    Print (pg,0, 40,10,0,"TABLEAU. OK R N L A OUI NON");
    Print (pg,0, 48,10,0,"LE TABLEAU NUMERO VA ETRE DETRUIT.");
    Print (pg,0, 56,10,0,"CONFIRMATION. VITESSE");
    Print (pg,0, 64,10,0,"NOMBRE DE DEPLACEMENT AVANT UN");
    Print (pg,0, 72,10,0,"CHANGEMENT DE DIRECTION.");
    Print (pg,0, 80,10,0,"BONUS POINT TEMPS PLUS. MOINS.");
    Print (pg,0, 88,10,0,"TOUS LES SERPENTS VONT ETRES EFFACER.");
    Print (pg,0, 96,10,0,"TOUS LES DESSINS");
    Print (pg,0,104,10,0,"SORTIE DE L'EDITEUR.");
    Print (pg,0,112,10,0,"LE TABLEAU VA ETRE EFFACER.");
    Print (pg,0,120,10,0,"TABLEAU COMPLET.");
    Print (pg,0,128,10,0,"TABLEAU INCOMPLET. CONDITIONS:");
    Print (pg,0,136,10,0,"- AU MOINS UNE BOULE BLEU.");
    Print (pg,0,144,10,0,"- SERPENT BLANC DEFINI.");
    flux = fopen ("font.bmp","wb");
    if (flux == NULL)
        return;
    for (cpt_point_y = 0 ; cpt_point_y < ht ; cpt_point_y++)
    {
        for (cpt_point_x = 0 ; cpt_point_x < lg ; cpt_point_x++)
        {
            couleur_point = Lire_Point (pg,
                                        x+cpt_point_x,
                                        y+cpt_point_y);
            fwrite(&couleur_point,1,1,flux);
        }
    }
    fclose (flux);
}
