#include <DOS.H>
#include <STDIO.H>
#include <STDARG.H>
#include "SOUREDIT/EDITGRAP.H"
#include "SOUREDIT/EDITCHAR.H"
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
