#include <DOS.H>
#include "SOURGAME/GAMECLAV.H"
void interrupt far Routine_Clavier_Interruption (void);
void (interrupt far *Ancienne_Interruption_Clavier)(void);
char bktouche;
char codetouche;
char actiontouche [128];
char bufferfleche [2][128];
void interrupt far Routine_Clavier_Interruption (void)
{
    register char x;
    codetouche = inp (0x60);
    x = inp (0x61);
    (void)outp (0x61,(x | 0x80));
    (void)outp (0x61,x);
    (void)outp (0x20,0x20);
    actiontouche[codetouche & 127] = 1;
    if (codetouche & 128)
    {
        actiontouche[codetouche & 127] = 0;
        codetouche = 0;
    }
}
void far Installer_Clavier_Interruption (void)
{
    OCTET cptbuf;
    for (cptbuf = 0;
            cptbuf < 128;
            cptbuf++)
        bufferfleche [0][cptbuf] = 0;
    for (cptbuf = 0;
            cptbuf < 128;
            cptbuf++)
        bufferfleche [1][cptbuf] = 0;
    bufferfleche [1][FLECHE_DROITE] =1;
    bufferfleche [1][FLECHE_GAUCHE] =2;
    bufferfleche [1][FLECHE_BAS ] =3;
    bufferfleche [1][FLECHE_HAUT ] =4;
    Ancienne_Interruption_Clavier = getvect (CLAVIER_INTERRUPTION);
    setvect (CLAVIER_INTERRUPTION,Routine_Clavier_Interruption);
}
void far Desinstaller_Clavier_Interruption (void)
{
    disable ();
    setvect (CLAVIER_INTERRUPTION,
             Ancienne_Interruption_Clavier);
    enable ();
}
char far Lire_Code_Touche (void)
{
    return (codetouche);
}
char far Lire_Action_Touche (char touche)
{
    return (actiontouche[touche]);
}
char far Lire_Direction_Touche (void)
{
    if (actiontouche [bktouche] == 0) bktouche = 0;
    if (actiontouche[codetouche] == 1)
    {
        if (codetouche == bktouche) return (0);
        else bktouche = codetouche;
    }
    return (bufferfleche [ actiontouche [codetouche] ] [ codetouche ]);
}
